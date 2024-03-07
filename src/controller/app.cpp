#include "app.h"

GLfloat WINDOW_WIDTH = 800.f, WINDOW_HEIGHT = 600.f;

App::App() { set_up_glfw(); }

App::~App() {
  glDeleteProgram(shader);

  delete motionSystem;
  delete cameraSystem;
  delete renderSystem;

  glfwTerminate();
}

void App::run() {
  while (!glfwWindowShouldClose(window)) {
    float currentFrame, lastFrame;
    currentFrame = glfwGetTime();
    float deltaTime =
        currentFrame - lastFrame > 0 ? currentFrame - lastFrame : 1.0f / 60.0f;
    lastFrame = currentFrame;

    motionSystem->update(transformComponents, physicsComponents, deltaTime);
    bool should_close = cameraSystem->update(transformComponents, cameraID,
                                             *cameraComponent, deltaTime);
    if (should_close) {
      break;
    }

    renderSystem->update(transformComponents, renderComponents);
  }
}

void App::set_up_glfw() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Precious Moment!",
                            NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Could not initialize GLAD" << std::endl;
    glfwTerminate();
  }
}

void App::set_up_opengl() {
  // Set the clear color
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  // Set the rendering region to the actual screen size
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  //(left, top, width, height)
  glViewport(0, 0, w, h);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  shader =
      make_shader("../src/shaders/vertex.glsl", "../src/shaders/fragment.glsl");

  glUseProgram(shader);
  unsigned int projLocation = glGetUniformLocation(shader, "projection");
  glm::mat4 projection =
      glm::perspective(45.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
  glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void App::make_systems() {
  motionSystem = new MotionSystem();
  cameraSystem = new CameraSystem(shader, window);
  renderSystem = new RenderSystem(shader, window);
}