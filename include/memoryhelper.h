#ifndef MEMORYHELPER_H
#define MEMORYHELPER_H

#include "main.h"

DWORD GetProcessIdByName(const char *processName);
uint32_t GetModuleBaseAddress(const DWORD processId, const char *moduleName);

class MemoryHelper
{
private:
    HANDLE hProcess;
    uint32_t base;
public:
    MemoryHelper(const HANDLE processHandle);

    void setBase(uint32_t baseAddress) {
        base = baseAddress;
    };

    // Reads a pointer
    int ReadPointer(const uint32_t address, uint32_t &value);

    // Reads a multi-level pointer
    int ReadMultiLevelPtrInt32Val(const uint32_t address, const std::vector<uint32_t> offsets, int32_t &value);

    // Reads a 32 bit integer value
    int ReadInt32(const uint32_t address, int32_t &value);
    
    int ReadInt32Ptr(const uint32_t address, int32_t *value);
    // Writes a 32 bit integer value to an address
    int WriteInt32(const uint32_t address, int32_t value);

    // Reads a 16 bit integer value
    int ReadUInt16(const uint32_t address, uint16_t &value);
    // Writes a 16 bit integer value to an address
    int WriteUInt16(const uint32_t address, uint16_t value);

    // Reads a Vector2 integer value
    int ReadVector2(const uint32_t address, Vector2 &value);
    // Writes a Vector2 integer value to an address
    int WriteVector2(const uint32_t address, Vector2 value);

    // Reads a Vector3 value
    int ReadVector3(const uint32_t address, Vector3 &value);
    // Writes a Vector3 value to an address
    int WriteVector3(const uint32_t address, Vector3 value);

    // Reads a 4x4 matrix
    int ReadMatrix(const uint32_t address, std::vector<float>& value, int length);

    // Reads a char[] value
    int ReadString(const uint32_t address, std::string &value, int strLength);
};

#endif // MEMORYHELPER_H