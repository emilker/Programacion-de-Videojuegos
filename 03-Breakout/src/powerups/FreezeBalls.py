"""
PowerUp Freeze 
"""

import settings

from src.powerups import PowerUp
from typing import TypeVar

from gale.timer import Timer

class FreezeBalls(PowerUp):

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x, y, 6, 40)

    def take(self, play_state: TypeVar("PlayState")) -> None:  # type: ignore
        self.active = False
        
        settings.SOUNDS["freeze_sound"].stop()
        settings.SOUNDS["freeze_sound"].play()
        
        play_state.freeze_ball = True