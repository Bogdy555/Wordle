![](./Solution%20Items/ReadMe%20Resources/Banner.png)

![C++](https://badgen.net/badge/Code/C++/red?icon=github)
![GitHub contributors](https://img.shields.io/github/contributors/Bogdy555/Wordle)
![GitHub repo size](https://img.shields.io/github/repo-size/Bogdy555/Wordle)


A clone of the game Wordle and a bot that can solve it.

# Contents

1. [Description](#description)
2. [Statistics](#statistics)
3. [Getting started](#gettingstarted)
4. [How to use](#howtouse)
5. [Key features](#keyfeatures)
6. [Team](#team)
7. [Learning resources](#learningresources)

# Description <a name="description"></a>
Wordle is a desktop application developed using Win32 API and OpenGL which has support for Windows 7 and higher, available on x86 and x64. The solver uses information theory to give the best guess at all times.

# Statistics <a name="statistics"></a>

__Bot specs:__

* Average guesses per word: 4.38214
* Time of processing the entire list of words: aprox. 1h (depending on hardware)

__App specs:__

* Average CPU consumption: 3% using Intel i7 8th gen 4 cores 8 threads with DDR4 memory
* Average GPU consumption: 15% using Intel UHD Graphics 620
* Constantly exceeds 60 fps on mid tier hardware



# Getting started <a name="gettingstarted"></a>
1. The repo has no modules and there is no recursive submodule cloning required.
1. Clone the repo and build using MSVC. We are not using a make system and we are relaying on Visual Studio to compile.
1. As long as it finds the WordleBot.exe in the path, the working directory is irrelevant.

# How to use <a name="howtouse"></a>
For an official copy of the binaries you can go to our github repo where you can find our releases.
When you open the app there will be a console in which there are 3 commands available:

* RUN GAME - opens the menu in which the user can play
* RUN BOT  - opens the menu in which the bot is playing and there is also a loading bar on the left side
* EXIT - closes the application

If the input in the console in wrong, the outline of the box will have a red flashing animation. Also when playing the game, if the word is not in the database the box will have a wiggle effect.

After running the game or the bot , to go back to the console you need to press the ESC button. If you press ESC in the console menu , the app will close.

The app has fullscreen support, just hit the F11 key.



# Key features <a name="keyfeatures"></a>
* Interface update based on the resolution of the client region
* Adaptive refresh rate
* The OS is not allowed to enter sleep while the bot is processing the guesses
* Using 3D accelerated graphics for rendering the interface
* IPC through shared memory
* The API allows custom bot apps (they just have to communicate on the same shared mem space)
* Shell integration, save file dialogue uses the Windows shell
* Portable app, no install required
* Animations with key frames and lerping between them

# Team <a name="team"></a>

Team name: HackxFF

All members are part of group 143.

Members: 

1. [Florescu Bogdan-Ilie](https://github.com/Bogdy555) 
2. [Fologea Valentin-Alexandru](https://github.com/Mex777)
3. [Huma Stefan-Dorian](https://github.com/Steven23X)
4. [Vulpoi Gabriel](https://github.com/GVulpoi)

# Learning resources<a name="learningresources"></a>

[3Blue1Brown - Solving Wordle using information theory](https://www.youtube.com/watch?v=v68zYyaEmEA)

[Joey de Vries - Learn OpenGL](https://learnopengl.com/)

[The good ol' MSDN](https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list)
