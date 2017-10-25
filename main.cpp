//
// Created by rostard on 16.10.17.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <zconf.h>

#include "font.h"
#include "game.h"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int button, int action, int modes);

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
    glfwSetMouseButtonCallback(window, mouse_callback);
    return 0;
}


void CreateServer(){
    std::cerr<<"create"<<std::endl;
    sockaddr_in addr;
    addr.sin_port = htons(12345);
    addr.sin_family = AF_INET;
    inet_aton("0.0.0.0",&addr.sin_addr);


    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int err =bind(fd, (sockaddr*)&addr, sizeof(addr));
    if(err == -1){
        std::cerr<<"Bind error: "<<strerror(errno)<<std::endl;
        exit(EXIT_FAILURE);
    }
    err = listen(fd, SOMAXCONN);
    if(err == -1){
        std::cerr<<"Listen error: "<<strerror(errno)<<std::endl;
        exit(EXIT_FAILURE);
    }
    int client = accept(fd, nullptr, nullptr);
    char buf[1024];
    int l;
    while(l = recv(client, buf, 1024, 0)){
        std::stringstream ss(buf);
        int x, y, n;
        ss>>x>>y>>n;
        for(int i = 0; i<1024;i ++)buf[i]=' ';
        if(x+y!=n)continue;
        GameName.secondPos.x = x;
        GameName.secondPos.y = y;

    }
}

void ConnectToServer(){
    std::cerr<<"connect"<<std::endl;
    sockaddr_in addr;
    addr.sin_port = htons(12345);
    addr.sin_family = AF_INET;
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //int err =bind(fd, (sockaddr*)&addr, sizeof(addr));

    inet_aton("127.0.0.1", &addr.sin_addr);

    int res = connect(fd, (sockaddr*)&addr, sizeof(addr));
    if(res == -1){
        std::cerr<<"error connect: "<<strerror(errno)<<std::endl;
    }
    while(true){
        std::stringstream ss;
        ss<<GameName.ownPos.x<<" "<<GameName.ownPos.y<<" ";
        int n = GameName.ownPos.x + GameName.ownPos.y;
        ss<<n;

        send(fd, ss.str().c_str(), ss.str().length(), 0);

    }
}

int main(){
    Init();

    Font f("fonts/arial.ttf");

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);

    GameName.Init();

    GLfloat deltaTime;
    GLfloat lastFrame = glfwGetTime();

    GLfloat dsum =0.0f;
    int frames = 0;
    int FPS;


    //std::thread net(CreateServer);

    std::thread net(ConnectToServer);

    Shader simple = ResourceManager::LoadShader("shaders/simple.vs.glsl", "shaders/simple.fs.glsl", nullptr, "simple");

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
        glClearColor(0.3, 0.0, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        GameName.Render();
        f.RenderText(std::to_string(FPS), 0, 0, 0.5, glm::vec3(1.0, 0.0, 0.0));
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    //net.join();
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, true);
    }
    if(key >= 0 && key <1024){
        //std::cerr<<key<<std::endl;
        if(action == GLFW_PRESS)
            GameName.Keys[key] = GL_TRUE;
        else if(action == GLFW_RELEASE)
            GameName.Keys[key] = GL_FALSE;

    }
}

void mouse_callback(GLFWwindow* window, int button, int action, int modes){
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
}