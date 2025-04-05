#include "main.h"
#include "programdata.h"

UIData::UIData()
{
    healthChanged = armorChanged = currentAmmoChanged = maxAmmoChanged = false;

    health = 100;
    armor = 0;
    currentAmmo = 0;
    maxAmmo = 0;

    espEnabled = false;
    tracerLinesEnabled = statusBarsEnabled = headCircleEnabled = true;

    aimBotEnabled = false;
    aimBotAlpha = 0.1f;
    aimBotDistance = 20.0f;
};

ProgramData *ProgramData::instance = nullptr;

ProgramData &ProgramData::getInstance()
{
    if (!instance)
    {
        instance = new ProgramData();
    };
    return *instance;
};

ProgramData::~ProgramData()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
};