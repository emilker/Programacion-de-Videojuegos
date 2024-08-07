"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the specialization of PowerUp to add two more ball to the game.
"""


from typing import TypeVar

from gale.factory import Factory

import settings
from src.cannon import cannon
from src.powerups.PowerUp import PowerUp


class Cannons(PowerUp):

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x, y, 3)
        self.connon_factory = Factory(cannon)
   
    def take(self, play_state: TypeVar("PlayState")) -> None:
        paddle = play_state.paddle
       
        
        a = self.connon_factory.create(paddle.x - 3, paddle.y)
        play_state.cannons.append(a)
        b = self.connon_factory.create(paddle.x + paddle.width - 7, paddle.y)
        play_state.cannons.append(b)

        settings.SOUNDS["paddle_hit"].stop()
        settings.SOUNDS["paddle_hit"].play()

        self.active = False
