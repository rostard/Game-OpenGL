#ifndef GAME_OPENGL_GAMEOBJECT_H
#define GAME_OPENGL_GAMEOBJECT_H

#include <glm/glm.hpp>
#include "texture.h"
#include "sprite_renderer.h"

class GameObject{
public:
    glm::vec2 Position, Size;

    Texture2D Sprite;

    GameObject();

    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
    virtual void Draw(SpriteRenderer &renderer);
};

#endif //GAME_OPENGL_GAMEOBJECT_H
