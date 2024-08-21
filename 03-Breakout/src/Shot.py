"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class shot.
"""

from typing import Any

import pygame

import settings

class shot:
    def __init__(self, x: int, y: int) -> None:
       
        self.x = x
        self.y = y
        self.width = 9
        self.height = 16

        self.vy = settings.SHOT_SPEED
        self.texture = settings.TEXTURES["shot"]
        
        self.active = True

    def get_collision_rect(self) -> pygame.Rect:
        return pygame.Rect(self.x, self.y, self.width, self.height)

    def solve_world_boundaries(self) -> bool:
        r = self.get_collision_rect()
        if r.bottom <= 0:
            self.active = False
            return True
        return False

    def collides(self, another: Any) -> bool:
        return self.get_collision_rect().colliderect(another.get_collision_rect())

    def update(self, dt: float) -> None:
            self.y += self.vy * dt

    def render(self, surface):
            surface.blit( self.texture, (self.x, self.y) )

  
