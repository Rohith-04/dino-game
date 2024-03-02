#include "raylib.h"
#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define window_width 1366
#define window_height 500
#define MAX_OBSTACLES 1000

struct Ball{
    int x;
    int y;
    float size;
    int vel;
    int vel_x;
};

struct Rect{
    int x;
    int y;
    int width;
    int height;
};

int main() {
    InitWindow(window_width, window_height, "Game");
    SetTargetFPS(60);
    srand(time(0));

    struct Ball ball = {250, 280, 10.0f, 4, 7};

    struct Rect obs[MAX_OBSTACLES]; 

    for (int i = 0; i < MAX_OBSTACLES; i++) {       /*Initial Declaration of obstacles*/
        obs[i].x = 1300 + i * GetRandomValue(300, 500); 
        obs[i].y = 320;                         
        obs[i].width = 20;
        obs[i].height = (float)(GetRandomValue(40,130));
    }

    // Camera Initializations
    Vector2 camera_offset = {.x = 0, .y = 0};
    Vector2 camera_target = {.x = 0, .y = 0};
    Camera2D camera = {.offset = camera_offset, .target = camera_target, .rotation = 0.0f, .zoom = 1};

    int world_width = window_width * 1000;

    while (!WindowShouldClose()) {
        
        // Camera settings
        camera.offset.x = 100;
        camera.offset.y = 0;
        camera.target.x = ball.x;
        camera.target.y = 0;

        // Check for collision with the obstacle
        for(int i = 0; i < MAX_OBSTACLES; i++){
            if(CheckCollisionCircleRec((Vector2){ball.x , ball.y}, (float)ball.size, (Rectangle){obs[i].x , obs[i].y, obs[i].width, obs[i].height})){
                int score  = i;
                printf("The score obtained is %d\n", score);
                //sleep(2);
                CloseWindow();
                
            }
        }
        // Updating ball velocities and also keeping it on the platform
        int ball_bottom = ball.y + ball.size;
            if (ball_bottom >= 320) {
            ball.vel = 0;
            ball.y = 320 - ball.size;
        }
            if (ball_bottom == 320) {
                if (IsKeyPressed(KEY_SPACE)) {
                    ball.vel = -18;
                }   
        }
        ball.y += ball.vel;
        ball.vel += 1;
        ball.x += ball.vel_x; 

        BeginDrawing(); 
        ClearBackground(BLACK);
        DrawFPS(10, 10);               //Initialising all the modes
        BeginMode2D(camera);

        // Draw ground
        DrawLine(0, 320, world_width, 320, RAYWHITE);

        //Draw circle
        DrawCircle(ball.x, ball.y, ball.size, RAYWHITE);

        // Draw obstacle
        for(int i = 0; i < MAX_OBSTACLES; i++){
            DrawRectangle(obs[i].x, 320 - obs[i].height, obs[i].width, obs[i].height, RED);
        }

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}