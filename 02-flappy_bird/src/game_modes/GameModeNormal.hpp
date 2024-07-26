#pragma once

#include <Settings.hpp>

#include <src/game_modes/GameMode.hpp>

class GameModeNormal : public GameMode
{
public:
    void handle_input(const sf::Event&,const std::shared_ptr<Bird>) const noexcept override;

    bool should_close_log_pair() const noexcept override;

    bool generate_powerup() const noexcept override;

    float time_to_spawn_logs() const noexcept override;

    float gap_change() const noexcept override;
};

