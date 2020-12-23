#include "includes/player.h"
#include "includes/map.h"

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
	player->collider = 
		(Vector2)
		{
			1.f,
			1.f
		}; 
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
			0.0f + ((player->walkSprite == -1) ? 0:40 * floor(player->walkSprite/FRAME_RATE)),
			0.0f + 40 * player->direction,
			40.0f,
			40.0f
		},
		(Vector2) {
			player->position.x - 20, 
			player->position.y - 20
		}, 
		WHITE);
}