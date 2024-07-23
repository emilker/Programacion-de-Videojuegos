/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PlayingBaseState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PlayingState.hpp>
#include "PlayingState.hpp"

PlayingState::PlayingState(StateMachine* sm) noexcept
    : BaseState{sm}
{
 
}

void PlayingState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird, bool log, bool _powerup, int _score, float _time) noexcept
{
    world = _world;
    score = _score;
    powerup = _powerup;
    time = _time;

    if(log)
    {
        world->reset(true);/////sdfsdgfdsgfsdfsdfsad
    }

    if(powerup)
    {
        world->generate_powerup(true);
    }
   
    if (_bird == nullptr)
    {
        bird = std::make_shared<Bird>(
            Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2,
            Settings::BIRD_WIDTH, Settings::BIRD_HEIGHT
        );
    }
    else
    {
        bird = _bird;
    }
}

void PlayingState::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        bird->jump();
    }

    if (event.key.code == sf::Keyboard::Enter)
    {
        state_machine->change_state("pause", world, bird , false, powerup, score, time);
    }
}

void PlayingState::update(float dt) noexcept
{
  
    bird->update(dt);
    world->update(dt);  
    
    if (world->collides(bird->get_collision_rect()) && (powerup))
    {
        Settings::sounds["explosion"].play();
        Settings::sounds["hurt"].play();

        bird->reset(Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2);
        world->reset(true);
        
        state_machine->change_state("count_down", world, bird);
    }

    if (world->collides_powerup(bird->get_collision_rect()))
    { 
        powerup = false;
        Settings::music.stop();
        Settings::music_2.setLoop(true);
        Settings::music_2.play();
        world->generate_powerup(false);
        bird->change_texturer();
    }

    if (!powerup)
    {
        timer(dt);
    }

    if (world->update_scored(bird->get_collision_rect()))
    {
        ++score;
        Settings::sounds["score"].play();
    }
}

void PlayingState::render(sf::RenderTarget &target) const noexcept
{
    world->render(target);
    bird->render(target);
    render_text(target, 20, 10, "Score: " + std::to_string(score), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
    
    if (!powerup)
    {
        render_text(target, 20, 50, "Time: " + std::to_string(static_cast<int>(time)), Settings::FLAPPY_TEXT_SIZE,"flappy", sf::Color::White);
    }
}

void PlayingState::timer(float dt) noexcept
{
    time += -dt;

    if (time < 0)
    {
        Settings::music_2.stop();
        Settings::music.play();
        world->generate_powerup(true);
        bird->change_texturer();
        powerup = true;
        time = 20.f;
    }
}