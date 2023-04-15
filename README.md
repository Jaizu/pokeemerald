# Pokémon Emerald

### Feature Branch: Dynamic In-Connection Clones

This feature branch implements a system to dynamically create in-connection clones from connecting maps. 

It started with the system similar to what FireRed has, but instead of requiring the creator to manually place these clones in PoryMap, these clones are dynamically created by scanning the map connections for objects within the view distance of the current map. If it finds any such objects, it creates FireRed style clones dynamically, appending them to the end of the EventObjectTemplate array.

Features:
- The ability to see objects from a connecting map, removing the limitation of object-free buffer-space being required between connecting maps.

Notes:
- The EventObjectTemplate array has not been expanded, meaning if you are close to the default limit of 64 EventObjectTemplates, the game will not have room to fill out objects dynamically.
	- The work around for this is to just split larger maps with more object templates into smaller sections, since now moving between maps doesn't require object free buffer zones.
- The default compiler, agbcc, does not support anonymous structs and unions like modern compilers do. As such, a different implementation involving dynamic casting is used for agbcc, so as not have to change literally all the code in the codebase. 
	- As such, if you've made any changes to the object event template struct, you will need to mirror these changes in the clone struct. Or just use a modern compiler, which is the preferrable option imo.

-----

To use this feature branch, [click here](https://github.com/tustin2121/pokeemerald/tree/pick-feature/dynamic-clones), then click on the latest commit and manually recreate the changes in your project.

Alternatively, run the following commands to cherry-pick the commit into your repo:

```shell
git fetch https://github.com/tustin2121/pokeemerald.git pick-feature/dynamic-clones --no-tags
git cherry-pick FETCH_HEAD
```
