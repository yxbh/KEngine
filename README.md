KEngine
=======

My 2D game engine side project.
The engine is currently going through it's 5th iteration.

To see it in use, check out my ProjectK repository.

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
The engine is built as a library. A VS12 solution is provided.

The engine has the follow dependencies:
 - SFML 2.x
 - Box2D (not yet required)

Compile steps:
 - If provided, compile all libraries in the lib directory in the Source directory. Otherwise you will have to get them yourself.
   - This will create all the .lib .dll and .pdb files.
 - Compile KEngine and ProjectK.
 
In the future, CMake files will be added to make this easier for everyone.

----------------------------------
| Building Doxygen Documentation |
----------------------------------
Run Doxygen on the provided doxyfile.
 
-----------
| License |
-----------
The source is currently available under the zlib license.