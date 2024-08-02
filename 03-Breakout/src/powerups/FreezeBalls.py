"""
PowerUp Freeze 
"""

import settings

from src.powerups import PowerUp
from typing import TypeVar

from gale.timer import Timer

class FreezeBalls(PowerUp):

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x, y, 6)

    def take(self, play_state: TypeVar("PlayState")) -> None: # type: ignore
        self.active = False
        
        settings.SOUNDS["freeze_sound"].stop()
        settings.SOUNDS["freeze_sound"].play()

        if play_state.freeze_ball:
           return 
        
        play_state.freeze_ball = True

        def finish_freeze_ball():
            play_state.freeze_ball = False

        Timer.after(5, finish_freeze_ball)