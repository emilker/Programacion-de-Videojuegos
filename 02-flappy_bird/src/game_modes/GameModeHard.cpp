#include <src/Bird.hpp>

#include <Settings.hpp>

#include <src/game_modes/GameModeHard.hpp>
<<<<<<< HEAD
=======
#include "GameModeHard.hpp"
>>>>>>> part-2-b

void GameModeHard::handle_input(const sf::Event& event,const std::shared_ptr<Bird> bird) const noexcept
{
    if (event.key.code == sf::Keyboard::W && event.type == sf::Event::KeyPressed)
   {
        bird->jump();
   }

   if (event.key.code == sf::Keyboard::A) 
   {
        if (event.type == sf::Event::KeyPressed)
        {
            bird->move(-Settings::HORIZONTAL_MOVEMENT);
        }
        else
        {
            bird->move(0);
        }
   }

   if (event.key.code == sf::Keyboard::D) 
   {
        if (event.type == sf::Event::KeyPressed)
        {
            bird->move(Settings::HORIZONTAL_MOVEMENT);
        }
        else
        {
            bird->move(0);
        }
   }
}

bool GameModeHard::should_close_log_pair() const noexcept 
{
    std::uniform_int_distribution<int> dist{1, 4};

    if (dist(Settings::RNG) == 4)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

bool GameModeHard::generate_powerup() const noexcept
{
    return true;
>>>>>>> part-2-b
}

float GameModeHard::time_to_spawn_logs() const noexcept
{
    std::uniform_real_distribution<float> dist{0.5f, 2.5f};

    return dist(Settings::RNG);
}

float GameModeHard::gap_change() const noexcept
{
    std::uniform_real_distribution<float> dist{70.f, 120.f};

    return dist(Settings::RNG);
}