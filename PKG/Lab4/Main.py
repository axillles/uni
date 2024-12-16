import pygame
import time

WIDTH, HEIGHT = 800, 600
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Растровые алгоритмы PKG")


def draw_axes():
    pygame.draw.line(screen, BLACK, (0, HEIGHT // 2), (WIDTH, HEIGHT // 2), 1)
    pygame.draw.line(screen, BLACK, (WIDTH // 2, 0), (WIDTH // 2, HEIGHT), 1)

    for x in range(0, WIDTH, 50):
        pygame.draw.line(screen, BLACK, (x, HEIGHT // 2 - 5), (x, HEIGHT // 2 + 5), 1)
        if x != WIDTH // 2:
            label = font.render(str(x - WIDTH // 2), True, BLACK)
            screen.blit(label, (x - 10, HEIGHT // 2 + 10))

    for y in range(0, HEIGHT, 50):
        pygame.draw.line(screen, BLACK, (WIDTH // 2 - 5, y), (WIDTH // 2 + 5, y), 1)
        if y != HEIGHT // 2:  # Avoid labeling the origin twice
            label = font.render(str(HEIGHT // 2 - y), True, BLACK)
            screen.blit(label, (WIDTH // 2 + 10, y - 10))


def dda_algorithm(x0, y0, x1, y1, color):
    dx = x1 - x0
    dy = y1 - y0
    steps = max(abs(dx), abs(dy))
    x_inc = dx / steps
    y_inc = dy / steps

    x, y = x0, y0
    for _ in range(steps):
        pygame.draw.rect(screen, color, (round(x), round(y), 1, 1))
        x += x_inc
        y += y_inc


def bresenham_line(x0, y0, x1, y1, color):
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx - dy

    while True:
        pygame.draw.rect(screen, color, (x0, y0, 1, 1))
        if x0 == x1 and y0 == y1:
            break
        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x0 += sx
        if e2 < dx:
            err += dx
            y0 += sy


def bresenham_circle(x0, y0, radius, color):
    x = 0
    y = radius
    d = 3 - 2 * radius
    while y >= x:
        for i in range(-x, x + 1):
            pygame.draw.rect(screen, color, (x0 + i, y0 + y, 1, 1))
            pygame.draw.rect(screen, color, (x0 + i, y0 - y, 1, 1))
            pygame.draw.rect(screen, color, (x0 + y, y0 + i, 1, 1))
            pygame.draw.rect(screen, color, (x0 - y, y0 + i, 1, 1))
        if d <= 0:
            d += 4 * x + 6
        else:
            d += 4 * (x - y) + 10
            y -= 1
        x += 1


def incremental_algorithm(x0, y0, x1, y1, color):
    dx = x1 - x0
    dy = y1 - y0
    slope = dy / dx if dx != 0 else 0

    if abs(slope) <= 1:
        y = y0
        for x in range(x0, x1 + 1):
            pygame.draw.rect(screen, color, (x, round(y), 1, 1))
            y += slope
    else:
        x = x0
        slope = dx / dy if dy != 0 else 0
        for y in range(y0, y1 + 1):
            pygame.draw.rect(screen, color, (round(x), y, 1, 1))
            x += slope


font = pygame.font.Font(None, 24)

screen.fill(WHITE)
draw_axes()

start_time = time.time()
dda_algorithm(100, 100, 200, 200, RED)
dda_time = time.time() - start_time

start_time = time.time()
bresenham_line(100, 300, 200, 400, RED)
bresenham_line_time = time.time() - start_time

start_time = time.time()
bresenham_circle(400, 300, 50, RED)
bresenham_circle_time = time.time() - start_time

start_time = time.time()
incremental_algorithm(100, 200, 200, 250, RED)
incremental_time = time.time() - start_time

text = font.render(f"DDA time: {dda_time:.6f}", True, BLACK)
screen.blit(text, (10, 10))
text = font.render(f"Bresenham line time: {bresenham_line_time:.6f}", True, BLACK)
screen.blit(text, (10, 40))
text = font.render(f"Bresenham circle time: {bresenham_circle_time:.6f}", True, BLACK)
screen.blit(text, (10, 70))
text = font.render(f"Incremental time: {incremental_time:.6f}", True, BLACK)
screen.blit(text, (10, 100))

pygame.display.flip()

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

pygame.quit()