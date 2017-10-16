//
// Created by rostard on 16.10.17.
//

#ifndef GAME_OPENGL_GAME_H
#define GAME_OPENGL_GAME_H

#include <glad/glad.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game{
public:
    GameState State;
    GLboolean Keys[1024];
    GLint Width, Height;

    Game(GLint width, GLint height);
    ~Game();

    void Init();

    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};


#endif //GAME_OPENGL_GAME_H
