"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class Ball.
"""

import pygame

from src.Paddle import Paddle

import settings

class cannon:
    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y
        self.width = 10
        self.height = 17
        self.vx = 0
        self.shots = 0
        self.texture = settings.TEXTURES["cannon"]
        self.active = True

    def update(self, posicion:Paddle) -> None:
        self.x = posicion

    def shot(self) -> None:
        self.shots += 1
        if self.shots == 4:
            self.active = False  

    def render(self, surface: pygame.Surface):
        surface.blit(
            self.texture, (self.x, self.y)
        )