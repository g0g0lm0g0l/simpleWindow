#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

const int WIDTH = 1200;
const int HEIGHT = 800;


typedef struct Position {
    int x;
    int y;
} Position;

Position position = { WIDTH/2, HEIGHT/2 };
void movePoint()
{
    if (IsKeyDown(KEY_D)) {
	position.x += 10;
    } 
    if (IsKeyDown(KEY_W)) {
	position.y -= 10;
    } 
    if (IsKeyDown(KEY_S)) {
	position.y += 10;
    } 
    if (IsKeyDown(KEY_A)) {
	position.x -= 10;
    } 
    if (IsKeyPressed(KEY_SPACE)) {
	position.x = WIDTH/2;
	position.y = HEIGHT/2;
    }
    DrawCircleGradient(position.x, position.y, 50.0, RED, VIOLET);
    DrawCircleGradient(position.x-20, position.y, 20.0, PINK, BLACK);
    DrawCircleGradient(position.x+20, position.y, 20.0, PINK, BLACK);
}
void *throw_shit() {
    float yRec = position.y - 50.0 * 2;
    while (yRec >= 0.0) {
    	DrawRectangleGradientH(position.x, yRec-=0.001, 50, 60, BLACK, LIME);
    }
}

int main(void) 
{
    char *fps = NULL;
    InitWindow(WIDTH, HEIGHT, "EXEcute");
    SetTargetFPS(120);
    pthread_t thread_id;

    while (!WindowShouldClose()) {
	movePoint();
    	DrawFPS(10,10);
    	BeginDrawing();
	ClearBackground(BLACK);
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    	     pthread_create(&thread_id, NULL, throw_shit, NULL); 
	}
	EndDrawing();
	fps = NULL;
    }

    pthread_join(thread_id, NULL);
    CloseWindow();
    return 0;
}

