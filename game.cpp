//
// Created by rostard on 16.10.17.
//

#include <glad/glad.h>
#include <iostream>
#include "game.h"
#include "resource_manager.h"


Game::Game(GLint width, GLint height) {
    this->Width = width;
    this->Height = height;
}

Game::~Game() {
    delete Renderer;
}


void Game::Init() {
    std::cerr<<"Game init"<<std::endl;
    // Load shaders
    ResourceManager::LoadShader("shaders/sprite.vs.glsl", "shaders/sprite.fs.glsl", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                                      static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").use().setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);

    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // Load textures
    ResourceManager::LoadTexture("resources/awesomeface.png", GL_TRUE, "face");

}



void Game::ProcessInput(GLfloat dt) {
    if(Keys[265]){
        ownPos.y--;
    }
    if(Keys[264]){
        ownPos.y++;
    }
    if(Keys[263]){
        ownPos.x--;
    }
    if(Keys[262]){
        ownPos.x++;
    }
}

void Game::Update(GLfloat dt) {

}

void Game::Render() {
    Texture2D tex = ResourceManager::GetTexture("face");

    Renderer->DrawSprite(tex, ownPos, glm::vec2(300, 300));
    Renderer->DrawSprite(tex, secondPos, glm::vec2(100, 100));
}
