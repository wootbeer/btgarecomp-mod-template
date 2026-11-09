// Tank Bucks Top-Up: an example mod for the BattleTanx: Global Assault recomp.
// Your Tank Bucks never drop below the amount you pick in the Mods menu.

#include "modding.h"
#include "recompconfig.h"
#include "btga.h"

// func_8007A0A0 starts each new frame of the game's main loop. It runs once
// a frame, so it's a good place to run code every frame.
// RECOMP_HOOK runs our function right before the game's function. The
// game's function still runs as normal after.
RECOMP_HOOK("func_8007A0A0")
void tank_bucks_on_frame(void) {
    // "min_bucks" is the option from mod.toml. You can change it in the
    // Mods menu.
    u32 min_bucks = recomp_get_config_u32("min_bucks");

    if (BTGA_TANK_BUCKS < min_bucks) {
        BTGA_TANK_BUCKS = (u8)min_bucks;
    }
}
