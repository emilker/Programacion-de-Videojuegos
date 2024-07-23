/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class World.
*/

#pragma once

#include <list>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>

#include <src/Factory.hpp>
#include <src/LogPair.hpp>

class World
{
public:

    World(bool _generate_logs = false) noexcept;

    World(const World& world) = delete;

    World& operator = (World) = delete;

    void reset(bool _generate_logs) noexcept;

    bool generate_powerup(bool _generate_powerup)  noexcept;

    bool collides(const sf::FloatRect& rect) const noexcept;

    bool collides_powerup(const sf::FloatRect& rect) noexcept;

    bool update_scored(const sf::FloatRect& rect) noexcept;
 
    void update(float dt) noexcept;

    void create_PowerUp(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;
    
private:
    bool generate_logs;
    bool generate_PowerUp;

    sf::Sprite background;
    sf::Sprite ground;
    sf::Sprite powerup;

    float background_x{0.f};
    float ground_x{0.f};
    float powerup_x{0};
    float powerup_y{0};

    Factory<LogPair> log_factory;

    std::list<std::shared_ptr<LogPair>> logs;

    std::mt19937 rng;

    float logs_spawn_timer{0.f};
    float powerup_spawn_timer{0.f};
    float last_log_y{0.f};

    sf::FloatRect rec_powerup;
 
};
