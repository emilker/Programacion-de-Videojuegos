"""
New powerup for the assignation
"""

import settings

from src.powerups import PowerUp
from typing import TypeVar

from gale.timer import Timer

class TakeTheBall(PowerUp):

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x, y, 7)

    def take(self, play_state: TypeVar("PlayState")) -> None: # type: ignore
        self.active = False

        if play_state.sticky_paddle:
           return 

        play_state.sticky_paddle = True

        def finish_sticky_paddle():
            play_state.sticky_paddle = False
            play_state.fire_sticked_balls()
        
        Timer.after(5, finish_sticky_paddle)



        


    
    