#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H

#include "main.h"
#include "entitymanager.h"

class EntityManager;

struct UIData {
    bool healthChanged = false;
    bool armorChanged = false;
    bool currentAmmoChanged = false;
    bool maxAmmoChanged = false;

    int32_t health = 0;
    int32_t armor = 0;
    int32_t currentAmmo = 0;
    int32_t maxAmmo = 0;

    bool espEnabled = false;
    bool drawTeammates = true;
    bool teamIndicatorTeammateEnabled = false;
    bool teamIndicatorEnemyEnabled = true;
    bool tracerLinesEnabled = true;
    bool statusBarsEnabled = true;
    bool headCircleEnabled = true;

    bool aimBotEnabled = false;
    bool lockTeammates = false;

    float aimBotAlpha = 0.1f;
    float aimBotDistance = 20.0f;
};

struct ProgramData {
    private:
        static ProgramData* instance;
    public:
        std::mutex mutex;
        HANDLE handle;
        HWND gameWindowHwnd;
        uint32_t baseAddress;
        EntityManager entityManager;
        std::vector<float> viewMatrix;
        UIData uiData;
        Vector2 monitorSize;
        Vector2 windowPos;
        Vector2 windowSize;
        bool aimBotLocked;
        double lastAimBotTick;

        static ProgramData& getInstance();

        ~ProgramData();
};

#endif // PROGRAMDATA_H