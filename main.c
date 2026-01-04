// #include <stdio.h>
#include "raylib.h"

#define HEIGHT 600
#define WIDTH 900
#define THICKNESS 3

#define MASS_WIDTH 150
#define MASS_HEIGHT 100

#define SPRING_TOP (HLINE_PAD - MASS_HEIGHT - ((double) THICKNESS / 2) + 10)
#define SPRING_BOTTOM (HLINE_PAD - 10)

//padding
#define HLINE_PAD (HEIGHT * (0.66))
#define VLINE_PAD 100
#define MASS_PAD (VLINE_PAD + 400)
#define HSPRING_PAD ((double) MASS_HEIGHT / 2)

#define NO_OF_SPRINGS 8

void draw_spring(float mass_offset) {
    float distance = mass_offset - VLINE_PAD;
    int n = distance / NO_OF_SPRINGS;

    Vector2 spring_start = {VLINE_PAD, (HLINE_PAD - HSPRING_PAD)};
    Vector2 spring_end = {mass_offset, (HLINE_PAD - HSPRING_PAD)};

    int springs[NO_OF_SPRINGS];
    for (int i = 0; i < NO_OF_SPRINGS; i++) {
        springs[i] = VLINE_PAD + (i * n);
    }

    DrawLineEx(
        spring_start,
        (Vector2) {springs[1], SPRING_TOP},
        THICKNESS,
        YELLOW
    );

    if ((NO_OF_SPRINGS - 1) % 2 == 0) {
        DrawLineEx(
            (Vector2) {springs[NO_OF_SPRINGS - 1], SPRING_BOTTOM},
            spring_end,
            THICKNESS,
            GREEN
        );
    } else {
        DrawLineEx(
            (Vector2) {springs[NO_OF_SPRINGS - 1], SPRING_TOP},
            spring_end,
            THICKNESS,
            BLUE
        );
    }

    for (int i = 1; i < NO_OF_SPRINGS - 1; i++) {
        if (i % 2 == 0) {
            DrawLineEx(
                (Vector2) {springs[i], SPRING_BOTTOM},
                (Vector2) {springs[i+1], SPRING_TOP},
                THICKNESS,
                GREEN
            );
        } else {
            DrawLineEx(
                (Vector2) {springs[i], SPRING_TOP},
                (Vector2) {springs[i+1], SPRING_BOTTOM},
                THICKNESS,
                BLUE
            );
        }
    }
}

void draw_planes(void) {
    Vector2 start_h = {VLINE_PAD, HLINE_PAD};
    Vector2 end_h = {WIDTH, HLINE_PAD};

    Vector2 start_v = {VLINE_PAD, 0};
    Vector2 end_v = {VLINE_PAD, HEIGHT};

    DrawLineEx(start_h, end_h, THICKNESS, RAYWHITE);
    DrawLineEx(start_v, end_v, THICKNESS, RAYWHITE);
}

void draw_mass(float mass_offset) {
        Rectangle rec = {
            // MASS_PAD, // intial mass placement
            mass_offset,
            HLINE_PAD - MASS_HEIGHT - ((double) THICKNESS / 2),
            MASS_WIDTH,
            MASS_HEIGHT
        };

        DrawRectangleRec(rec, RED);
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "raylib");

    float mass_offset = VLINE_PAD;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Spring Simulation!", WIDTH/3, HEIGHT/4, 30, GREEN);
        draw_planes();
        draw_mass(mass_offset);
        mass_offset += 0.1;
        draw_spring(mass_offset);
        EndDrawing();
    }

    return 0;
}
