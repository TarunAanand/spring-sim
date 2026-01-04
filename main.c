// #include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "raylib.h"

#define HEIGHT 600
#define WIDTH 900
#define THICKNESS 3

#define MASS_WIDTH 150
#define MASS_HEIGHT 100

#define SPRING_TOP (HLINE_PAD - MASS_HEIGHT - ((float) THICKNESS / 2) + 10)
#define SPRING_BOTTOM (HLINE_PAD - 10)

//padding
#define HLINE_PAD (HEIGHT * (0.66))
#define VLINE_PAD 100
#define MASS_PAD (VLINE_PAD + 400)
#define HSPRING_PAD ((float) MASS_HEIGHT / 2)

#define NO_OF_SPRINGS 8

// temporary values
#define MIN_DISTANCE (VLINE_PAD + 70)
#define MAX_DISTANCE (VLINE_PAD + 500)

float bounds_helper(int spring_length, float angle) {
    int side = ((float) (180 - angle) / 2);

    float rad = (angle / 2) * (M_PI / 180);
    float base = 2 * spring_length * sin(rad);

    float distance = base * ((float) NO_OF_SPRINGS / 2);
    // printf("distance = %.3f\n", distance);
    return distance;
}

Vector2 calc_bounds(void) {
    int springs = NO_OF_SPRINGS;
    int spring_length = MASS_HEIGHT - ((float) THICKNESS / 2);
    // float distance = VLINE_PAD + 200;
    // float n = distance / NO_OF_SPRINGS;
    // float c = fmod(distance, NO_OF_SPRINGS);

    const float min_angle = 10;
    const float max_angle = 90;

    float min_distance = bounds_helper(spring_length, min_angle);
    float max_distance = bounds_helper(spring_length, max_angle);

    char x[64], y[64];
    sprintf(x, "min_angle -> %.3f", min_distance);
    sprintf(y, "max_angle -> %.3f", max_distance);
    DrawText(x, WIDTH - 180, 10, 18, BLUE);
    DrawText(y, WIDTH - 180, 30, 18, BLUE);

    Vector2 distances = {min_distance, max_distance};
    return distances;
}

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
        RAYWHITE
    );

    if ((NO_OF_SPRINGS - 1) % 2 == 0) {
        DrawLineEx(
            (Vector2) {springs[NO_OF_SPRINGS - 1], SPRING_BOTTOM},
            spring_end,
            THICKNESS,
            RAYWHITE
        );
    } else {
        DrawLineEx(
            (Vector2) {springs[NO_OF_SPRINGS - 1], SPRING_TOP},
            spring_end,
            THICKNESS,
            RAYWHITE
        );
    }

    for (int i = 1; i < NO_OF_SPRINGS - 1; i++) {
        if (i % 2 == 0) {
            DrawLineEx(
                (Vector2) {springs[i], SPRING_BOTTOM},
                (Vector2) {springs[i+1], SPRING_TOP},
                THICKNESS,
                RAYWHITE
            );
        } else {
            DrawLineEx(
                (Vector2) {springs[i], SPRING_TOP},
                (Vector2) {springs[i+1], SPRING_BOTTOM},
                THICKNESS,
                RAYWHITE
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
    float mass_offset = VLINE_PAD + 200; //300
    bool decreasing = true;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Spring Simulation!", WIDTH/3, HEIGHT/4, 30, GREEN);
        draw_planes();
        draw_mass(mass_offset);

        Vector2 distances = calc_bounds();
        if (decreasing && mass_offset >= (VLINE_PAD + distances.x)) { // 300 > 170 (min)
            mass_offset -= 0.1;
        } else {
            decreasing = false;
        }

        if (!decreasing && mass_offset <= (VLINE_PAD +distances.y)) { // 300 < 600 (max)
            mass_offset += 0.1;
        } else {
            decreasing = true;
        }

        draw_spring(mass_offset);
        EndDrawing();
    }

    return 0;
}
