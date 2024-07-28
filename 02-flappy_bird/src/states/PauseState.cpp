/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PauseBaseState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PauseState.hpp>
#include "PauseState.hpp"

PauseState::PauseState(StateMachine* sm) noexcept
    : BaseState{sm}
{

}

void PauseState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird,  bool pause, bool _timer_powerup, int _score, float _time) noexcept
{
    world = _world;
    bird = _bird;
    score = _score;
    timer_powerup =_timer_powerup;
    time = _time;
}

void PauseState::handle_inputs(const sf::Event& event) noexcept
{
   if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        state_machine->change_state("playing", world, bird, false, timer_powerup, score, time);
    }
    
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
    {
        if( Settings::music_2.Playing )
        {
            Settings::music_2.stop();
            Settings::music.play();
        }
        state_machine->change_state("title");
    }
}

void PauseState::render(sf::RenderTarget &target) const noexcept
{
    world->render(target);
    bird->render(target);
    render_text(target, 20, 10, "Score: " + std::to_string(score), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2.5, "PAUSE", Settings::FLAPPY_TEXT_SIZE, "font", sf::Color::White, true);

    render_text(target, Settings::VIRTUAL_WIDTH / 2, 2 * Settings::VIRTUAL_HEIGHT / 4, "Press enter to return to the game", Settings::MEDIUM_TEXT_SIZE, "font", sf::Color::White, true);

    render_text(target, Settings::VIRTUAL_WIDTH / 2, 2 * Settings::VIRTUAL_HEIGHT / 3, "Press X to return to the beginning", Settings::MEDIUM_TEXT_SIZE, "font", sf::Color::White, true);


    if (timer_powerup)
    {
        render_text(target, 20, 50, "Time: " + std::to_string(static_cast<int>(time)), Settings::FLAPPY_TEXT_SIZE,"flappy", sf::Color::White);
    }
}
