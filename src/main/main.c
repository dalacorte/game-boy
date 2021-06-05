#include <gb/gb.h>
#include <stdio.h>
#include "PikachuSprites.c"

void main()
{
    UINT8 spriteIndex = 0;

    set_sprite_data(0, 2, Pikachu);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while (1)
    {
        if (spriteIndex == 0)
        {
            spriteIndex = 1;
        }
        else
        {
            spriteIndex = 0;
        }

        set_sprite_tile(0, spriteIndex);
        delay(1000);
    }
}