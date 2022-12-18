#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"
#include "model.h"
#include <GL/glut.h>

#include <iostream>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <string>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <string>
    #include <limits.h>
 #endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::string getexepath()
{
  #ifdef WINDOWS
    char result[ MAX_PATH ];
    std::string out = std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
    return out.substr(0, out.find_last_of("\\")+1);
  #else
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    std::string out = std::string( result, (count > 0) ? count : 0 );
    return out.substr(0, out.find_last_of("/")+1);
  #endif
  
}

class Checkerboard {
  int displayListId;
  int width;
  int depth;
public:
  Checkerboard(int width, int depth): width(width), depth(depth) {}
  double centerx() {return width / 2;}
  double centerz() {return depth / 2;}
  void create() {
  
    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = {4, 3, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 0);
    for (int x = 0; x < width - 1; x++) {
      for (int z = 0; z < depth - 1; z++) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                     (x + z) % 2 == 0 ? RED : WHITE);
        glVertex3d(x, 0, z);
        glVertex3d(x+1, 0, z);
        glVertex3d(x+1, 0, z+1);
        glVertex3d(x, 0, z+1);
      }
    }
    glEnd();
    glEndList();
   // glRotatef(-25-180,0,1,0);
  }
  void draw() {
    glCallList(displayListId);
  }
};



int main()
{   
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    

    // build and compile shaders
    // -------------------------
    Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

    // load models
    // -----------
    Model sphere(getexepath() + "sphere.obj");
    Model cyl(getexepath() + "cyl.obj");
    Model cube(getexepath() + "cube.obj");
    Model checker(getexepath() + "checkerboard.obj");
    Checkerboard checkerboard(8, 8);
    checkerboard.create();
    bool first = true;
    

    
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        if(first) {
            camera.Position.z += 5;
            first = false;
        }
        
       
        
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        
        
        glm::mat4 model = glm::mat4(1.0f);
        
      
        
        model = glm::rotate(model, 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        sphere.Draw(ourShader);
        model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model);
        cyl.Draw(ourShader);
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model);
        cube.Draw(ourShader);
      
     
           
        model = glm::translate(model, glm::vec3(0.0f,1.0f,0.0f));
        ourShader.setMat4("model", model);
        checker.Draw(ourShader);
        
        
       // checkerboard.draw();



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    bool shift, ctrl;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) 
        shift = true;
    else 
        shift = false;

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) 
        ctrl = true;
    else 
        ctrl = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if(ctrl)
            camera.yaw(-2);
        else
            camera.ProcessKeyboard(LEFT, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if(ctrl)
            camera.yaw(2);
        else
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if(ctrl)
            camera.pitch(-2);
        else if(shift)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        else
            camera.ProcessKeyboard(UP, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if(ctrl)
            camera.pitch(2);
        else if(shift)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        else
            camera.ProcessKeyboard(DOWN, deltaTime);
    }
    else if (shift && glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        camera.rotate(-1.0f);
    else if (shift && glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        camera.rotate(1.0f);
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.reset();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



