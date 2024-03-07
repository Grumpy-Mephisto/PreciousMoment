#include "camera_system.h"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow *window) {
  this->window = window;
  glUseProgram(shader);
  viewLocation = glGetUniformLocation(shader, "view");
}

bool CameraSystem::update(
    std::unordered_map<unsigned int, TransformComponent> &transformComponents,
    unsigned int cameraID, CameraComponent &cameraComponent, float dt) {

  glm::vec3 &pos = transformComponents[cameraID].position;
  glm::vec3 &eulers = transformComponents[cameraID].eulers;
  float theta = glm::radians(eulers.z);
  float phi = glm::radians(eulers.y);

  glm::vec3 &right = cameraComponent.right;
  glm::vec3 &up = cameraComponent.up;
  glm::vec3 &forwards = cameraComponent.forwards;

  forwards = {glm::cos(theta) * glm::cos(phi), glm::sin(theta) * glm::cos(phi),
              glm::sin(phi)};
  right = glm::normalize(glm::cross(forwards, global_up));
  up = glm::normalize(glm::cross(right, forwards));

  glm::mat4 view = glm::lookAt(pos, pos + forwards, up);
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

  handleKeyboardInput(pos, eulers, right, up, forwards);
  glfwPollEvents();

  return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void CameraSystem::handleKeyboardInput(glm::vec3 &pos, glm::vec3 &eulers,
                                       const glm::vec3 &right,
                                       const glm::vec3 &up,
                                       const glm::vec3 &forwards) {
  glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    dPos += forwards;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    dPos += right;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    dPos -= forwards;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    dPos -= right;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    dPos += global_up;
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    dPos -= global_up;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    dPos *= 2.0f;
  if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    dPos *= 0.5f;
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    eulers.z += 1.0f;
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    eulers.z -= 1.0f;

  if (glm::length(dPos) > 0.1f) {
    dPos = glm::normalize(dPos) * 1.0f;
    pos += 0.01f * dPos.x * forwards;
    pos += 0.01f * dPos.y * right;
    pos += 0.01f * dPos.z * up;
  }

  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    pos = {-1.25f, 2.0f, 1.25f};
    eulers = {1.0f, 1.0f, 0.0f};
  }
}
