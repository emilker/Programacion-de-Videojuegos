import pygame

from gale.state import BaseState
from gale.input_handler import InputData
from gale.text import render_text
from gale.timer import Timer

import settings


class PauseState(BaseState):
    def enter(self, **params: dict) -> None:
        self.level = params["level"]
        self.paddle = params["paddle"]
        self.balls = params["balls"]
        self.cannons = params["cannons"]
        self.shots = params.get("shots", [])
        self.cannons_active = params["cannons_active"]
        self.brickset = params["brickset"]
        self.score = params["score"]
        self.lives = params["lives"]
        self.live_factor = params["live_factor"]
        self.points_to_next_live = params["points_to_next_live"]
        self.powerups = params["powerups"]
        self.sticky_paddle = params["sticky_paddle"]
        self.sticked_balls = params["sticked_balls"]
        self.freeze_ball   = params["freeze_ball"]
        settings.SOUNDS["pause"].play()
        Timer.pause()

    def render(self, surface: pygame.Surface) -> None:
        heart_x = settings.VIRTUAL_WIDTH - 120

        i = 0
        # Draw filled hearts
        while i < self.lives:
            surface.blit(
                settings.TEXTURES["hearts"], (heart_x, 5), settings.FRAMES["hearts"][0]
            )
            heart_x += 11
            i += 1

        # Draw empty hearts
        while i < 3:
            surface.blit(
                settings.TEXTURES["hearts"], (heart_x, 5), settings.FRAMES["hearts"][1]
            )
            heart_x += 11
            i += 1

        render_text(
            surface,
            f"Score: {self.score}",
            settings.FONTS["tiny"],
            settings.VIRTUAL_WIDTH - 80,
            5,
            (255, 255, 255),
        )

        self.brickset.render(surface)
        self.paddle.render(surface)

        render_text(
            surface,
            "Pause",
            settings.FONTS["medium"],
            settings.VIRTUAL_WIDTH // 2,
            settings.VIRTUAL_HEIGHT // 2,
            (255, 255, 255),
            center=True,
        )

    def on_input(self, input_id: str, input_data: InputData) -> None:
        if input_id == "pause" and input_data.pressed:
            self.state_machine.change(
                "play",
                level=self.level,
                score=self.score,
                lives=self.lives,
                paddle=self.paddle,
                balls=self.balls,
                cannons=self.cannons,
                shots=self.shots,
                cannons_active=self.cannons_active,
                brickset=self.brickset,
                points_to_next_live=self.points_to_next_live,
                live_factor=self.live_factor,
                powerups=self.powerups,
                resume=True,
                sticky_paddle=self.sticky_paddle,
                sticked_balls=self.sticked_balls,
                freeze_ball=self.freeze_ball
            )
