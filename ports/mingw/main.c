/**
* @file     main.c
* @brief    Anarch front end for Win32 (mingw).
*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <minifb.h>

// Game configuration settings
#define SFG_SCREEN_RESOLUTION_X 240
#define SFG_SCREEN_RESOLUTION_Y 192
#define SFG_BACKGROUND_BLUR     1
#define SFG_DITHERED_SHADOW     1
#define SFG_FPS                 30
#include "game.h"

#define GFX_SCALE               2   // Scaling factor

// RGB565 frame buffer.
static uint16_t frame_buffer[SFG_SCREEN_RESOLUTION_X * SFG_SCREEN_RESOLUTION_Y];

// ---------------------------------------------------------------------------
static inline void SFG_setPixel(uint16_t x, uint16_t y, uint8_t colorIndex)
{
    frame_buffer[y * SFG_SCREEN_RESOLUTION_X + x] = paletteRGB565[colorIndex];
}

// ---------------------------------------------------------------------------
int8_t SFG_keyPressed(uint8_t key)
{
    return 0;
}

// ---------------------------------------------------------------------------
void SFG_getMouseOffset(int16_t *x, int16_t *y)
{
}

// ---------------------------------------------------------------------------
uint32_t SFG_getTimeMs(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
void SFG_sleepMs(uint16_t gameTimeMs)
{
}

// ---------------------------------------------------------------------------
void SFG_playSound(uint8_t soundIndex, uint8_t volume)
{
}

// ---------------------------------------------------------------------------
void SFG_setMusic(uint8_t value)
{
}

// ---------------------------------------------------------------------------
void SFG_processEvent(uint8_t event, uint8_t data)
{
}

// ---------------------------------------------------------------------------
void SFG_save(uint8_t data[SFG_SAVE_SIZE])
{
}

// ---------------------------------------------------------------------------
uint8_t SFG_load(uint8_t data[SFG_SAVE_SIZE])
{
    return 0;
}

// ---------------------------------------------------------------------------
// Application entry point
int main(int argc, char **argv)
{
    // Create display window
    if (!mfb_open("anarch", SFG_SCREEN_RESOLUTION_X, SFG_SCREEN_RESOLUTION_Y, GFX_SCALE)) {
        // Error: cannot create display window
        return 1;
    }

    // Initialize game
    SFG_init();

    // Game loop
    for (;;) {
        SFG_mainLoopBody();
        if (mfb_update(frame_buffer, SFG_FPS) != 0) {
            // Exit
            break;
        }
    }

    // Clean up
    mfb_close();

    return 0;
}
