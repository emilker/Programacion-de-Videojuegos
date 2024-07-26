/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class PlayingBaseState.
*/

#pragma once

#include <src/Bird.hpp>
#include <src/World.hpp>
#include <src/states/BaseState.hpp>

class PlayingState: public BaseState
{

public:
    PlayingState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> _world = nullptr, std::shared_ptr<Bird> _bird = nullptr, bool pause = false, bool _timer_powerup = false, int _score = 0, float _time = 20.f) noexcept override;

    void handle_inputs(const sf::Event& event) noexcept override;

    void update(float dt) noexcept override;

    void timer(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept override;

private:
    std::shared_ptr<Bird> bird;
    std::shared_ptr<World> world;
    int score{0};
    float time{20.f};
    bool timer_powerup{false};
};
