#include "raylib.h"
#include <math.h>
#include <stdio.h>


#define SCR_HEIGHT 800
#define SCR_WIDTH 1200

void CalculatePoints(Vector2 *points, Vector2 o, int divs, int r)
{
	float theta = 2 * PI / divs;

	for(int i = 0; i < divs; i++)
	{
		points[i].x = o.x + r * cosf(theta * i);
		points[i].y = o.y + r * sinf(theta * i);
	}
}

int main ()
{
	// Create the window and OpenGL context
	InitWindow(SCR_WIDTH, SCR_HEIGHT, "Cardioid Animation");

	Vector2 origin = {SCR_WIDTH/2, SCR_HEIGHT/2};
	int divisions = 500;
	int radius = 400;
	double mult = 1;
	
	Vector2 points[divisions];

	int alpha = 255 - (divisions / 10); // make sure alpha isnt too bright at high divisions
    if (alpha < 50) alpha = 50;

	// find all the segments of the cardioid
	CalculatePoints(points, origin, divisions, radius);
	
	// loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// multicolour pulse effect
		float rpulse = (sinf(GetTime() * 2.0f) + 1.0f) / 2.0f; 
		float gpulse = ((sinf(GetTime() * 2.5f + PI/3) + 1.0f) / 2.0f);
		float bpulse = (sinf(GetTime() * 3.0f + 2 * PI/3) + 1.0f) / 2.0f;
        Color multicolour = { (unsigned char)(255 * rpulse), (unsigned char)(255 * gpulse), (unsigned char)(255 * bpulse), alpha };

		// Drawing
		BeginDrawing();

		// draw border circle
		DrawCircleLinesV(origin, radius, multicolour);

		// Draw the lines between points
        for (int i = 0; i < divisions; i++)
		{
			int nextIndex = (int)(mult * i) % divisions;

			DrawLineEx(points[i], points[nextIndex], 1, multicolour);
		}

		// steadily increment multiplier for the cool effect
		mult += 0.01;


		// Clean frame
		ClearBackground(BLACK);
		EndDrawing();

	}


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
