"""
ISPPJ1 2024
Study Case: Match-3

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class Tile.
"""

import pygame

import settings


class Tile:
    def __init__(self, i: int, j: int, color: int, variety: int) -> None:
        self.i = i
        self.j = j
        self.x = self.j * settings.TILE_SIZE
        self.y = self.i * settings.TILE_SIZE
        self.color = color
        self.variety = variety
        self.powerup_4 = False
        self.powerup_5 = False
        self.use_powerup = False
        self.alpha_surface = pygame.Surface(
            (settings.TILE_SIZE, settings.TILE_SIZE), pygame.SRCALPHA
        )

    def render(self, surface: pygame.Surface, offset_x: int, offset_y: int) -> None:
        
        self.alpha_surface.blit(
        settings.TEXTURES["tiles"],
        (0, 0),
        settings.FRAMES["tiles"][self.color][self.variety],
        )
        
        pygame.draw.rect(
            self.alpha_surface,
            (34, 32, 52, 200),
            pygame.Rect(0, 0, settings.TILE_SIZE, settings.TILE_SIZE),
            border_radius=7,
        )
        surface.blit(self.alpha_surface, (self.x + 2 + offset_x, self.y + 2 + offset_y))
        
        if self.powerup_4:
            self.use_powerup = True
            self.variety = 0
            if self.variety > 5:
                self.variety = 6
            surface.blit(
            settings.TEXTURES["tiles_powerup_4"],
            (self.x + offset_x, self.y + offset_y),
            settings.FRAMES2["tiles_powerup_4"][self.color][self.variety],
            )
        elif self.powerup_5:
            self.variety = 0
            if self.variety > 5:
                self.variety = 6
            surface.blit(
            settings.TEXTURES["tiles_powerup_5"],
            (self.x + offset_x, self.y + offset_y),
            settings.FRAMES3["tiles_powerup_5"][self.color][self.variety],
            )
        else:
                surface.blit(
                settings.TEXTURES["tiles"],
                (self.x + offset_x, self.y + offset_y),
                settings.FRAMES["tiles"][self.color][self.variety],
                )

