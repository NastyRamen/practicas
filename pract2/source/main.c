/*
	Pract2 for the AEV subject
	--Touch screen counter game:--
	---Touch the screen as many times as possible--- 
	---within the 3 second time limit!---
*/

#include <3ds.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	gfxInitDefault();

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	//Read the system timer

	//Centered text describing game
	printf("\x1b[16;17H\x1b[47;30mSCREEN TAP GAME\x1b[0m");	
	printf("\x1b[18;7H\x1b[47;30mTap the screen as quickly as possible!\x1b[0m");
	printf("\x1b[20;20H\x1b[47;30m3 SECONDS\x1b[0m");
	//"Menu" options on top left corner
	printf("\x1b[0;0HPress A to exit.");
	printf("\x1b[1;0HTouch Screen position:");
	printf("\x1b[3;0HNumber of Touch Screen clicks:");

	//Touch Screen click counter
	int counter = 0;

	//Timer in seconds
	double timer = 300;
	
	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//Exit when user hits A
		if(keysHeld()&KEY_A)break;

		//Timer countdown
		if(timer > 0) timer--;
		
		touchPosition touch;

		//Read the touch screen coordinates 
		hidTouchRead(&touch);
		
		//Add to touch counter
		if(keysDown()&KEY_TOUCH && timer > 0)counter++;
		if(keysDown()&KEY_TOUCH && timer <= 0)counter = counter;

		//Print the touch screen coordinates
		printf("\x1b[2;0H%03d; %03d", touch.px, touch.py);

		//Print the screen tap counter
		printf("\x1b[4;0H%03d", counter);

		//Print timer
		printf("\x1b[22;15H\x1b[47;30mTIMER: %f\x1b[0m", timer);
		
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	return 0;
}

