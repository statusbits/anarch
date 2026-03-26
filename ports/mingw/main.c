/**
* @file     main.c
* @brief    Anarch front end for Win32 (mingw).
*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <minifb.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
    static uint8_t const keymap[SFG_KEY_COUNT] = {
        0x26,   //  0 - SFG_KEY_UP                              [Up]
        0x27,   //  1 - SFG_KEY_RIGHT                           [Right]
        0x28,   //  2 - SFG_KEY_DOWN                            [Down]
        0x25,   //  3 - SFG_KEY_LEFT                            [Left]
        'X',    //  4 - SFG_KEY_A (fire, confirm)               [X]
        0x08,   //  5 - SFG_KEY_B (cancel)                      [Backspace]
        'V',    //  6 - SFG_KEY_C                               [V]
        0x20,   //  7 - SFG_KEY_JUMP                            [Space]
        'Z',    //  8 - SFG_KEY_STRAFE_LEFT                     [Z]
        'C',    //  9 - SFG_KEY_STRAFE_RIGHT                    [C]
        0x09,   // 10 - SFG_KEY_MAP                             [Tab]
        'F',    // 11 - SFG_KEY_TOGGLE_FREELOOK                 [F]
        'D',    // 12 - SFG_KEY_NEXT_WEAPON                     [D]
        'A',    // 13 - SFG_KEY_PREVIOUS_WEAPON                 [A]
        0x0D,   // 14 - SFG_KEY_MENU                            [Enter]
        'S',    // 1S - 5FG_KEY_CYCLE_WEAPON                    [S]
    };

    char * key_status;

    if (key >= SFG_KEY_COUNT) {
        return 0;
    }

    key_status = mfb_keystatus();

    return key_status[keymap[key]];
}

// ---------------------------------------------------------------------------
void SFG_getMouseOffset(int16_t *x, int16_t *y)
{
}

// ---------------------------------------------------------------------------
uint32_t SFG_getTimeMs(void)
{
    return GetTickCount();
}

// ---------------------------------------------------------------------------
void SFG_sleepMs(uint16_t gameTimeMs)
{
    Sleep(gameTimeMs);
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
