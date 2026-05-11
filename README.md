# NitroKart-Loader

This is a partial source code release for Nitro Kart Loader, a modding framework for Mario Kart DS

# Features

## Custom Track Information file (course_info.nkldr)

Makes it so that course attributes that are normally hardcoded or baked into the ARM9 binary are instead loaded from a binary blob inside of the course archive.
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

* Fixed an arbitrary condition that caused the Delfino Square slot to crash if a bridge map object instance is not present.
* Disabled ROB palette swap
* RCM Loader (made by @Garhoogin)
* Exception handler

# Planned features

* Custom characters/karts loader/manager
* Make shyguy selectable on the character select screen
* Custom weather achieved by loading a .spa file from the course archive
* Extended cannon types (Such as fast cannons, or warp pipes that work more similarly to portals)
* Add more attributes to info file format
* Author credits on course intro / race intro on VS


The following set of features is not confirmed, their inclussion is not warranted 
* Custom cup manager
* MyStuff folder 
* Sectioned tracks (Like Mount Wario)
* 200cc

# What has been released so far

* Custom Track information file (course_info.nkldr)

# Note
NitroKart Loader restricts online play to friend lobbies, this is to prevent interference with the vanilla game
