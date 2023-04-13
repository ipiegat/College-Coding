import pygame
import time
import random


(width, height) = (1000, 500)
screen = pygame.display.set_mode((width, height))
pygame.display.flip()

up_pressed = False
right_pressed = False
left_pressed = False
down_pressed = False


class Boom:
    def __init__(self, pos):
        self.pos = list(pos)
        self.color = (255, 255 * random.random(), 255 * random.random())
        self.v = list(((random.random() - 0.5) * 500, (random.random() - 0.2) * 800))
        self.r = 0
        self.max_r = 100 * random.random()
        self.age = 0

    def step(self, delta_t):
        self.age += delta_t
        self.r = self.age * self.max_r
        self.pos[0] -= self.v[0] * delta_t
        self.pos[1] -= self.v[1] * delta_t
        self.v[1] -= delta_t * 50 * (50 - self.r)

    def is_done(self):
        return self.age >= 1

    def draw(self, screen):
        alpha = max(0, 1 - self.age)
        pygame.draw.circle(
            screen, tuple(c * alpha for c in self.color), self.pos, self.r
        )


class Circle:
    def __init__(self, x=100, y=100, r=20):
        self.x = x
        self.y = y
        self.r = r


c_y = 100
c_x = 100
c_r = 20

pellet_locs = []
booms = []


def make_pellet():
    px = 50 + random.random() * (width - 100)
    py = 50 + random.random() * (height - 100)
    return (px, py)


for _ in range(10):
    pellet_locs.append(make_pellet())


last_t = time.time()
running = True
while running:
    delta_t = time.time() - last_t
    last_t = time.time()

    """
    parse user input (figure out state of keyboard)
    update game state (taking into account input state)
    render game
    """
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.dict["key"] == pygame.K_UP:
                up_pressed = True
            if event.dict["key"] == pygame.K_RIGHT:
                right_pressed = True
            if event.dict["key"] == pygame.K_LEFT:
                left_pressed = True
            if event.dict["key"] == pygame.K_DOWN:
                down_pressed = True

        if event.type == pygame.KEYUP:
            if event.dict["key"] == pygame.K_UP:
                up_pressed = False
            if event.dict["key"] == pygame.K_RIGHT:
                right_pressed = False
            if event.dict["key"] == pygame.K_LEFT:
                left_pressed = False
            if event.dict["key"] == pygame.K_DOWN:
                down_pressed = False

    if up_pressed:
        c_y -= 300 * delta_t

    if right_pressed:
        c_x += 300 * delta_t

    if left_pressed:
        c_x -= 300 * delta_t

    if down_pressed:
        c_y += 300 * delta_t

    c_x = max(0, min(width, c_x))
    c_y = max(0, min(height, c_y))

    for i in range(len(pellet_locs)):
        p_x, p_y = pellet_locs[i]
        d = ((c_x - p_x) ** 2 + (c_y - p_y) ** 2) ** 0.5
        if d < c_r - 10:
            for _ in range(10):
                booms.append(Boom(pellet_locs[i]))
            pellet_locs[i] = make_pellet()
            c_area = 3.14 * (c_r) ** 2
            p_area = 3.14 * (10) ** 2
            c_area += p_area
            c_r = (c_area / (3.14)) ** (0.5)

    for b in booms:
        b.step(delta_t)

    i = 0
    while i < len(booms):
        if booms[i].is_done():
            del booms[i]
        else:
            i += 1

    pygame.draw.rect(screen, (0, 0, 0), pygame.Rect(0, 0, width, height))
    for b in booms:
        b.draw(screen)
    for p_loc in pellet_locs:
        pygame.draw.circle(screen, (255, 0, 0), p_loc, 10)

    pygame.draw.circle(screen, (255, 255, 255), (c_x, c_y), c_r)
    pygame.display.update()

"""<Event(768-KeyDown {'unicode': '', 'key': 1073741903, 'mod': 0, 'scancode': 79, 'window': None})>
<Event(769-KeyUp {'unicode': '', 'key': 1073741903, 'mod': 0, 'scancode': 79, 'window': None})>
<Event(768-KeyDown {'unicode': '', 'key': 1073741904, 'mod': 0, 'scancode': 80, 'window': None})>
<Event(769-KeyUp {'unicode': '', 'key': 1073741904, 'mod': 0, 'scancode': 80, 'window': None})>
<Event(768-KeyDown {'unicode': '', 'key': 1073741905, 'mod': 0, 'scancode': 81, 'window': None})>
<Event(769-KeyUp {'unicode': '', 'key': 1073741905, 'mod': 0, 'scancode': 81, 'window': None})>
<Event(768-KeyDown {'unicode': '', 'key': 1073741906, 'mod': 0, 'scancode': 82, 'window': None})>
<Event(769-KeyUp {'unicode': '', 'key': 1073741906, 'mod': 0, 'scancode': 82, 'window': None})>"""
