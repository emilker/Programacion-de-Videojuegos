/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class LogPair.
*/

#include <Settings.hpp>
#include <src/LogPair.hpp>

LogPair::LogPair(float _x, float _y, bool _should_close) noexcept
    : x{_x}, y{_y}, should_close{_should_close},
      top{x, y + Settings::LOG_HEIGHT, true},
      bottom{x, y + Settings::GAME_MODE->gap_change() + Settings::LOG_HEIGHT, false}
{

}

bool LogPair::collides(const sf::FloatRect& rect) const noexcept
{
    return top.get_collision_rect().intersects(rect) || bottom.get_collision_rect().intersects(rect);
}

void LogPair::update(float dt) noexcept
{
    x += -Settings::MAIN_SCROLL_SPEED * dt;

    next_y_top = top.get_y();
    next_y_bottom = bottom.get_y();

    if (should_close)
    {
        float dy = Settings::LOG_MOVEMENT * dt;
        
        if (top.get_collision_rect().intersects(bottom.get_collision_rect()))
        {
            Settings::sounds["sound_log"].play();
            dy_sign = -1.f;
        }
        else if (top.get_y() <= y + Settings::LOG_HEIGHT && 
                bottom.get_y() >= y + Settings::LOGS_GAP + Settings::LOG_HEIGHT)
        {
            dy_sign = 1.f;
        }

        next_y_top += dy * dy_sign;
        next_y_bottom -= dy * dy_sign;
    }
    else
    {
        if (top.get_y() + 40 >= bottom.get_y())
        {
            next_y_top -= 120.f;
            next_y_bottom += 120.f;
        }

        if (top.get_y() <= 15.f)
        {
            next_y_top = 25.f;
        }
        
    }

    top.update(x, next_y_top);
    bottom.update(x, next_y_bottom);
}

void LogPair::render(sf::RenderTarget& target) const noexcept
{
    top.render(target);
    bottom.render(target);
}

bool LogPair::is_out_of_game() const noexcept
{
    return x < -Settings::LOG_WIDTH;
}

bool LogPair::update_scored(const sf::FloatRect& rect) noexcept
{
    if (scored)
    {
        return false;
    }

    if (rect.left > x + Settings::LOG_WIDTH)
    {
        scored = true;
        return true;
    }

    return false;
}

void LogPair::reset(float _x, float _y, bool _should_close) noexcept
{
    x = _x;
    y = _y;
    should_close = _should_close;
    scored = false;
}