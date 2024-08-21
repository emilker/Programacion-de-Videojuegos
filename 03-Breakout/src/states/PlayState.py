"""
ISPPJ1 2024
Study Case: Breakout

Author: Alejandro Mujica
alejandro.j.mujic4@gmail.com

This file contains the class to define the Play state.
"""

import random

import pygame

from gale.factory import AbstractFactory
from gale.state import BaseState
from gale.input_handler import InputData
from gale.text import render_text
from src.Shot import shot
from src.particle import particle
from gale.factory import Factory

import settings
import src.powerups


class PlayState(BaseState):
    def enter(self, **params: dict):
        self.level = params["level"]
        self.score = params["score"]
        self.lives = params["lives"]
        self.paddle = params["paddle"]
        self.balls = params["balls"]
        self.brickset = params["brickset"]
        self.live_factor = params["live_factor"]
        self.points_to_next_live = params["points_to_next_live"]
        self.points_to_next_grow_up = (
            self.score
            + settings.PADDLE_GROW_UP_POINTS * (self.paddle.size + 1) * self.level
        )
        self.powerups       = params.get("powerups", [])
        self.sticky_paddle  = params.get("sticky_paddle", False)
        self.sticked_balls  = params.get("sticked_balls", [])
        self.freeze_ball    = params.get("freeze_ball", False)
        self.shots          = params.get("shots", [])
        self.cannons_active = params.get("cannons_active", False)

        if not params.get("resume", False):
            self.balls[0].vx = random.randint(-80, 80)
            self.balls[0].vy = random.randint(-170, -100)
            settings.SOUNDS["paddle_hit"].play()
        self.powerups_abstract_factory = AbstractFactory("src.powerups")
    
    def fire_sticked_balls(self):
        for ball in self.sticked_balls:
            ball.vx = random.randint(-80, 80)
            ball.vy = random.randint(-170, -100)
            settings.SOUNDS["paddle_hit"].play()
        self.sticked_balls = []
        self.particle_instance = particle()

    def update(self, dt: float) -> None:
        deltas = [ball.x - self.paddle.x for ball in self.sticked_balls]
        self.paddle.update(dt)

        for i in range(len(self.sticked_balls)):
            self.sticked_balls[i].x = self.paddle.x + deltas[i]
        
        self.particle_instance.update(dt)
     
        if self.cannons:
            self.cannons[0].update(self.paddle.x - 3)  
            self.cannons[1].update(self.paddle.x + self.paddle.width - 7)


        for shot in self.shots:
            shot.update(dt) 
            # Check collision with world
            if shot.solve_world_boundaries():
                self.particle_instance.generate(shot.x)

            if not shot.collides(self.brickset):
                continue

            brick = self.brickset.get_colliding_brick(shot.get_collision_rect())

            if brick is None:
                continue

            brick.destroy()
            shot.active = False
            self.score += brick.score()

        for ball in self.balls:
            if ball in self.sticked_balls:
                continue
            
            if self.freeze_ball:
                continue

            ball.update(dt)
            ball.solve_world_boundaries()

            # Check collision with the paddle
            if ball.collides(self.paddle):
                if self.sticky_paddle:
                    ball.vx = 0
                    ball.vy = 0
                    self.sticked_balls.append(ball)
                else:    
                    settings.SOUNDS["paddle_hit"].stop()
                    settings.SOUNDS["paddle_hit"].play()
                    ball.rebound(self.paddle)
                    ball.push(self.paddle)

            # Check collision with brickset
            if not ball.collides(self.brickset):
                continue

            brick = self.brickset.get_colliding_brick(ball.get_collision_rect())

            if brick is None:
                continue

            brick.hit()
            self.score += brick.score()
            ball.rebound(brick)

            # Check earn life
            if self.score >= self.points_to_next_live:
                settings.SOUNDS["life"].play()
                self.lives = min(3, self.lives + 1)
                self.live_factor += 0.5
                self.points_to_next_live += settings.LIVE_POINTS_BASE * self.live_factor

            # Check growing up of the paddle
            if self.score >= self.points_to_next_grow_up:
                settings.SOUNDS["grow_up"].play()
                self.points_to_next_grow_up += (
                    settings.PADDLE_GROW_UP_POINTS * (self.paddle.size + 1) * self.level
                )
                self.paddle.inc_size()
            # Chance to generate two more balls
            if random.random() < 0.1:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("TwoMoreBall").create(
                        r.centerx - 8, r.centery - 8
                    )
                )
            
            #Chence to generate take the ball
            if not self.sticky_paddle and random.random() < 0.05:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("TakeTheBall").create(
                        r.centerx - 8, r.centery - 8
                    )
                )

            #Chence to generate Freeze Balls
            if not self.freeze_ball and random.random() < 0.02:
                r = brick.get_collision_rect()
                self.powerups.append(
                    self.powerups_abstract_factory.get_factory("FreezeBalls").create(
                        r.centerx - 8, r.centery - 8
                    )
                )

            #Generate cannons
            if not self.cannons:
                if random.random() < 1 and not self.cannons_active:
                    r = brick.get_collision_rect()
                    self.powerups.append(
                        self.powerups_abstract_factory.get_factory("Cannons").create(
                            r.centerx - 8, r.centery - 8
                        )
                    )  
                self.cannons_active = True 
        if self.cannons:
            if self.cannons[0].shots == 4:  
                self.cannons_active = False 

        # Removing all cannons that are not in play       
        self.cannons = [cannon for cannon in self.cannons if cannon.active]
        # Removing all shots that are not in play
        self.shots = [shot for shot in self.shots if shot.active]
        # Removing all balls that are not in play
        self.balls = [ball for ball in self.balls if ball.active]
        
        self.brickset.update(dt)

        if not self.balls:
            self.lives -= 1
            if self.lives == 0:
                self.state_machine.change("game_over", score=self.score)
            else:
                self.paddle.dec_size()
                self.state_machine.change(
                    "serve",
                    level=self.level,
                    score=self.score,
                    lives=self.lives,
                    paddle=self.paddle,
                    brickset=self.brickset,
                    points_to_next_live=self.points_to_next_live,
                    live_factor=self.live_factor,
                )

        # Update powerups
        for powerup in self.powerups:
            powerup.update(dt)

            if powerup.collides(self.paddle):
                powerup.take(self)

        # Remove powerups that are not in play
        self.powerups = [p for p in self.powerups if p.active]

        # Check victory
        if self.brickset.size == 1 and next(
            (True for _, b in self.brickset.bricks.items() if b.broken), False
        ):
            self.state_machine.change(
                "victory",
                lives=self.lives,
                level=self.level,
                score=self.score,
                paddle=self.paddle,
                balls=self.balls,
                points_to_next_live=self.points_to_next_live,
                live_factor=self.live_factor,
            )

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

        self.particle_instance.render(surface)

        for ball in self.balls:
            ball.render(surface)

        for cannon in self.cannons:
            cannon.render(surface)    

        for shot in self.shots:
            shot.render(surface)    

        for powerup in self.powerups:
            powerup.render(surface)

    def on_input(self, input_id: str, input_data: InputData) -> None:
        if input_id == "move_left":
            if input_data.pressed:
                self.paddle.vx = -settings.PADDLE_SPEED
            elif input_data.released and self.paddle.vx < 0:
                self.paddle.vx = 0
        elif input_id == "move_right":
            if input_data.pressed:
                self.paddle.vx = settings.PADDLE_SPEED
            elif input_data.released and self.paddle.vx > 0:
                self.paddle.vx = 0
        elif input_id == "enter" and input_data.pressed:
            self.fire_sticked_balls()
        elif input_id == "pause" and input_data.pressed:
            self.state_machine.change(
                "pause",
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
                sticky_paddle=self.sticky_paddle,
                sticked_balls=self.sticked_balls,
                freeze_ball=self.freeze_ball
            )
        elif input_id == "f" and input_data.pressed:
            if self.cannons:
                    if not self.shots:
                        self.shot_factory = Factory(shot)
                        a = self.shot_factory.create(self.paddle.x - 1, self.paddle.y)
                        self.shots.append(a)
                        b = self.shot_factory.create(self.paddle.x + self.paddle.width - 9, self.paddle.y)
                        self.shots.append(b)
                        for cannon in self.cannons:
                            cannon.shot()