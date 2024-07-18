/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class PowerUp.
*/

#pragma once

#include <SFML/Graphics.hpp>
// bool crear
class PowerUp
{
public:
    
    PowerUp(float _x, float _y, float w, float h) noexcept;

    sf::FloatRect get_collision_rect() const noexcept;

    void update(float dt) noexcept;
   
    void render(sf::RenderTarget& target) const noexcept;

private:
    float x;
    float y;
    float width;
    float height;
    bool crear;
    sf::Sprite sprite;
};