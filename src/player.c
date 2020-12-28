#include "includes/player.h"
#include <stdio.h>

Player * Player_new() {
	Player * player = malloc(sizeof(Player));
	Player_init(player);
	return player;
}

void Player_init(Player * player) {
	player->position = 
		(Vector2)
		{
			MAP_TEXTURE_SCALE * (MAP_WIDTH/2), 
			MAP_TEXTURE_SCALE * (MAP_HEIGHT/2)
		};
	player->speed = 
		(Vector2)
		{
			200.f,
			200.f
		};
	player->acceleration = 1.75f;
	player->rotation = 0.f;
	player->size = PLAYER_SIZE;
	player->collider = Collider_new();
	player->color = WHITE;
	player->inventory = Inventory_new();
	player->sprinting = false;
	player->direction = 0;
	player->walkSprite = -1; 
	player->texture = LoadTexture("assets/sprite_player.png");
}

void Player_draw(Player * player) {
	DrawTextureRec(player->texture,
		(Rectangle){ 
			0.0f + ((player->walkSprite == -1) ? 0 : PLAYER_SIZE * floor(player->walkSprite/FRAME_RATE)),
			0.0f + PLAYER_SIZE * player->direction,
			PLAYER_SIZE,
			PLAYER_SIZE
		},
		(Vector2) {
			player->position.x - PLAYER_SIZE/2, 
			player->position.y - PLAYER_SIZE/2
		}, 
		WHITE);
}

void Player_control(Camera2D * camera, Player * player) {
	// Key switch (inventory)
    int keys[] = {KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE};
    for (int i = 0; i < 9; i++) if (IsKeyPressed(keys[i])) player->inventory->selected = keys[i] - KEY_ONE;

    if (!IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_RIGHT_CONTROL)) {
        // Mouse Wheel switch (inventory)
        player->inventory->selected -= GetMouseWheelMove();
        if (player->inventory->selected < 0) Player_switchItem(player, 0);
        if (player->inventory->selected > 8) Player_switchItem(player, 8);
    }

    // Update selected item (inventory draw the name of item)
    Player_switchItem(player, player->inventory->selected);

    // Is player sprinting ?
	player->sprinting = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

}

void Player_switchItem(Player * player, int selected) {
	player->inventory->selected = selected;
    if (player->inventory->items[selected].name != 0x0)
        sprintf(player->inventory->selectedText, "Selected: %s", player->inventory->items[selected].name);
}

void Player_move(GameMap * map, Player * player, float delta) {
// Save temporary the speed with sprinting calculated, if need to decrease (diagonal speed fix)
    Vector2 speed = {player->speed.x * ((player->sprinting) ? player->acceleration : 1.f) * delta,
                    player->speed.y * ((player->sprinting) ? player->acceleration : 1.f) * delta};

    // Check movements
    bool UP = (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));
    bool DOWN = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S));
    bool LEFT = (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    bool RIGHT = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D));

    // Limit diagonal movements
    if ((UP || DOWN) 
        && (LEFT || RIGHT)
        && !(LEFT && RIGHT))
    {
        // remove 30% of the saved speed
        speed = (Vector2) {(speed.x*0.7), (speed.y*0.7)};
    }

    Player_collisions(map, player, speed);

	// Note: Keyboard mapping is only QWERTY
    // UP AND DOWN
    if (UP && !player->collider->UP) player->position.y -= speed.y;
    if (DOWN && !player->collider->DOWN) player->position.y += speed.y;
    // RIGHT AND LEFT
    if (RIGHT && !player->collider->RIGHT) player->position.x += speed.x;
    if (LEFT && !player->collider->LEFT) player->position.x -= speed.x;

    // Anim sprite if moving
    if (UP | DOWN | LEFT | RIGHT)
    {
        player->walkSprite += 1;
        player->walkSprite %= FRAME_RATE*3;
    }

    // Change sprite direction
    if (LEFT) player->direction = 1;
    else if (RIGHT) player->direction = 0;

    Collider_reset(player->collider);
}

void Player_collisions(GameMap * map, Player * player, Vector2 speed) {
    // Check all collisions with 3 blocs width
    for (int i = -1; i <= 1; i++) {
        // Retrieve the player position in the map 2D Array
        int location[2] = {(int) (player->position.x/MAP_TEXTURE_SCALE), (int) (player->position.y/MAP_TEXTURE_SCALE)};

        // Retrieve current position of player
        Vector2 p = player->position;
        // NORTH
        /*
        [x, x, x]
        [ , p,  ]
        [ ,  ,  ]
        */
        Sprite ei = map->sprite[location[1]-1][location[0]+i];
        if (ei.blocking &&
            ei.rect.y + ei.rect.height <= p.y+PLAYER_SIZE/2 &&
            ei.rect.y + ei.rect.height >= p.y-PLAYER_SIZE/2 &&
            ei.rect.x <= p.x+PLAYER_SIZE/2-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-PLAYER_SIZE/2+speed.x)
        {
            player->collider->UP = true;
        }
        // EAST
        /*
        [ ,  , x]
        [ , p, x]
        [ ,  , x]
        */
        ei = map->sprite[location[1]+i][location[0]+1];
        if (ei.blocking &&
            ei.rect.x <= p.x+PLAYER_SIZE/2 &&
            ei.rect.x > p.x-PLAYER_SIZE/2 &&
            ei.rect.y <= p.y+PLAYER_SIZE/2-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-PLAYER_SIZE/2+speed.y)
        {
            player->collider->RIGHT = true;
        }
        // SOUTH
        /*
        [ ,  ,  ]
        [ , p,  ]
        [x, x, x]
        */
        ei = map->sprite[location[1]+1][location[0]+i];
        if (ei.blocking &&
            ei.rect.y <= p.y+PLAYER_SIZE/2 &&
            ei.rect.y > p.y-PLAYER_SIZE/2 &&
            ei.rect.x <= p.x+PLAYER_SIZE/2-speed.x &&
            ei.rect.x + ei.rect.width >= p.x-PLAYER_SIZE/2+speed.x)
        {
            player->collider->DOWN = true;
        }
        // WEST
        /*
        [x,  ,  ]
        [x, p,  ]
        [x,  ,  ]
        */
        ei = map->sprite[location[1]+i][location[0]-1];
        if (ei.blocking &&
            ei.rect.x + ei.rect.width <= p.x+PLAYER_SIZE/2 &&
            ei.rect.x + ei.rect.width >= p.x-PLAYER_SIZE/2 &&
            ei.rect.y <= p.y+PLAYER_SIZE/2-speed.y &&
            ei.rect.y + ei.rect.height >= p.y-PLAYER_SIZE/2+speed.y)
        {
            player->collider->LEFT = true;
        }
    }
}