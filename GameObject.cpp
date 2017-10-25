//
// Created by rostard on 24.10.17.
//

#include "GameObject.h"


GameObject::GameObject(): Position(0, 0), Size(1, 1), Sprite() {
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite): Position(pos), Size(size), Sprite(sprite) {
}

void GameObject::Draw(SpriteRenderer &renderer) {
    renderer.DrawSprite(Sprite, Position, Size);
}



