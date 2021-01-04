#include "raylib.h"
#include "includes/objective.h"

Objective * Objective_new(int id, char * text, Texture2D objectiveTexture, Texture2D objectiveFinishedTexture) {
	Objective * objective = malloc(sizeof(Objective));
	objective->id = id;
	objective->text = text;
	objective->finished = false;
	objective->visible = false;
	objective->objectiveTexture = objectiveTexture;
	objective->objectiveFinishedTexture = objectiveFinishedTexture;
	objective->lines_count = 1;
	for (int i = 0; text[i] != 0; i++) if (text[i] == '\n') objective->lines_count++;
	return objective;
}

void Objective_draw(int x, int y, Objective * objective) {
	if (!objective->visible) return;
	DrawTexture(objective->finished ? objective->objectiveFinishedTexture : objective->objectiveTexture, x, y, WHITE);
	DrawText(objective->text, x + 16 + 5, y + 5, 10, objective->finished ? LIGHTGRAY : BLACK);
}

void Objective_reveal(Objective * objective) {
	objective->visible = true;
}

void Objective_finish(Objective * objective) {
	objective->finished = true;
}