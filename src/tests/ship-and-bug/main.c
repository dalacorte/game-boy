#include <gb/gb.h>
#include <stdio.h>
#include "main-character.c"
#include "test-sprites.c"

struct mainCharacter ship;
struct mainCharacter bug;
UBYTE spriteSize = 8;

void performantDelay(UINT8 numloops)
{
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

UBYTE checkCollisions(struct mainCharacter *one, struct mainCharacter *two)
{
    return (one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height);
}

void moveGameCharacter(struct mainCharacter *character, UINT8 x, UINT8 y)
{
    move_sprite(character->spriteIds[0], x, y);
    move_sprite(character->spriteIds[1], x + spriteSize, y);
    move_sprite(character->spriteIds[2], x, y + spriteSize);
    move_sprite(character->spriteIds[3], x + spriteSize, y + spriteSize);
}

void setShip()
{
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    set_sprite_tile(0, 0);
    ship.spriteIds[0] = 0;
    set_sprite_tile(1, 1);
    ship.spriteIds[1] = 1;
    set_sprite_tile(2, 2);
    ship.spriteIds[2] = 2;
    set_sprite_tile(3, 3);
    ship.spriteIds[3] = 3;

    moveGameCharacter(&ship, ship.x, ship.y);
}

void setBug()
{
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;

    set_sprite_tile(4, 4);
    bug.spriteIds[0] = 4;
    set_sprite_tile(5, 5);
    bug.spriteIds[1] = 5;
    set_sprite_tile(6, 6);
    bug.spriteIds[2] = 6;
    set_sprite_tile(7, 7);
    bug.spriteIds[3] = 7;

    moveGameCharacter(&bug, bug.x, bug.y);
}

void main()
{
    set_sprite_data(0, 8, TestSprites);
    setShip();
    setBug();

    SHOW_SPRITES;
    DISPLAY_ON;

    while (!checkCollisions(&ship, &bug))
    {
        if (joypad() & J_LEFT)
        {
            ship.x -= 2;
            moveGameCharacter(&ship, ship.x, ship.y);
        }
        if (joypad() & J_RIGHT)
        {
            ship.x += 2;
            moveGameCharacter(&ship, ship.x, ship.y);
        }

        bug.y += 5;

        if (bug.y >= 144)
        {
            bug.y = 0;
            bug.x = ship.x;
        }

        moveGameCharacter(&bug, bug.x, bug.y);

        performantDelay(5);
    }

    printf("GAME OVER");
}