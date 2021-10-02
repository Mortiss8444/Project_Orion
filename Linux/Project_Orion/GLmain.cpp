#include "Dependencies/GLFW/include/glad/glad.h"
#include <GLFW/glfw3.h>
//#include "glad/glad.h"
#include <iostream>

#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtc/type_ptr.hpp"
#include <mutex>
#include <thread>

#include "GLmain.h"
#include "MapRenderer.h"
#include "Sat_class.h"
#include "TextRenderer.h"
#include "Texture.h"
#include "shader.h"

namespace Project_Orion {
//#define ASSERT(x) if (!(x)) __debugbreak();
//#define GLCall(x) GLClearError();\
//    x;\
//    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//
//    void GLClearError()
//    {
//        while (glGetError() != GL_NO_ERROR);
//    }
//    bool GLLogCall(const char* function, const char* file, int line)     <-
//    use it to debug openGL's functions
//    {
//        while (GLenum error = glGetError())
//        {
//            std::cout << "[OpenGL Error]: (" << error << "): " << function <<
//                " " << file << ":" << line << std::endl;
//            return false;
//        }
//        return true;
//    }

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void New_Text(Shader textShader, std::string &s_name, float x, float y, float r,
              float g, float b, float act_long, float act_lat);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int glLoop() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project_Orion", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  // OpenGL state
  // ------------
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /*-------------Text init----------------*/
  Shader shader("Shaders/text.vs.shader", "Shaders/text.fs.shader");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f,
                                    static_cast<float>(SCR_HEIGHT));
  shader.use();
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE,
                     glm::value_ptr(projection));

  LoadFont();
  /*--------------Map init----------------*/
  Shader shaderProgram("Shaders/image.vs.shader", "Shaders/image.fs.shader");

  InitVertices();
  shaderProgram.use();
  shaderProgram.setFloat("scale", 0.5f);

  Texture texture("map.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB,
                  GL_UNSIGNED_BYTE);
  texture.texUnit(shaderProgram, "tex0", 0);
  /*--------------Satellite icon init----------------*/
  Shader shaderPoint("Shaders/Circle.vs.shader", "Shaders/Circle.fs.shader",
                     "Shaders/Circle.gs.shader");

  shaderPoint.use();
  GLuint circle_vbo;
  glGenBuffers(1, &circle_vbo);

  // Create VAO
  GLuint circle_vao;
  glGenVertexArrays(1, &circle_vao);
  glBindVertexArray(circle_vao);

  glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Satellite) * 100, nullptr,
               GL_DYNAMIC_DRAW);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderPoint.ID, "pos");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Satellite),
                        (void *)offsetof(Satellite, m_Pos));

  GLint colAttrib = glGetAttribLocation(shaderPoint.ID, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Satellite),
                        (void *)offsetof(Satellite, m_Color));

  GLint sidesAttrib = glGetAttribLocation(shaderPoint.ID, "sides");
  glEnableVertexAttribArray(sidesAttrib);
  glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(Satellite),
                        (void *)offsetof(Satellite, m_Sides));

  Satellite *sat = nullptr;
  std::mutex mtx1;
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();

    if (displayInitWindow) {
      RenderText(shader, "Waiting for commands...", (SCR_WIDTH / 2.0) - 185,
                 SCR_HEIGHT / 2.0, 0.8, glm::vec3(1.0, 1.0f, 1.0f));
      // glfw: swap buffers and poll IO events (keys pressed/released, mouse
      // moved etc.)
      glfwSwapBuffers(window);
    }
    mtx1.lock();
    if (!satelliteStorage.empty()) {
      glUseProgram(shaderProgram.ID);
      // Binds texture so that is appears in rendering
      glBindTexture(GL_TEXTURE_2D, texture.ID);
      // Bind the VAO so OpenGL knows to use it
      glBindVertexArray(img_VAO);
      // Draw primitives, number of indices, datatype of indices, index of
      // indices
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      shaderPoint.use();
      glBindVertexArray(circle_vao);
      glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      sizeof(Satellite) * satelliteStorage.size(),
                      &satelliteStorage[0]);
      glDrawArrays(GL_POINTS, 0, satelliteStorage.size());

      for (size_t i = 0; i < satelliteStorage.size(); i++) {
        New_Text(shader, satelliteStorage[i].m_Stl_name,
                 satelliteStorage[i].m_Pos.x, satelliteStorage[i].m_Pos.y,
                 satelliteStorage[i].m_Color.r, satelliteStorage[i].m_Color.g,
                 satelliteStorage[i].m_Color.b,
                 satelliteStorage[i].m_actLatLong.x,
                 satelliteStorage[i].m_actLatLong.y);
      }
      glfwSwapBuffers(window);
    }
    mtx1.unlock();

    if (terminateGL) {
      std::cout << "[Info]: Terminating GL..." << std::endl;
      break;
    }
  }
  glfwTerminate();
  glDeleteProgram(shader.ID);
  glDeleteProgram(shaderProgram.ID);
  glDeleteProgram(shaderPoint.ID);

  texture.Delete();
  glDeleteBuffers(1, &circle_vbo);
  glDeleteVertexArrays(1, &circle_vao);

  deleteVerticies();
  delete sat;
  return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void New_Text(Shader textShader, std::string &s_name, float x, float y, float r,
              float g, float b, float act_long, float act_lat) {
  float pixLong = (x + 1.0) * (SCR_WIDTH / 2);
  float pixLat = (y + 1.0) * (SCR_HEIGHT / 2);

  std::string str_a = std::to_string(static_cast<int>(act_lat)) + "*N";
  std::string str_b = std::to_string(static_cast<int>(act_lat * -1)) + "*S";
  std::string str_c = std::to_string(static_cast<int>(act_long * -1)) + "*W";
  std::string str_d = std::to_string(static_cast<int>(act_long)) + "*E";

  std::string str_s = y > 0 ? str_a : str_b;
  std::string str_f = x > 0 ? str_d : str_c;

  RenderText(textShader, s_name, pixLong - 25, pixLat + 13, 0.27,
             glm::vec3(r, g, b));
  RenderText(textShader, str_s + " " + str_f, pixLong - 25, pixLat - 17, 0.27,
             glm::vec3(r, g, b));
}
} // namespace Project_Orion
