#include "entitymanager.h"
#include "programdata.h"
#include "memoryhelper.h"

int EntityManager::Init(ProgramData& programData) {
    MemoryHelper memory(programData.handle);
    memory.setBase(programData.baseAddress);

    uint32_t localPlrAddress;
    memory.ReadPointer(Offsets::localPlayerOff, localPlrAddress);

    localPlayer.setAddress(localPlrAddress);
    localPlayer.Init(programData);

    return 0;
};

int EntityManager::ReadEntityList(ProgramData& programData, const int32_t playerCount) {
    MemoryHelper memory(programData.handle);
    memory.setBase(programData.baseAddress);

    uint32_t entityListAddr;
    if (memory.ReadPointer(Offsets::entityListOff, entityListAddr) != 0) return 1;

    entityList.clear();

    for (int i = 0; i < playerCount; i++) {
        uint32_t bAddress = i * Offsets::playerGap;
        uint32_t entityAddr;
        memory.setBase(entityListAddr);
        if (memory.ReadPointer(bAddress, entityAddr) != 0) return 1;

        Entity newEntity;
        newEntity.setAddress(entityAddr);
        newEntity.Init(programData);
        entityList.push_back(newEntity);
    }
    return 0;
}

int EntityManager::UpdateEntities(ProgramData& programData) {
    MemoryHelper memory(programData.handle);
    
    localPlayer.Update(programData);

    Vector2 windowSize = programData.windowSize;
    Vector2 windowPosition = programData.windowPos;
    std::vector<float>& viewMatrix = programData.viewMatrix;

    screenPositionList.clear();
    for (Entity& entity : entityList) {
        entity.Update(programData);
        Vector3 headScreenPos;
        Vector3 bodyScreenPos;
        Vector3 entityHeadPos = entity.getHeadPosition();
        Vector3 entityBodyPos = entityHeadPos;
        entityBodyPos.z -= 2.25f;

        Utils::WorldToScreen(entityHeadPos, headScreenPos, viewMatrix, windowSize);
        Utils::WorldToScreen(entityBodyPos, bodyScreenPos, viewMatrix, windowSize);
        headScreenPos.x += windowPosition.x; headScreenPos.y += windowPosition.y;
        bodyScreenPos.x += windowPosition.x; bodyScreenPos.y += windowPosition.y;

        screenPositionList.push_back({ headScreenPos, bodyScreenPos });
    }

    return 0;
}

Entity& EntityManager::getLocalPlayer() {
    return localPlayer;
};

std::vector<Entity>& EntityManager::getEntityList() {
    return entityList;
};

std::vector<std::pair<Vector3, Vector3>>& EntityManager::getScreenPositionList() {
    return screenPositionList;
};