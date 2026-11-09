#ifndef BTGA_H
#define BTGA_H

// Basic N64 types.
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define NULL ((void*)0)

// Game variables we know about.
// From btgarecomp's src/game/cheats.cpp (the Cheats tab uses them).

// Tank Bucks. The GameShark code "Infinite Tank Bucks" (80236A9F 0064)
// keeps this at 100.
#define BTGA_TANK_BUCKS (*(volatile u8*)0x80236A9F)

// Flags the game's own cheat codes turn on (1 = on).
#define BTGA_CHEAT_INVINCIBILITY (*(volatile u8*)0x80125AB0) // HPPYHPPY
#define BTGA_CHEAT_ALL_WEAPONS   (*(volatile u8*)0x80125AB1) // RCKTSRDGLR

#endif
