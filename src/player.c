#include "includes/player.h"

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