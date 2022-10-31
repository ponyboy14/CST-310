#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "shader.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

int main()
{
    // create and setup the window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shiny Cubes", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    // set the look of the window
    glm::mat4 view = glm::lookAt(glm::vec3(-1.0f, 1.0f, 6.0f),
                glm::vec3(2.5f, 1.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
                );

    // vertices to make a cube
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // positions of the cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(2.0f, 0.0f, 0.0f), 
        glm::vec3(4.0f, 0.0f, 0.0f), 
        glm::vec3(6.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 2.0f, 0.0f), 
        glm::vec3(2.0f, 2.0f, 0.0f), 
        glm::vec3(4.0f, 2.0f, 0.0f), 
        glm::vec3(6.0f, 2.0f, 0.0f)
    };  
    // position of the lighting
    glm::vec3 lightPos[] = {
        glm::vec3(0.0f, 0.0f, 2.0f),
        glm::vec3(2.0f, 0.0f, 2.0f),
        glm::vec3(4.0f, 0.0f, 2.0f),
        glm::vec3(6.0f, 0.0f, 2.0f),
        glm::vec3(0.0f, 2.0f, 2.0f),
        glm::vec3(2.0f, 2.0f, 2.0f),
        glm::vec3(4.0f, 2.0f, 2.0f),
        glm::vec3(6.0f, 2.0f, 2.0f)

    };

    // How the cube views the lighting
    glm::vec3 viewPos[] = {
        glm::vec3(-0.7f, 0.0f, 2.0f),
        glm::vec3(1.3f, 0.0f, 2.0f),
        glm::vec3(3.3f, 0.0f, 2.0f),
        glm::vec3(5.3f, 0.0f, 2.0f),
        glm::vec3(-0.7f, 2.0f, 2.0f),
        glm::vec3(1.3f, 2.0f, 2.0f),
        glm::vec3(3.3f, 2.0f, 2.0f),
        glm::vec3(5.3f, 2.0f, 2.0f)

    };

    // shininess values of the cubes
    int shiny[8] = {32, 64, 128, 256, 2, 4, 8, 16};

    // load in the lighting shaders
    Shader lightingShader("lighting.vs", "lighting.fs");

    // bind buffers and arrays
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        // compute timing
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // clear the last frame
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        // create each cube
        for (int i = 0; i < 8; i++) {
            // activate shader and update the values
            lightingShader.use();
            lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
            lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            lightingShader.setVec3("lightPos", lightPos[i]);
            lightingShader.setVec3("viewPos", viewPos[i]);
            lightingShader.setInt("shininess", shiny[i]);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            lightingShader.setMat4("projection", projection);
            lightingShader.setMat4("view", view);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            lightingShader.setMat4("model", model);

            // create the cube with the shader attached
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // delete buffers and arrays
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    // end the window
    glfwTerminate();
    return 0;
}
