#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "main.h"
#include "entity.h"

class EntityManager
{
private:
    Entity localPlayer;
    std::vector<Entity> entityList;
    std::vector<std::pair<Vector3, Vector3>> screenPositionList;
public:
    int Init(ProgramData& programData);
    int ReadEntityList(ProgramData& programData, const int32_t playerCount);
    int UpdateEntities(ProgramData& programData);

    Entity& getLocalPlayer();
    std::vector<Entity>& getEntityList();
    std::vector<std::pair<Vector3, Vector3>>& getScreenPositionList();
};

#endif // ENTITYMANAGER_H