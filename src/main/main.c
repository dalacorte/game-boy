#include <gb/gb.h>
#include <stdio.h>
#include "background-map.c"
#include "background-sprites.c"
#include "pikachu-sprites.c"

void main()
{
    set_sprite_data(0, 2, pikachu);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    set_bkg_data(0, 7, backgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, backgroundMap);
    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
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