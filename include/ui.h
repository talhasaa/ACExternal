#ifndef UI_H
#define UI_H

#include "main.h"
#include "programdata.h"

void mainMenu(UIData& data);
int uiRender(std::atomic<bool> &isRunning);

#endif // UI_H