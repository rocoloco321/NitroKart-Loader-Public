# NitroKart-Loader

This is a partial source code release for Nitro Kart Loader, a modding framework for Mario Kart DS

# Features

## Custom Track Information file

Allows to load course attributes that usually are hardcoded or requires editing the arm9
* Local Map coords
* Global Map coords
* Sequence ID
* SFX Bank ID
Additionally, the information file allows you to use features from the vanilla game that cannot be used by conventional means:
* Extended local map (Every mode is supported)
* Slot independent weather (rain, snow)
* Select between cannons or warp pipes
* Rotate global maps (As seen on Figure 8 Circuit or in Yoshi Falls)
* Partial fog for both the course model and skybox model (As seen on Luigi's Mansion and Rainbow Road)

## Other features
* Fixed a bug that caused the Delfino Square slot to crash if a bridge map object instance is not present.
* Disabled ROB palette swap
* RCM Loader
* Exception handler 

# What has been released

