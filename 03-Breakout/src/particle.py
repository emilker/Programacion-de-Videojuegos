"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class Ball.
"""

import pygame

from gale.particle_system import ParticleSystem

import settings


class particle:
    def __init__(self) -> None:
       
        self.particle_system = ParticleSystem( 0, 0, 64)
        self.particle_system.set_life_time(0.2, 0.4)
        self.particle_system.set_linear_acceleration(-0.3, 0.5, 0.3, 1)
        self.particle_system.set_area_spread(1, 7)

    def generate(self, x: int) -> None:
        settings.SOUNDS["hurt"].play()
        self.particle_system.x_mean = x
        self.particle_system.set_colors([(217, 87, 99, 10), (217, 87, 99, 50)])
        self.particle_system.generate()
        
    def update(self, dt: float) -> None:
        self.particle_system.update(dt)       

    def render(self, surface):
        self.particle_system.render(surface)

  
