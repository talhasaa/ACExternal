#ifndef OFFSETS_H
#define OFFSETS_H

#include "main.h"

namespace Offsets
{
    const uint32_t localPlayerOff = 0x0017E0A8;
    const uint32_t entityListOff = 0x00191FCC;
    const uint32_t playerCountOff = 0x00191FD4;
    const uint32_t playerGap = 0x4;

    const uint32_t viewMatrixOff = 0x0017DFD0;

    namespace Entity {
        const uint32_t headPositionOff      = 0x0004;
        const uint32_t positionOff          = 0x0028;
        const uint32_t cameraPositionOff    = 0x0034;
        //const uint32_t jumpingOff           = 0x005F;
        //const uint32_t walkDirectionOff     = 0x0074;
        const uint32_t healthOff            = 0x00EC;
        const uint32_t armorOff             = 0x00F0;
        //const uint32_t shootingOff          = 0x0204;
        //const uint32_t playerNameOff        = 0x0205;
        const uint32_t currentWeaponPtrOff  = 0x0374;
        const uint32_t ammoClipPtrOff       = 0x0010;
    };

    namespace AmmoClip {
        const uint32_t maxAmmoOff     = 0x0;
        const uint32_t currentAmmoOff = 0x0024;
    };
};

#endif // OFFSETS_H