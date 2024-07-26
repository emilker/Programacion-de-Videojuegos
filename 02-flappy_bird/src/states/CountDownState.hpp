/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class CountDownBaseState.
*/

#pragma once

#include <src/World.hpp>
#include <src/states/BaseState.hpp>

class CountDownState: public BaseState
{
public:
    CountDownState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> _world = nullptr, std::shared_ptr<Bird> _bird = nullptr, bool pause = false, bool timer_powerup = false, int _score = 0, float _time = 20.f) noexcept override;

    void update(float dt) noexcept override;

    void render(sf::RenderTarget& target) const noexcept override;

private:
    std::shared_ptr<World> world;
    std::shared_ptr<Bird> bird;
    int counter{3};
    float timer{0.f};
};
