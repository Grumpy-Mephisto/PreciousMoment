#include "render_system.h"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow *window) {
  modelLocation = glGetUniformLocation(shader, "model");
  this->window = window;
}

void RenderSystem::update(
    std::unordered_map<unsigned int, TransformComponent> &transformComponents,
    std::unordered_map<unsigned int, RenderComponent> &renderComponents) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto &[entity, renderable] : renderComponents) {
    TransformComponent &transform = transformComponents[entity];

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform.position);
    model = glm::rotate(model, glm::radians(transform.eulers.z),
                        {0.0f, 0.0f, 1.0f});
    model = glm::rotate(model, glm::radians(transform.eulers.y),
                        {0.0f, 1.0f, 0.0f});
    model = glm::rotate(model, glm::radians(transform.eulers.x),
                        {1.0f, 0.0f, 0.0f});
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    // spin the object
    float speed = 0.05f;
    transform.eulers.z += speed;

    if (renderable.material != 0)
      glBindTexture(GL_TEXTURE_2D, renderable.material);
    else
      glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(renderable.VAO);
    glDrawArrays(GL_TRIANGLES, 0, renderable.vertexCount);
  }
  glfwSwapBuffers(window);
}