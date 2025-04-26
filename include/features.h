#ifndef FEATURES_H
#define FEATURES_H

#include "features.h"
#include "programdata.h"
#include "entity.h"

void renderEsp(ProgramData& programData, UIData& uiData, ImDrawList* draw_list, Entity& localPlayer, std::vector<Entity>& entityList, std::vector<std::pair<Vector3, Vector3>>& posList);
void renderAimBot(ProgramData& programData, UIData& uiData, ImDrawList* draw_list);
void runAimBot(ProgramData& programData, UIData& uiData, std::vector<Entity>& entityList, Entity& localPlayer, std::vector<std::pair<Vector3, Vector3>>& posList);

#endif // FEATURES_H