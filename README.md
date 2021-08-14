________________________________________________________________________________________________________________________________________________
# DEPRECATED
## Spore-ToolImageEnforcer is now integrated with ModAPI.
Improved version of this mod is now part of the core DLLs.

________________________________________________________________________________________________________________________________________________
Old OP for achival purposes:
# Spore-ToolImageEnforcer
A small [ModAPI](https://github.com/emd4600/Spore-ModAPI) mod for Spore, allowing Space Stage Tools to have custom icons.

## About
This modification does nothing visible to the end user by itself, but it enables mod developers to use custom icons in the Toolbar in Space Stage.
Spore by default preloads all the tool icons from one `.spui` interface file, which cannot be modified without breaking mod compability.
This mod reads all additional images added to the `0x3064cb38` (aliased as `ufotools~` in [SporemodderFX](https://github.com/emd4600/SporeModder-FX)) folder and alters Spore's Window search function to include new icons.

## In practice:
__Default game behaviour:__

![mainWindowImage](./resources/exampleWithout.PNG?raw=true)

__With this modification:__

![mainWindowImage](./resources/exampleWith.PNG?raw=true)

### How to use:
If you're a mod developer and want to use custom icons, simply add your `.png` images into `0x3064cb38 (ufotools~)` folder and use their `ResourceKey` in `spaceToolImageID` property.

## Attention!
_Compilations available here are intended for mod developers. Build for general audiences hasn't been released yet._

________________________________________________________________________________________________________________________________________________
# DEPRECATED
## Spore-ToolImageEnforcer is now integrated with ModAPI.

________________________________________________________________________________________________________________________________________________
