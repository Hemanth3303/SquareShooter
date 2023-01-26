#include "raylib.h"

int main(int argc, char** argv){
	InitWindow(640, 480, "Hello Raylib");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}