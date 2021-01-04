#include "includes/gameiaentities.h"
#include "includes/env.h"

GameIAEntities * GameIAEntities_new(int id, Texture2D texture, Vector2 position, Vector2 speed, float radiusZone, bool visible) {
	GameIAEntities * iaEntity = malloc(sizeof(GameIAEntities));
	iaEntity->id = id;
	iaEntity->texture = texture;
	iaEntity->position = position;
	iaEntity->speed = speed;
	iaEntity->radiusZone = radiusZone > (PATHFINDING_SIZE/2) * MAP_TEXTURE_SCALE ? (PATHFINDING_SIZE/2) * MAP_TEXTURE_SCALE: radiusZone;
	iaEntity->active = false;
	iaEntity->visible = visible;
	iaEntity->clock = 0;
	GameIAEntities_resetPath(iaEntity);
	iaEntity->pathIndex = 0;
	return iaEntity;
}

void GameIAEntities_resetPath(GameIAEntities * gameIAEntity) {
	for (int i = 0; i < PATH_BUFFER_LENGTH; i++) {
		gameIAEntity->path[i][0] = -1;
		gameIAEntity->path[i][1] = -1;
	}
	gameIAEntity->pathIndex = 0;
}

void GameIAEntities_update(Game * game, GameIAEntities * gameIAEntity, float delta) {
	if (!gameIAEntity->visible) return;
	if (!gameIAEntity->active && CheckCollisionPointCircle(game->player->position, gameIAEntity->position, gameIAEntity->radiusZone)) {
		gameIAEntity->active = true;
		pathfinding(gameIAEntity->path, ((int) gameIAEntity->position.x / MAP_TEXTURE_SCALE) -(PATHFINDING_SIZE/2), ((int) gameIAEntity->position.y / MAP_TEXTURE_SCALE) -(PATHFINDING_SIZE/2), game->map, (Vector2) {game->player->position.x-(PLAYER_SIZE/2), game->player->position.y-(PLAYER_SIZE/2)});
	}
	gameIAEntity->active = CheckCollisionPointCircle(game->player->position, gameIAEntity->position, gameIAEntity->radiusZone);

	if (gameIAEntity->active) {
		gameIAEntity->clock++;

		if (gameIAEntity->clock >= CLOCK_MAX) {
			gameIAEntity->clock = 0;
			GameIAEntities_resetPath(gameIAEntity);
			pathfinding(gameIAEntity->path, ((int) gameIAEntity->position.x / MAP_TEXTURE_SCALE) -(PATHFINDING_SIZE/2), ((int) gameIAEntity->position.y / MAP_TEXTURE_SCALE) -(PATHFINDING_SIZE/2), game->map, (Vector2) {game->player->position.x-(PLAYER_SIZE/2), game->player->position.y-(PLAYER_SIZE/2)});
		}


		if ((gameIAEntity->pathIndex < PATH_BUFFER_LENGTH) 
			& (gameIAEntity->path[gameIAEntity->pathIndex][0] != -1))
		{
			float y = (gameIAEntity->path[gameIAEntity->pathIndex][0] * MAP_TEXTURE_SCALE) + (MAP_TEXTURE_SCALE / 2);
			float x = (gameIAEntity->path[gameIAEntity->pathIndex][1] * MAP_TEXTURE_SCALE) + (MAP_TEXTURE_SCALE / 2);
			gameIAEntity->position.y += (y - gameIAEntity->position.y) >= 0 ? 1 : -1 * gameIAEntity->speed.y * delta;
			gameIAEntity->position.x += (x - gameIAEntity->position.x) >= 0 ? 1 : -1 * gameIAEntity->speed.x * delta;

			if ((float) 
			(sqrt(
				pow(gameIAEntity->position.x - x, 2) 
				+ 
				pow(gameIAEntity->position.y - y, 2))
			) <= 8.f) gameIAEntity->pathIndex++;
				// 8 is 1/4 of size of a cell
		}
	}
}

void GameIAEntities_control(Game * game, GameIAEntities * gameIAEntity) {
	if (!gameIAEntity->visible) return;
	
	if (!game->player->invulnerable 
		& gameIAEntity->active
		& ((float) 
			(sqrt(
				pow(gameIAEntity->position.x - game->player->position.x, 2) 
				+ 
				pow(gameIAEntity->position.y - game->player->position.y, 2))
			) <= 48.f)) 
		{
			Player_damage(game->player);
			if (game->player->life == 0) Game_end(game);
		}
}

void GameIAEntities_draw(GameIAEntities * gameIAEntity) {
	if (!gameIAEntity->visible) return;
	// Debug radius
	if (DEBUG)
		DrawCircle(gameIAEntity->position.x, gameIAEntity->position.y, gameIAEntity->radiusZone, (Color) { 211, 176, 131, 75 });  

	// Draw entity
	DrawTexture(gameIAEntity->texture, gameIAEntity->position.x - (ENITTY_TEXTURE_SCALE/2), gameIAEntity->position.y - (ENITTY_TEXTURE_SCALE/2), WHITE);
}