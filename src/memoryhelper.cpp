#include "main.h"
#include "memoryhelper.h"

DWORD GetProcessIdByName(const char *processName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32First(snapshot, &entry)) {
        do {
            if (_stricmp(entry.szExeFile, processName) == 0) {
                DWORD pid = entry.th32ProcessID;
                CloseHandle(snapshot);
                return pid;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
};

uint32_t GetModuleBaseAddress(const DWORD processId, const char *moduleName) {
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    uint32_t baseAddress = 0;
    if (Module32First(hSnapshot, &moduleEntry)) {
        do {
            if (_stricmp(moduleEntry.szModule, moduleName) == 0) {
                baseAddress = (DWORD_PTR)moduleEntry.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &moduleEntry));
    }

    CloseHandle(hSnapshot);
    return baseAddress;
};

MemoryHelper::MemoryHelper(const HANDLE processHandle) {
    hProcess = processHandle;
    base = 0x0;
};

int MemoryHelper::ReadPointer(const uint32_t address, uint32_t &value) {
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), &value, sizeof(uint32_t), NULL)) return 1;
    return 0;
};

/*int MemoryHelper::ReadMultiLevelPtrInt32Val(const uint32_t address, const std::vector<uint32_t> offsets, int32_t &value) {
    uint32_t ptrValue;
    if (ReadPointer(address, ptrValue) != 0) return 1;
    for (int32_t offset : offsets) {
        if (ReadPointer(ptrValue + offset, ptrValue) != 0) return 1;
    };
    value = ptrValue;
    return 0;
};*/

int MemoryHelper::ReadInt32(const uint32_t address, int32_t &value) {
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), &value, sizeof(int32_t), NULL)) return 1;
    return 0;
};

int MemoryHelper::WriteInt32(const uint32_t address, int32_t value) {
    if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(base + address), (LPCVOID)&value, sizeof(int32_t), NULL)) return 1;
    return 0;
};

/*int MemoryHelper::ReadUInt16(const uint32_t address, uint16_t &value) {
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), &value, sizeof(uint16_t), NULL)) return 1;
    return 0;
};

int MemoryHelper::WriteUInt16(const uint32_t address, uint16_t value) {
    if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(base + address), &value, sizeof(uint16_t), NULL)) return 1;
    return 0;
};*/

int MemoryHelper::ReadVector2(const uint32_t address, Vector2 &value) {
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), &value, sizeof(Vector2), NULL)) return 1;
    return 0;
};

int MemoryHelper::WriteVector2(const uint32_t address, Vector2 value) {
    if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(base + address), &value, sizeof(Vector2), NULL)) return 1;
    return 0;    
};

int MemoryHelper::ReadVector3(const uint32_t address, Vector3 &value) {
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), &value, sizeof(Vector3), NULL)) return 1;
    return 0;
};

int MemoryHelper::WriteVector3(const uint32_t address, Vector3 value) {
    if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(base + address), &value, sizeof(Vector3), NULL)) return 1;
    return 0;    
};

int MemoryHelper::ReadMatrix(const uint32_t address, std::vector<float>& value, int length) {
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), value.data(), length * sizeof(float), NULL)) return 1;
    return 0;
};

/*int MemoryHelper::ReadString(const uint32_t address, std::string &value, int strLength) {
    std::vector<char> buffer;
    SIZE_T bytesRead;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(base + address), buffer.data(), sizeof(strLength), &bytesRead)) return 1;
    value = std::string(buffer.data(), bytesRead);
    return 0;
};*/