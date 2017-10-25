//
// Created by rostard on 19.10.17.
//

#ifndef GAME_OPENGL_SPRITE_RENDERER_H
#define GAME_OPENGL_SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"

class SpriteRenderer{
public:
    SpriteRenderer(Shader &shader);

    ~SpriteRenderer();

    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.f, 10.f), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    GLuint quadVAO;

    void InitRenderData();
};

#endif //GAME_OPENGL_SPRITE_RENDERER_H
