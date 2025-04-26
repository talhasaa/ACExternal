#include "main.h"
#include "programdata.h"

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