#include "main.h"
#include "memoryhelper.h"
#include "programdata.h"

#include "entity.h"
#include "entitymanager.h"

#include "features.h"
#include "ui.h"

void mainLoop(std::atomic<bool> &isRunning);

int main() {
    std::cout << "<#### ACExternal by talhasa ####>" << std::endl;

    HWND hwnd = FindWindow(NULL, "AssaultCube");
    if (!hwnd) {
        MessageBox(NULL, "Please run the game first and try again!", "ACExternal Warning", MB_OK | MB_ICONWARNING);
        return 1;
    }

    std::cout << "# Loading.." << std::endl;
    DWORD pid = GetProcessIdByName("ac_client.exe");

    std::cout << "# Opening handle.. [OpenProcess]" << std::endl;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    std::cout << "# Initializing.." << std::endl;

    Vector2 monitorSize;

    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi;
    mi.cbSize = sizeof(mi);
    
    if (GetMonitorInfo(hMonitor, &mi)) {
        monitorSize.x = mi.rcMonitor.right;
        monitorSize.y = mi.rcMonitor.bottom;
    } else {
        MessageBox(NULL, "Couldn't get monitor info", "ACExternal Warning", MB_OK | MB_ICONWARNING);
        return 1;
    }

    Vector2 winPos = {0, 0};
    Vector2 winSize = {0, 0};
    std::vector<float> vMatrix(16);

    ProgramData& programData = ProgramData::getInstance();
    programData.handle = hProcess;
    programData.baseAddress = GetModuleBaseAddress(pid, "ac_client.exe");
    programData.viewMatrix = vMatrix;
    programData.monitorSize = monitorSize;
    programData.windowPos = winPos;
    programData.windowSize = winSize;
    programData.aimBotLocked = false;

    std::atomic<bool> isRunning(true);
    std::cout << "\n# Launching UI and main thread.." << std::endl;
    std::thread uiThread(uiRender, std::ref(isRunning));
    std::thread mainThread(mainLoop, std::ref(isRunning));

    uiThread.join();
    mainThread.join();

    CloseHandle(hProcess);
}

void mainLoop(std::atomic<bool> &isRunning) {
    ProgramData &programData = ProgramData::getInstance();
    HANDLE hProcess = programData.handle;

    EntityManager& entityManager = programData.entityManager;
    entityManager.Init(programData);

    UIData& uiData = programData.uiData;
    std::mutex& mutex = programData.mutex;
    Vector2 monitorSize = programData.monitorSize;

    MemoryHelper memory(hProcess);
    memory.setBase(programData.baseAddress);

    Entity& localPlayer = entityManager.getLocalPlayer();
    std::vector<Entity>& entityList = entityManager.getEntityList();
    std::vector<std::pair<Vector3, Vector3>>& screenPosList = entityManager.getScreenPositionList();
    
    int32_t oldPlayerCount = 0;

    std::cout << "# Enjoy!" << std::endl;

    while (isRunning.load())
    {
        std::this_thread::yield();
        // Get game window
        HWND hwnd = FindWindow(NULL, "AssaultCube");
        if (hwnd == NULL) {
            isRunning.store(false);
            MessageBox(NULL, "Game is closed, quitting..", "ACExternal", MB_OK | MB_ICONINFORMATION);
            continue;
        }

        RECT rect;
        if (GetClientRect(hwnd, &rect)) {
            Vector2 winPos, winSize;
            winSize.x = rect.right - rect.left;
            winSize.y = rect.bottom - rect.top;

            if (winSize.x == 0 && winSize.y == 0) {
                programData.windowSize = monitorSize;
                programData.windowPos = Vector2 {0, 0};
            } else {
                programData.windowSize = winSize;

                ClientToScreen(hwnd, (POINT*)&rect);
                winPos.x = rect.left; winPos.y = rect.top;
                programData.windowPos = winPos;
            };
        };

        int32_t playerCount;
        if (memory.ReadInt32(Offsets::playerCountOff, playerCount) != 0) continue;
        
        if (oldPlayerCount != playerCount) {
            entityManager.ReadEntityList(programData, playerCount);
            oldPlayerCount = playerCount;
        } else {
            entityManager.UpdateEntities(programData);
        }

        std::vector<float> viewMatrix(16);
        memory.ReadMatrix(Offsets::viewMatrixOff, viewMatrix, 16);
        programData.viewMatrix = viewMatrix;

        std::lock_guard<std::mutex> lock(mutex);

        if (uiData.healthChanged) {
            localPlayer.setHealth(hProcess, uiData.health);
            uiData.healthChanged = false;
        } else {
            uiData.health = localPlayer.getHealth();
        }

        if (uiData.armorChanged) {
            localPlayer.setArmor(hProcess, uiData.armor);
            uiData.armorChanged = false;
        } else {
            uiData.armor = localPlayer.getArmor();
        }

        if (uiData.currentAmmoChanged) {
            localPlayer.setCurrentWpCurrentAmmo(hProcess, uiData.currentAmmo);
            uiData.currentAmmoChanged = false;
        } else {
            uiData.currentAmmo = localPlayer.getCurrentWpCurrentAmmo();
        }

        if (uiData.maxAmmoChanged) {
            localPlayer.setCurrentWpMaxAmmo(hProcess, uiData.maxAmmo);
            uiData.maxAmmoChanged = false;
        } else {
            uiData.maxAmmo = localPlayer.getCurrentWpMaxAmmo();
        }
        
        if (uiData.aimBotEnabled) {
            if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_LCONTROL) & 0x8000)) {
                runAimBot(programData, uiData, entityList, localPlayer, screenPosList);
            } else {
                if (programData.aimBotLocked == true) {
                    programData.aimBotLocked = false;
                };
            }
        };
    }
};