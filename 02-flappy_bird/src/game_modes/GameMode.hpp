#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class Bird;

class GameMode
{
public:
    virtual void handle_input(const sf::Event&,const std::shared_ptr<Bird>) const noexcept = 0;

    virtual bool should_close_log_pair() const noexcept = 0;

    virtual bool generate_powerup() const noexcept = 0;

    virtual float time_to_spawn_logs() const noexcept = 0;

    virtual float gap_change() const noexcept = 0;

    virtual ~GameMode();
};