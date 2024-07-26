#include <src/Bird.hpp>

#include <Settings.hpp>

#include <src/game_modes/GameModeNormal.hpp>

void GameModeNormal::handle_input(const sf::Event& event,const std::shared_ptr<Bird> bird) const noexcept
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        bird->jump();
    }
}

bool GameModeNormal::should_close_log_pair() const noexcept 
{
    return false;
}

bool GameModeNormal::generate_powerup() const noexcept
{
    return false;
}

float GameModeNormal::time_to_spawn_logs() const noexcept
{
    return Settings::TIME_TO_SPAWN_LOGS;  
}

float GameModeNormal::gap_change() const noexcept
{
    return Settings::LOGS_GAP;
}