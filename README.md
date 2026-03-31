# FRESteamWorks Stub (Offline AIR Steamworks Shim) 

Stub implementation of the `com.amanitadesign.steam.FRESteamWorks` Adobe AIR native extension (ANE).

It is designed for **digital preservation**, and **long‑term playability** 
of AIR‑based games that depend on Steamworks initialization but do
not require actual Steam API functionality.

## Purpose

Some AIR games freeze on a black screen if the Steamworks ANE fails to load or
initialize, for ex. Detective Grimoire. 


## What This Stub Does

This allows affected games to launch normally **without internet**, and 
**without the original Steamworks SDK**.

- Loads as a valid AIR native extension  
- Responds to `AIRSteam_Init` with a truthy value  
- Does **not** implement achievements, stats, callbacks, or any Steam API  
- Does **not** communicate with Steam or the network  

## Structure

/src
FRESteamWorks_stub.c
FlashRuntimeExtensions.h
FRESteamWorks.def

## Building (MinGW)

This project uses the MSYS2 environment and the 32‑bit MinGW‑w64 toolchain,
because Adobe AIR for Windows is a 32‑bit runtime and requires 32‑bit native
extensions.

### 1. Install MSYS2

Download and install MSYS2 from:

https://www.msys2.org/

Optionally: You may need the JRE 8 runtime which you can obtain from 
https://adoptium.net/temurin/releases?version=8&os=any&arch=any

### 2. Install the 32‑bit MinGW‑w64 GCC toolchain

Open the **MSYS2 MinGW 32‑bit** terminal and run:


pacman -Syu
pacman -S mingw-w64-i686-gcc

### 3. Clone this repository

git clone https://github.com/calydon/FRESteamWorks-Stub.git
cd FRESteamWorks-Stub

### 4. Build the DLL

From the **MSYS2 MinGW 32‑bit** terminal:

gcc -shared -o FRESteamWorks.dll src/FRESteamWorks_stub.c src/FRESteamWorks.def -Isrc


This produces:


FRESteamWorks.dll


Place this DLL in:

<game folder>/META-INF/AIR/extensions/com.amanitadesign.steam.FRESteamWorks/META-INF/ANE/Windows-x86/

Example using Detective Grimoire (Steam version)
C:\Program Files (x86)\Steam\steamapps\common\Detective Grimoire\META-INF\AIR\extensions\com.amanitadesign.steam.FRESteamWorks\META-INF\ANE\Windows-x86

### 5. Run the game

If the game previously froze on a black screen due to missing Steamworks
initialization, it should now launch normally.

## License

This project is released under an MIT License.  
You are free to use, modify, and redistribute it for preservation and research.

## Attribution

This stub is **not** affiliated with Amanita Design, Valve, Adobe, SFB Games, Armor Games or any of its subsidiaries.  
It is a reimplementation created solely for archival and educational
purposes.

The original AIR Steamworks ANE belongs to its respective authors and copyright holders.

## Disclaimer

This stub does **not** implement Steamworks and does not bypass Steam DRM
or enable unauthorized access to Steam‑exclusive features. It is intended only
for preserving games that no longer function due to deprecated AIR/Steam
integration.