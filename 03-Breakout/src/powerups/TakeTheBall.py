"""
New powerup for the assignation

By: Jesus Salas
"""
import settings

from src.powerups import PowerUp

class TakeTheBall(PowerUp):

    def __init__(self, x: int, y: int, frame: int) -> None:
        super().__init__(x, y, 7)
    
    