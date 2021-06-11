#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "background-map.c"
#include "background-sprites.c"
#include "window-map.c"
#include "pikachu-sprites.c"

void main()
{
    font_t min_font;
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    set_win_tiles(0, 0, 5, 1, windowMap);
    move_win(7, 120);
    SHOW_WIN;

    set_sprite_data(0, 2, pikachu);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    set_bkg_data(37, 7, backgroundTiles); // starts 37
    set_bkg_tiles(0, 0, 40, 18, backgroundMap);
    SHOW_BKG;

    DISPLAY_ON;

    // specific order
    NR52_REG = 0x80; // 1000 0000 -> turns on sound
    NR50_REG = 0x77; // set the volume for left and right channel
    NR51_REG = 0xFF; // 1111 1111 -> select all chanels

    while (1)
    {
        UBYTE joypad_state = joypad();

        if (joypad_state)
        {
            NR10_REG = 0x16;
            NR11_REG = 0x40;
            NR12_REG = 0x73;
            NR13_REG = 0x00;
            NR14_REG = 0xC3;

            delay(100);
        }

        scroll_bkg(1, 0);

        switch (joypad())
        {
        case J_LEFT:
            scroll_sprite(0, -10, 0);
            break;
        case J_RIGHT:
            scroll_sprite(0, 10, 0);
            break;
        case J_UP:
            scroll_sprite(0, 0, -10);
            break;
        case J_DOWN:
            scroll_sprite(0, 0, 10);
            break;
        }

        delay(100);
    }
}