# btgarecomp-mod-template

A mod template for the [BattleTanx: Global Assault recomp](https://github.com/wootbeer/btgarecomp).

The example mod is **Tank Bucks Top-Up**: your Tank Bucks never drop below the amount you pick in the Mods menu.

**Just want to play it?** Get `btga_tank_bucks_topup.nrm` from [Releases](https://github.com/wootbeer/btgarecomp-mod-template/releases), then see [Installing](#installing).

Copy this repo, change the code in `src/` and the info in `mod.toml`, and you have your own mod.

## What You Need
- `clang` and `make`. Use clang 18. clang 19 has trouble with MIPS.
  - Windows: install with [chocolatey](https://chocolatey.org/): `choco install llvm --version 18.1.8` and `choco install make`.
  - Linux: install `clang`, `lld`, `make` and `zip` from your package manager.
  - macOS: install `llvm`, `make` and `zip` with Homebrew. Apple's clang won't work.
- `RecompModTool` from the [N64Recomp releases](https://github.com/N64Recomp/N64Recomp/releases/tag/mod-tool-release). Put it in this folder.

## Building
1. Run `make nrm`.
2. Your mod is `build/btga_tank_bucks_topup.nrm`.

Or skip all that: push to GitHub and the Build action makes the `.nrm` for you. Get it from the run's Artifacts.

## Making a Release
1. Change `version` in `mod.toml` and the text in `release_notes.md`.
2. Push to `main`.
3. The Build action makes a release with the `.nrm` on it. If that version already has a release, it skips it.

## Installing
Open the Mods tab in the recomp and drop the `.nrm` file in. Turn the mod on and start the game.

## Files
| File | What it is |
|---|---|
| `src/main.c` | The mod's code. |
| `mod.toml` | Mod name, ID, version, authors and options. |
| `include/btga.h` | Game variables we know about (Tank Bucks, cheat flags). |
| `include/modding.h` | `RECOMP_HOOK`, `RECOMP_PATCH` and the rest. Don't edit. |
| `include/recompconfig.h` | Read your mod's options. |
| `include/recomputils.h` | Memory and dependency helpers. |
| `thumb.png` | The picture in the Mods menu. Replace it with your own. |
| `syms/battletanxga.us.rev0.syms.toml` | Every game function's name and address. Copied from btgarecomp's `BattleTanxGASyms/`. |

## Making Your Own Mod

### Hooks and patches
- `RECOMP_HOOK("func_name")` runs your function right before the game's. The game's function still runs. Use this when you can.
- `RECOMP_HOOK_RETURN("func_name")` runs your function right after the game's.
- `RECOMP_PATCH` replaces a game function completely. Name your function the same as the game's. Only one mod can patch a function.

The game has no decompilation, so most functions are just named by address (`func_8007A0A0`). The names have to match `syms/battletanxga.us.rev0.syms.toml`. All the game's code is in the first MB of the ROM (`0x80071000` to `0x80171000`), and the syms file covers it.

### Reading and changing game memory
Game variables are just addresses. See `include/btga.h`:

```c
#define BTGA_TANK_BUCKS (*(volatile u8*)0x80236A9F)
```

Then use it like a normal variable: `BTGA_TANK_BUCKS = 100;`

Add your own addresses to `btga.h` as you find them. GameShark codes are a good place to start: `80XXXXXX 00YY` writes the byte `YY` to `0x80XXXXXX`, and `81XXXXXX YYYY` writes the 16-bit value `YYYY`. btgarecomp's `src/game/cheats.cpp` has a lot of them.

### Memory
Mods are loaded at `0x81000000`. btgarecomp keeps some of the memory below that for its own fixes (`0x807E0000` to `0x80802000` and `0x80C00000` to `0x80CC0000`), so don't write there. If you need memory, use `recomp_alloc` from `recomputils.h`.

### Don't touch these functions
btgarecomp already changes these. Hooking or patching them will undo btgarecomp's own fixes, or the mod won't load:

- Patched: `func_800A1858`
- Stubbed: `func_8007919C` `func_80079260` `__osException_80104FB0`
- Hooked: `Fdefa` `Ftempo` `_Ldtob` `alAdpcmPull` `alLoadParam` `func_80079CB8` `func_80079FF0` `func_8007A250` `func_8007A818` `func_8007B03C` `func_8007B1F0` `func_8007B65C` `func_8007B8EC` `func_8007C364` `func_80082834` `func_80082F1C` `func_80087DF4` `func_80088030` `func_8008BF5C` `func_8008C3B4` `func_8008C5D8` `func_8008E780` `func_8008ECB4` `func_80096424` `func_80096BDC` `func_80097844` `func_800988E8` `func_80098B40` `func_80099FE8` `func_8009A95C` `func_8009AE38` `func_8009C524` `func_8009D3A4` `func_8009D75C` `func_8009ED9C` `func_800A0968` `func_800A0BA8` `func_800A0E00` `func_800A1384` `func_800A1FDC` `func_800A2FBC` `func_800A5744` `func_800A89B0` `func_800AC9E8` `func_800ACE70` `func_800AF43C` `func_800BC9F4` `func_800BF80C` `func_800BFAEC` `func_800C7AA0` `func_800C7C10` `func_800C877C` `func_800CF41C` `func_800CF4E4` `func_800CF5C8` `func_800CF690` `func_800D25E0` `func_800D56FC` `func_800D5E2C` `func_800D6EEC` `func_800D7638` `func_800D88F0` `func_800D8C60` `func_800D8F48` `func_800D92E0` `func_800D942C` `func_800D9900` `func_800D9D50` `func_800DB850` `func_800E1BB0` `func_800E4530` `func_800E713C` `func_800E7768` `func_800EA224` `func_800EAE58` `func_800ED63C` `func_800ED990` `func_800EDDCC` `func_800F11D0` `func_800F3B80` `func_800F3E58` `func_800F4698` `func_800F50B8` `func_800F67F0` `func_800FAFBC` `func_800FC31C` `func_800FC8E0` `func_800FD4CC` `func_800FD608` `func_800FF820` `func_80113E30` `leointerrupt_text_078C` `n_alEnvmixerPull` `player_text_1AE0` `xldtob_text_0000`
- Instruction patches (besides the ones above): `func_800788E8` `func_80078DFC` `func_80078E18` `func_80078E40` `func_800A60E0`

The libultra functions the runtime replaces (`osSendMesg`, `osRecvMesg`, `__ll_div` and the like) can't be hooked either.

The list comes from btgarecomp's `battletanxga.us.rev0.toml` and `patches/`. Check there if btgarecomp gets updated.

### Picture
The Mods menu shows `thumb.png`. Make your own, keep it square (256x256 is good) and keep the name `thumb.png`.

### Options
Options go in `mod.toml` under `[[manifest.config_options]]` and show up in the Mods menu. Read them in code with `recomp_get_config_u32("id")`.

### Not there yet
- `recomp_printf` (printing to the console) isn't in btgarecomp yet. A mod that uses it won't load.

## More Info
- [N64Recomp modding guide](https://hackmd.io/fMDiGEJ9TBSjomuZZOgzNg): hooks, patches, events and talking to other mods.
- [Sin and Punishment mod template](https://github.com/wootbeer/snprecomp-mod-template): the same kind of template for snprecomp.
- [Banjo-Kazooie mod template](https://github.com/BanjoRecomp/BKRecompModTemplate): these templates are based on it.
