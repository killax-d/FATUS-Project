#include "includes/objectivesnotes.h"

void ObjectivesNotes_init(ObjectivesNotes * objectives, Assets * assets) {
	objectives->background = assets->textures[OBJECTIVES_BACKGROUND_TEXTURE];
	objectives->visible = false;

	objectives->objectives[OPEN_CELL_OBJECTIVE] = Objective_new(OPEN_CELL_OBJECTIVE, "Faire exploser la porte\n de votre cellule", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);
	objectives->objectives[FIND_GREEN_MAGNET_CARD] = Objective_new(FIND_GREEN_MAGNET_CARD, "Ouvrir la salle des gardes", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);
	objectives->objectives[FIND_YELLOW_MAGNET_CARD] = Objective_new(FIND_YELLOW_MAGNET_CARD, "Ouvrir l'accès à la salle des machines\n au Sud du vaisseau", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);
	objectives->objectives[FIND_ENGINES_KEY] = Objective_new(FIND_ENGINES_KEY, "Ouvrir les 2 salles des moteurs", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);
	objectives->objectives[FIND_BLUE_MAGNET_CARD] = Objective_new(FIND_BLUE_MAGNET_CARD, "Ouvrir l'infimerie dans l'aile Ouest\n du vaisseau", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);
	objectives->objectives[FIND_RED_MAGNET_CARD] = Objective_new(FIND_RED_MAGNET_CARD, "Ouvrir la salle de contrôle au Nord\n du vaisseau", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);
	objectives->objectives[FIND_USB_KEY] = Objective_new(FIND_USB_KEY, "Trouver la clé USB pour la brancher \n sur l'ordinateur principal", assets->textures[OBJECTIVE_TEXTURE], assets->textures[OBJECTIVE_TICKED_TEXTURE]);

	objectives->objectives[OPEN_CELL_OBJECTIVE]->visible = true;
}

void ObjectivesNotes_draw(int x, int y, ObjectivesNotes * objectives) {
	if (!objectives->visible) return;
	int lines = 0;
	DrawTexture(objectives->background, x, y, WHITE);
	for (int i = 0; i < OBJECTIVES_COUNT; i++) {
		Objective_draw(OBJECTIVES_NOTES_PADDING_LEFT + x, OBJECTIVES_NOTES_PADDING_TOP + y + (i * 4) + (16 * (lines + 1)), objectives->objectives[i]);
		lines += objectives->objectives[i]->lines_count;
	}
}

void ObjectivesNotes_finish(ObjectivesNotes * objectives, int id) {
	Objective_finish(objectives->objectives[id]);
	if (id < OBJECTIVES_COUNT-1) Objective_reveal(objectives->objectives[id+1]);
}