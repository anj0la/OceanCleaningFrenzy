-- Folder Details --

Download and extract the assignment4.zip folder into your C:\ directory to view all necessary files in the cover_page.html

-- Implementation Details --

The oceancleaningfrenzy.cpp file runs the game, by creating a game object of the Game class, and calls the
start_game() method that starts the game.

The game.cpp file implements the game.h file, which defines the Game class that controls the execution of the game. This is where
you will find the interrupt handler, the objects used in the game and so forth. The game.h file includes the player.h, fish.h and trash_pool.h files,
which all implement the Player, Fish, and Trash_Pool classes respectively. They also include the sprite.h file, which is implemented in the sprite.cpp file.

-- New Additions --

There are a few new static methods that have been implemented in the game so that the game is multi-threaded (or at least somewhat multi-threaded). 
Unfortunately, C++ classes and the Pthreads library are very hard to use together, every time the game executes, a new thread is created and then joined once doing executing.
This occurs until the main thread (in the oceancleaningfrenzy.cpp file) is finished its execution.
This was one of the only ways that multi-threading could be achieved without changing the overall structure of the game.

The game also includes an Allegro datafile containing all of the game's resources. 
Instead of using the pathname to locate the resource, the datafile is loaded into the game, and the resource is grabbed from the datafile by using the pre-defined object names in the datafile.h header file.

Lastly, AI was implemented into this game by using the tracking technique. The fish now moves towards the player and is harder to avoid - thereby showing some sort of intelligence.

Therefore, 3 out of the 3 new technologies have been implemented in this game.

All methods have been documented.

-- Build Details --

The game was built on Windows 11 with Visual Studio 2022, and uses the x86 configuration instead of the x64 configuration,
as Allegro is a 32-bit library.

You can link Allegro the same way the Visual Studio guide tells you to set up Allegro with Visual Studio, although, a few changes were made.
1. When linking Allegro, make sure that adding the "include" and "lib" directories to the C/C++ -> General -> Additional Include Directories
   and Linker -> General -> Additional Library Dependencies respectively, that the configuration bar above the Configuration
   Properties is set to "All Configurations".

2. Under Project Properties -> C/C++ -> General, set SDL checks to No(/sdl-) for All Configurations.

3. You'll need to add _CRT_SECURE_NO_WARNINGS in both your debug and release configurations under C/C++ -> Preprocessor -> Preprocessor Definitions, 
   for methods like strcat to work without getting those pesky warnings.

4. In Linker -> System -> SubSystem, you'll need to change the SubSystem to Windows for both configurations.

5. Under Linker -> Input -> Additional Depedencies, for each configuration, you'll need to add the corresponding allegro monolith file.
   That is, for the Debug Configuration, the path you should be using should contain the word "debug" in it 
   (i.e., C\:allegro-4.4.2-msvc-10.0\lib\allegro-4.4.2-monolith-md-debug.lib), and for the Release Configuration, the path
   you should be using should NOT contain the word "debug" in it (i.e., C\:allegro-4.4.2-msvc-10.0\lib\allegro-4.4.2-monolith-md.lib)

6. The project was throughly tested under the "Debug" Configuration, but as the Release Configuration was set up alongside the 
   Debug Configuration when setting up Allegro, the game should run under the Release Configuration as well.

7. (ONLY DO THIS IF THE GAME ISN'T RUNNING) Under Linker -> General, set Enable Incremental Linking to Yes for All Configurations. 

-- Game Execution Details --

1. The graphics and fonts are included in the project directory and contains all the graphics and fonts used in the game. 
   DO NOT move any graphics, and instead, change the path of the file in game.cpp so that it correctly grabs the graphics.
   If the game doesn't run, make sure to check out the file path as it could be the cause of the error.

2. The audio and sound effects used for the game are include in the project directory.
   DO NOT move them unless for some reason, they are not in the project directory.
   If the game doesn't run, make sure to check out the file path as it could be the cause of the error.

-- Pthreads Library --

This game uses the Pthreads library in other to achieve multi-threading. If for some reason the game does not work, try putting the pthreadsVCE.dll inside your SystemWOW64 and System32 folder. The pthreadsVCE.dll
is located in the DLL folder in the same directory as this README file.

-- Bitmaps Details --

The pencil sprite was drawn by Anjolaoluwa Aina in Photoshop. It was 100% drawn by her, and is not a reedit/recolouring.

All the images used that were not created by Anjolaoluwa Aina were collected from Freepik. Attribution is not required as a Premium user, but has been provided below nonetheless.

Background: https://www.freepik.com/premium-vector/underwater-cartoon-background-with-coral-reef-fishes_29549498.htm
The background was pixelated using a free online pixel editor, but the inital background source has been cited still.

Fish: https://www.freepik.com/premium-vector/tuna-fish-icon-pixel-art-illustration-8-bit_33501191.htm

Banana Peel: https://www.freepik.com/premium-vector/banana-peel-with-pixel-art-style_19580307.htm

Half-Eaten Apple: https://www.freepik.com/premium-vector/eaten-apple-with-pixel-art-style_18791427.htm

Water Bottle: https://www.freepik.com/premium-vector/plastic-bottle-pixel-art-style_22461236.htm

Crushed Can: https://www.freepik.com/premium-vector/set-pixel-art-junk-empty-can-isolated-white_11006006.htm

The inspiration for the diver sprite came from this image: https://www.freepik.com/free-vector/cute-diver-catching-fish-with-fishing-net-cartoon-vector-icon-illustration-science-animal-isolated_29885062.htm

However, the diver sprite was created in Adobe Photoshop 2022 by Anjolaoluwa Aina.

Game Title Font: https://www.freepik.com/premium-vector/world-environment-day-editable-text-effect-suitable-celebrate-environment-day-event_27059905.htm

-- Font Details --

Name - Marvin Round
Designer - Patrick Griffin
Website (Download) - https://www.xfonts.pro/fonts/marvin_round#google_vignette
Note - As Anjolaoluwa Aina owns Adobe Photoshop, she can use these fonts without purchasing a commerical license.

-- Sound Details --

All sounds were taken from Pixabay, which does not require attribution, but have been provided below.

Tropical Summer Music (Background Music): https://pixabay.com/music/dance-tropical-summer-music-112842/

Negative Beeps: https://pixabay.com/sound-effects/negative-beeps-6008/

Tiny Splash: https://pixabay.com/sound-effects/tiny-splash-83778/

-- Bugs -- 

After pressing Ctrl + h or Ctrl + h to invoke the help module or toggle the background music, then you press the ESC key to quit 
the game, the game does not quit unless you click on another key, like the SHIFT or Up key.
 
I tried looking online on ways to fix the bug, but it seems to be an Allegro problem, since the ENTER key works perfectly fine
after pressing Ctrl + h / Ctrl + m. The source is here: https://www.allegro.cc/forums/thread/603468

Another trick to fix the bug is to close the application and open it up again, and pressing the ESC key then works as it should.
This is not something that really impacts the game, as the game works regardless of the bug. 

