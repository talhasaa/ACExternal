#ifndef ENTITY_H
#define ENTITY_H

#include "main.h"
class ProgramData;

class Entity
{
private:
    uint32_t address;
    Vector3 headPosition;

    //Vector3 position;     // Position is just z: -4.5 compared to head position
    Vector2 cameraPosition;

    //uint16_t walkDirection;

    int32_t health;
    int32_t armor;
    int32_t team;

    //std::string playerName;

    int32_t currentWpCurrAmmo;
    int32_t currentWpMaxAmmo;
public:
    void setAddress(const uint32_t baseAddress);
    int Update(ProgramData& programData);
    int Init(ProgramData& programData);

    Vector3 getHeadPosition();
    void setHeadPosition(HANDLE hProcess, const Vector3 headPosition);

    /*Vector3 getPosition();
    void setPosition(const Vector3& position);*/

    Vector2 getCameraPosition();
    void setCameraPosition(HANDLE hProcess, const Vector2 cameraPosition);

    uint16_t getWalkDirection();
    void setWalkDirection(HANDLE hProcess, uint16_t walkDirection);

    int32_t getHealth();
    void setHealth(HANDLE hProcess, int32_t health);

    int32_t getArmor();
    void setArmor(HANDLE hProcess, int32_t armor);

    int32_t getTeam();

    int32_t getCurrentWpCurrentAmmo();
    void setCurrentWpCurrentAmmo(HANDLE hProcess, int32_t currAmmoValue);

    int32_t getCurrentWpMaxAmmo();
    void setCurrentWpMaxAmmo(HANDLE hProcess, int32_t maxAmmoValue);
};

#endif // ENTITY_H