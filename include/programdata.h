#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H

#include "main.h"
#include "entitymanager.h"

class EntityManager;

struct UIData {
    UIData();
    bool healthChanged, armorChanged, currentAmmoChanged, maxAmmoChanged;

    int32_t health;
    int32_t armor;
    int32_t currentAmmo;
    int32_t maxAmmo;

    bool espEnabled, tracerLinesEnabled, statusBarsEnabled, headCircleEnabled;

    bool aimBotEnabled;
    float aimBotAlpha, aimBotDistance;
};

struct ProgramData {
    private:
        static ProgramData* instance;
    public:
        std::mutex mutex;
        HANDLE handle;
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