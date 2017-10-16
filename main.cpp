//
// Created by rostard on 16.10.17.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <string>

#include "font.h"
#include "game.h"
#include "resource_mager.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLFWwindow* window;

Game GameName(SCR_WIDTH, SCR_HEIGHT);

int Init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glfwSetKeyCallback(window, key_callback);

    return 0;
}

int main(){
    Init();

    Font f("fonts/arial.ttf");

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    GameName.Init();

    GLfloat deltaTime;
    GLfloat lastFrame = glfwGetTime();

    GLfloat dsum =0.0f;
    int frames = 0;
    int FPS;
    while(!glfwWindowShouldClose(window)){
        //Time calculation
        frames ++;
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        dsum += deltaTime;
        if(dsum>1){
            dsum = 0;
            FPS = frames;
            frames =0;
        }

        //Process
        GameName.ProcessInput(deltaTime);
        GameName.Update(deltaTime);

        // Rendering
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        GameName.Render();
        f.RenderText(std::to_string(FPS), 0, 0, 0.5, glm::vec3(1.0, 0.0, 0.0));
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, true);
    }
    if(key >= 0 && key <1024){
        if(action == GLFW_PRESS)
            GameName.Keys[key] = GL_TRUE;
        else if(action == GLFW_RELEASE)
            GameName.Keys[key] = GL_FALSE;

    }
}