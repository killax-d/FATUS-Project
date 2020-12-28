#include "includes/minimap.h"

void Minimap_init(Minimap * minimap) {
	minimap->zooms_availables[0] = 40;
	minimap->zooms_availables[1] = 50;
	minimap->zooms_availables[2] = 100;

	minimap->zoom = 0;
	minimap->scale = minimap->width / minimap->zooms_availables[minimap->zoom];
}

void Minimap_control(Minimap * minimap) {
    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
	    // Zoom control
	    minimap->zoom -= GetMouseWheelMove();
	    if (minimap->zoom >= ZOOM_COUNT) minimap->zoom = ZOOM_COUNT-1;
	    else if (minimap->zoom < 0) minimap->zoom = 0;

	    // update scale
	    minimap->scale = minimap->width / minimap->zooms_availables[minimap->zoom];
	}
}

void Minimap_draw(Minimap * minimap, Game * game) {
	// Background
	DrawRectangleRec(
		(Rectangle)
		{ 
			minimap->x, 
			minimap->y, 
			minimap->width,
			minimap->height
		},
		(Color)
			{255, 255, 255, 100}
	);

	// Map
    for (int i = -minimap->zooms_availables[minimap->zoom]/2; i <= minimap->zooms_availables[minimap->zoom]/2; i++) 
        for (int j = -minimap->zooms_availables[minimap->zoom]/2; j <= minimap->zooms_availables[minimap->zoom]/2; j++) {
            int y = ((int) game->player->position.y / MAP_TEXTURE_SCALE);
            int x = ((int) game->player->position.x / MAP_TEXTURE_SCALE);
            float drawX = minimap->x + (j+minimap->zooms_availables[minimap->zoom]/2)*minimap->scale;
            float drawY = minimap->y + (i+minimap->zooms_availables[minimap->zoom]/2)*minimap->scale;
            if ((y+i >= 0 && y+i < MAP_HEIGHT && x+j >= 0 && x+j < MAP_WIDTH)
            	&& (drawX < minimap->x + minimap->width && drawY < minimap->y + minimap->height))
                DrawRectangleRec(
                    (Rectangle)
                        { 
                        	drawX, 
                        	drawY, 
                        	minimap->scale, 
                        	minimap->scale 
                        },
                    game->map->sprite[y+i][x+j].color);
        }
    // Player
    DrawRectangleRec((Rectangle)
    	{
    		minimap->x + (minimap->width/2)-(minimap->scale/2),
    		minimap->y + (minimap->height/2)-(minimap->scale/2),
    		minimap->scale,
    		minimap->scale
    	}, RED);
    // Border
    DrawRectangleLines(
		minimap->x, 
		minimap->y, 
		minimap->width,
		minimap->height,
		(Color){0, 0, 0, 200}
	);
}