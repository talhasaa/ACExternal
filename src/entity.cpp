#include "entity.h"
#include "programdata.h"
#include "memoryhelper.h"

void Entity::setAddress(const uint32_t baseAddress) {
    address = baseAddress;
};

int Entity::Update(ProgramData& programData) {
    MemoryHelper memory(programData.handle);
    
    memory.setBase(address);

    if (memory.ReadVector3(Offsets::Entity::headPositionOff, headPosition) != 0) return 1;
    if (memory.ReadVector2(Offsets::Entity::cameraPositionOff, cameraPosition) != 0) return 1;
    if (memory.ReadInt32(Offsets::Entity::healthOff, health) != 0) return 1;
    if (memory.ReadInt32(Offsets::Entity::armorOff, armor) != 0) return 1;

    uint32_t weaponAddr;
    if (memory.ReadPointer(Offsets::Entity::currentWeaponPtrOff, weaponAddr) != 0) return 1;

    if (weaponAddr == 0x0) {
        currentWpCurrAmmo = 0;
        currentWpMaxAmmo = 0;
    } else {
        memory.setBase(weaponAddr);
        uint32_t ammoClipAddr;
        if (memory.ReadPointer(Offsets::Entity::ammoClipPtrOff, ammoClipAddr) != 0) return 1;

        memory.setBase(ammoClipAddr);
        if (memory.ReadInt32(Offsets::AmmoClip::maxAmmoOff, currentWpMaxAmmo) != 0) return 1;
        if (memory.ReadInt32(Offsets::AmmoClip::currentAmmoOff, currentWpCurrAmmo) != 0) return 1;
    }

    return 0;
};

int Entity::Init(ProgramData& programData) {
    Update(programData);
    
    /*memory.setBase(address);
    if (memory.ReadString(Offsets::Entity::playerNameOff, playerName, 16) != 0) return 1;*/

    return 0;
}

Vector3 Entity::getHeadPosition() {
    return headPosition;
}

void Entity::setHeadPosition(HANDLE hProcess, const Vector3 headPosition) {
    MemoryHelper memory(hProcess);
    memory.setBase(address);
    memory.WriteVector3(Offsets::Entity::headPositionOff, headPosition);
}

Vector2 Entity::getCameraPosition() {
    return cameraPosition;
}

void Entity::setCameraPosition(HANDLE hProcess, const Vector2 cameraPosition) {
    MemoryHelper memory(hProcess);
    memory.setBase(address);
    memory.WriteVector2(Offsets::Entity::cameraPositionOff, cameraPosition);
}

int32_t Entity::getHealth() {
    return health;
}

void Entity::setHealth(HANDLE hProcess, int32_t health) {
    MemoryHelper memory(hProcess);
    memory.setBase(address);
    memory.WriteInt32(Offsets::Entity::healthOff, health);
}

int32_t Entity::getArmor() {
    return armor;
}

void Entity::setArmor(HANDLE hProcess, int32_t armor) {
    MemoryHelper memory(hProcess);
    memory.setBase(address);
    memory.WriteInt32(Offsets::Entity::armorOff, armor);
}

int32_t Entity::getCurrentWpCurrentAmmo() {
    return currentWpCurrAmmo;
}

void Entity::setCurrentWpCurrentAmmo(HANDLE hProcess, int32_t currAmmoValue) {
    MemoryHelper memory(hProcess);
    memory.setBase(address);

    uint32_t weaponAddr;
    if (memory.ReadPointer(Offsets::Entity::currentWeaponPtrOff, weaponAddr) != 0) return;
    if (weaponAddr == 0x0) return;

    memory.setBase(weaponAddr);
    uint32_t ammoClipAddr;
    if (memory.ReadPointer(Offsets::Entity::ammoClipPtrOff, ammoClipAddr) != 0) return;

    memory.setBase(ammoClipAddr);
    if (memory.WriteInt32(Offsets::AmmoClip::currentAmmoOff, currAmmoValue) != 0) return;
}

int32_t Entity::getCurrentWpMaxAmmo() {
    return currentWpMaxAmmo;
}

void Entity::setCurrentWpMaxAmmo(HANDLE hProcess, int32_t maxAmmoValue) {
    MemoryHelper memory(hProcess);

    memory.setBase(address);
    
    uint32_t weaponAddr;
    if (memory.ReadPointer(Offsets::Entity::currentWeaponPtrOff, weaponAddr) != 0) return;
    if (weaponAddr == 0x0) return;

    memory.setBase(weaponAddr);
    uint32_t ammoClipAddr;
    if (memory.ReadPointer(Offsets::Entity::ammoClipPtrOff, ammoClipAddr) != 0) return;

    memory.setBase(ammoClipAddr);
    if (memory.WriteInt32(Offsets::AmmoClip::maxAmmoOff, maxAmmoValue) != 0) return;
}