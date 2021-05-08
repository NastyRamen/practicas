// Simple citro2d sprite drawing example
// Images borrowed from:
//   https://kenney.nl/assets/space-shooter-redux
#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SPRITES 4

//Screen bot 
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
//Screen top
#define CHARACTER_SPEED 2

// Simple sprite struct
typedef struct
{
	C2D_Sprite spr;
	float dx, dy; // velocity
} Sprite;

C2D_TextBuf g_staticBuf, g_dynamicBuf;
C2D_Text g_staticText[4];


static C2D_SpriteSheet spriteSheet;
static Sprite sprites[MAX_SPRITES];
static size_t numSprites = MAX_SPRITES;
Sprite *sprite = &sprites[MAX_SPRITES];

//---------------------------------------------------------------------------------
static void initSprites()
{
	//---------------------------------------------------------------------------------
	srand(time(NULL));

	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		//puntero a la estructura Sprite
		Sprite *sprite = &sprites[i];	
		if (i != 3 )
		{ // Random image, position, rotation and speed
			C2D_SpriteFromSheet(&sprite->spr, spriteSheet, i);
			C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
			C2D_SpriteSetPos(&sprite->spr, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
			C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
			sprite->dx = rand() * 4.0f / RAND_MAX - 2.0f;
			sprite->dy = rand() * 4.0f / RAND_MAX - 2.0f;
		}
		if (i == 3){
			C2D_SpriteFromSheet(&sprite->spr, spriteSheet, i);
			C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
			C2D_SpriteSetPos(&sprite->spr, 200.0f, 110.0f);
			sprite->dx = 200.0f;
			sprite->dy = 110.0f;
		}
		
	}
}

static void movePlayer(u32 kHeld)
{
	Sprite *sprite = &sprites[3];


	if (kHeld & KEY_UP)
	{
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	
	sprite->dy = sprite->dy- 1;
	
			
		
	}else
	if (kHeld & KEY_DOWN)
	{
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	
	sprite->dy = sprite->dy + 1;

	
	}
	else if (kHeld & KEY_RIGHT)
	{
	
	
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	
	sprite->dx = sprite->dx + 1;
	}
	else if (kHeld & KEY_LEFT)
	{
	
	
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	
	sprite->dx = sprite->dx - 1;
	}
	

}

 
	//---------------------------------------------------------------------------------
	static void moveSprites()
{
	//---------------------------------------------------------------------------------
	for (size_t i = 0; i < numSprites; i++)
	{
		Sprite *sprite = &sprites[i];
		
		if ( i != 3)
		{
			C2D_SpriteMove(&sprite->spr, sprite->dx, sprite->dy);
			C2D_SpriteRotateDegrees(&sprite->spr, 1.0f);

			// Check for collision with the screen boundaries
			if ((sprite->spr.params.pos.x < sprite->spr.params.pos.w / 2.0f && sprite->dx < 0.0f) ||
				(sprite->spr.params.pos.x > (SCREEN_WIDTH - (sprite->spr.params.pos.w / 2.0f)) && sprite->dx > 0.0f))
				sprite->dx = -sprite->dx;

			if ((sprite->spr.params.pos.y < sprite->spr.params.pos.h / 2.0f && sprite->dy < 0.0f) ||
				(sprite->spr.params.pos.y > (SCREEN_HEIGHT - (sprite->spr.params.pos.h / 2.0f)) && sprite->dy > 0.0f))
				sprite->dy = -sprite->dy;
		}
	}
}



static void sceneInit(void)
{
	// Create two text buffers: one for static text, and another one for
	// dynamic text - the latter will be cleared at each frame.
	g_staticBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	g_dynamicBuf = C2D_TextBufNew(4096);
	// Parse the static text strings
	C2D_TextParse(&g_staticText[1], g_staticBuf, "Codoñer, Nieves | Garcés, Antoni | Padró, Cristina");
	// Optimize the static text strings
	C2D_TextOptimize(&g_staticText[1]);
}

static void sceneRender(float size)
{
	C2D_TextBufClear(g_dynamicBuf);
	// Draw static text strings
	C2D_DrawText(&g_staticText[1], C2D_AtBaseline | C2D_WithColor, 16.0f, 210.0f, 0.5f, 0.5f, 0.75f, C2D_Color32f(2.0f,0.0f,0.0f,3.0f));
	// Generate and draw dynamic text
	char buf[160];
	C2D_Text dynText;

	snprintf(buf,sizeof(buf),"Sprites: %zu/%u", numSprites, MAX_SPRITES);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter| C2D_WithColor, 200.0f, 90.0f, 0.5f, 0.5f, 0.6f,C2D_Color32f(1.0f,2.0f,3.0f,2.0f));

	snprintf(buf,sizeof(buf),"CPU:     %6.2f%%", C3D_GetProcessingTime() * 6.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter| C2D_WithColor, 200.0f, 110.0f, 0.5f, 0.5f, 0.7f,C2D_Color32f(1.0f,2.0f,3.0f,2.0f));

	snprintf(buf,sizeof(buf),"GPU:     %6.2f%%", C3D_GetDrawingTime() * 6.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter| C2D_WithColor, 200.0f, 130.0f, 0.5f, 0.5f, 0.8f,C2D_Color32f(1.0f,2.0f,3.0f,2.0f));

		snprintf(buf,sizeof(buf),"CmdBuf:  %6.2f%%", C3D_GetCmdBufUsage() * 100.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter| C2D_WithColor, 200.0f, 150.0f, 0.5f, 0.5f, 0.9f,C2D_Color32f(1.0f,2.0f,3.0f,2.0f));


}

C2D_TextBuf g_staticBuf;
C2D_Text g_staticText[4];

//---------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	//---------------------------------------------------------------------------------
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	//consoleInit(GFX_TOP, NULL);

	// Create screens
	C3D_RenderTarget *bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet)
		svcBreak(USERBREAK_PANIC);

	// Initialize sprites
	initSprites();
	/*
	printf("\x1b[8;1HPress Up to increment sprites");
	printf("\x1b[9;1HPress Down to decrement sprites");
	*/


	C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	sceneInit();
	float size = 0.5f;

	
	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		
		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		//hidKeysHeld returns information about which buttons have are held down in this frame
		u32 kHeld = hidKeysHeld();


		if (kDown & KEY_START) break;
		movePlayer(kHeld);
		moveSprites();
		// Render the scene bot
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bot, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(bot);

		for (size_t i = 0; i < numSprites; i++)
			C2D_DrawSprite(&sprites[i].spr);
		C3D_FrameEnd(0);
		//Render the scene top

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
		C2D_SceneBegin(top);
		sceneRender(size);
		
		
	}

	// Delete graphics
	C2D_SpriteSheetFree(spriteSheet);

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
