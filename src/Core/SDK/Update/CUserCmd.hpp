#pragma once

#include <Common/Math/Vector.hpp>

class CUserCmd {
public:
    enum class ButtonFlag : int {
        Attack = 1 << 0,
        Jump = 1 << 1,
        Duck = 1 << 2,
        Forward = 1 << 3,
        Back = 1 << 4,
        Use = 1 << 5,
        Cancel = 1 << 6,
        Left = 1 << 7,
        Right = 1 << 8,
        MoveLeft = 1 << 9,
        MoveRight = 1 << 10,
        Attack2 = 1 << 11,
        Run = 1 << 12,
        Reload = 1 << 13,
        Alt1 = 1 << 14,
        Alt2 = 1 << 15,
        Score = 1 << 16,
        Speed = 1 << 17,
        Walk = 1 << 18,
        Zoom = 1 << 19,
        Weapon1 = 1 << 20,
        Weapon2 = 1 << 21,
        BullRush = 1 << 22,
        Grenade1 = 1 << 23,
        Grenade2 = 1 << 24,
        Attack3 = 1 << 25
    };

    enum class Impulse : unsigned char {
        Flashlight = 100
    };

    int commandNumber;
    int tickCount;
    Angle viewAngles;
    float forwardMove;
    float sideMove;
    float upMove;
    int buttonFlags;
    unsigned char impulse;
    int weaponSelect;
    int weaponSubtype;
    int randomSeed;
    short mouseDx;
    short mouseDy;
    bool hasBeenPredicted;
    char padding0[5];
    bool unknown;
    bool contextMenu;
    Vector3 contextNormal;
    bool isTyping;
};
