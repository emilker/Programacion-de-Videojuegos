/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PowerUp.
*/
#include <Settings.hpp>
#include <src/PowerUp.hpp>

PowerUp::PowerUp(float _x, float _y, float w, float h) noexcept
    : x{_x}, y{_y}, width{w}, height{h}, sprite{Settings::textures["PowerUp"]}
{    
     
}

void PowerUp::update(float dt) noexcept
{
    x += -Settings::MAIN_SCROLL_SPEED * dt;
}

void PowerUp::render(sf::RenderTarget& target) const noexcept
{
    target.draw(sprite);
}
