KEngine
=======

My 2D game engine side project, along with a in-development game that's being developed in parallel.

The engine is currently going through it's 5th iteration.

----------------
| Known Issues |
----------------
 - When compiling using the VS12 solution. The obj files will be in folders out of the repo directry.
   (There's no source folder contamination from the .obj files but there will be these weird directories kind of all over the place. Albeit away from rest of the repo

---------------------
| Development Cycle |
---------------------
 - Release/Commit stage:
	dev-branches ==> master ==> STABLE ==> GOLD ==> LIVE
	
	- master: Merge branch for all dev branches.
	- STABLE: No known major/minor issues. No interface breaking updates
	- GOLD: Ready-to-release/preview/close-to-release
	- LIVE: Released builds/source-code

----------------------------
| Building for development |
----------------------------
 - Compile all libraries in the lib directory in source.
   - This will create all the .lib .dll and .pdb files.
 - Compile KEngine and ProjectK.
