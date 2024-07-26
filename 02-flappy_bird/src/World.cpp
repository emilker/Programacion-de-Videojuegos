/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class World.
*/

#include <Settings.hpp>
#include <src/World.hpp>

#include <src/game_modes/GameMode.hpp>
#include "World.hpp"

World::World(bool _generate_logs) noexcept
    : generate_logs{_generate_logs}, background{Settings::textures["background"]}, ground{Settings::textures["ground"]},powerup{Settings::textures["PowerUp"]},
      logs{}
{
    ground.setPosition(0, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);
    std::uniform_int_distribution<int> dist(0, 80);
    last_log_y = -Settings::LOG_HEIGHT + dist(Settings::RNG) + 20;
}

void World::reset(bool _generate_logs) noexcept
{
    generate_logs = _generate_logs;
    for (auto log_pair: logs)
    {
        log_factory.remove(log_pair);
    }
    logs.clear();
}

bool World::generate_powerup(bool _generate_powerup) noexcept
{
    return generate_PowerUp =_generate_powerup;
}

bool World::collides(const sf::FloatRect& rect) const noexcept
{
    if (rect.top + rect.height >= Settings::VIRTUAL_HEIGHT)
    {
        return true;
    }
    
    for (auto log_pair: logs)
    {
        if (log_pair->collides(rect))
        {
            return true;
        }
    }

    return false;
}

bool World::update_scored(const sf::FloatRect& rect) noexcept
{
    for (auto log_pair: logs)
    {
        if (log_pair->update_scored(rect))
        {
            return true;
        }
    }

    return false;
}

bool World::collides_powerup(const sf::FloatRect &rect) noexcept
{
    if (generate_PowerUp)
    {
        rec_powerup = sf::FloatRect(powerup_x,powerup_y,Settings::POWERUP_WIDTH,Settings::POWERUP_HEIGHT);
    
        if(rec_powerup.intersects(rect))
        { 
            generate_PowerUp = false;
            return true;
        }    
        return false;
    }
    return false;
}

void World::update(float dt) noexcept
{
    if (generate_logs)
    {
        logs_spawn_timer += dt;

        if (logs_spawn_timer >= time_change_between_logs)
        {
            logs_spawn_timer = 0.f;

            time_change_between_logs = Settings::GAME_MODE->time_to_spawn_logs();

            std::uniform_int_distribution<int> dist{-20, 20};
            float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(Settings::RNG), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));

            last_log_y = y;

            logs.push_back(log_factory.create(Settings::VIRTUAL_WIDTH, y, Settings::GAME_MODE->should_close_log_pair()));
        }
    }

    if (generate_PowerUp)
    {
        create_PowerUp(dt);
    }
    else
    {
        powerup_spawn_timer = 0.f;
        powerup_y = 0;
        powerup_x = 0 ;        
    }

    powerup.setPosition(powerup_x, powerup_y);

    background_x += -Settings::BACK_SCROLL_SPEED * dt;

    if (background_x <= -Settings::BACKGROUND_LOOPING_POINT)
    {
        background_x = 0;
    }

    background.setPosition(background_x, 0);

    ground_x += -Settings::MAIN_SCROLL_SPEED * dt;

    if (ground_x <= -Settings::VIRTUAL_WIDTH)
    {
        ground_x = 0;
    }

    ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

    for (auto it = logs.begin(); it != logs.end(); )
    {
        if ((*it)->is_out_of_game())
        {
            auto log_pair = *it;
            log_factory.remove(log_pair);
            it = logs.erase(it);
            
        }
        else
        {
            (*it)->update(dt);
            ++it;
        }
    }
}

void World::render(sf::RenderTarget& target) const noexcept
{
    target.draw(background);

    for (const auto& log_pair: logs)
    {
        log_pair->render(target);
    }

    target.draw(ground);

    sf::Vector2f position = powerup.getPosition();

    if((position.x != 0) && (position.y != 0) )
    {
        target.draw(powerup);
    }
}

void World::create_PowerUp(float dt) noexcept
{
    powerup_spawn_timer += dt;

    if(powerup_spawn_timer >= Settings::TIME_TO_SPAWN_POWERUP)
    {
        powerup_spawn_timer = 0.f;

        std::uniform_int_distribution<int> dist_powerup(60, 240);
        powerup_y = dist_powerup(rng);
    
        powerup_x = Settings::VIRTUAL_WIDTH ;
           
        rec_powerup = sf::FloatRect(powerup_x, powerup_y,Settings::POWERUP_WIDTH, Settings::POWERUP_HEIGHT);

        while (collides(rec_powerup)) // Ajustar la posición X del powerup para evitar colisiones
        {
            powerup_x += Settings::POWERUP_WIDTH;
            rec_powerup = sf::FloatRect(powerup_x, powerup_y, Settings::POWERUP_WIDTH, Settings::POWERUP_HEIGHT);
        }
    }

    powerup_x += -Settings::MAIN_SCROLL_SPEED * dt;
}