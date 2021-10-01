#include "Dependencies/GLFW/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "MapRenderer.h"

namespace Project_Orion {
GLfloat img_vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.67f, -0.67f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
    -0.67f, 0.67f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left corner
    0.67f,  0.67f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Upper right corner
    0.67f,  -0.67f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] = {
    0, 2, 1, // Upper triangle
    0, 3, 2  // Lower triangle
};
GLuint img_VAO = 0;
GLuint img_VBO = 0;
GLuint img_IBO = 0;

void InitVertices() {
  // Generates Vertex Array Object and binds it
  glGenVertexArrays(1, &img_VAO);
  glBindVertexArray(img_VAO);

  // Generates Vertex Buffer Object and links it to vertices
  glGenBuffers(1, &img_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, img_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(img_vertices), img_vertices,
               GL_STATIC_DRAW);

  // Generates Element Buffer Object and links it to indices
  glGenBuffers(1, &img_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, img_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Links VBO attributes such as coordinates and colors to VAO
  glBindBuffer(GL_ARRAY_BUFFER, img_VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, img_VBO);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, img_VBO);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Unbind all to prevent accidentally modifying them
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void deleteVerticies() {
  glDeleteVertexArrays(1, &img_VAO);
  glDeleteBuffers(1, &img_VBO);
  glDeleteBuffers(1, &img_IBO);
}
} // namespace Project_Orion
