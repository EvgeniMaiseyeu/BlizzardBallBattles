BlizzardBallBattle

#Setup For Windows
1) Open the project in Visual Studio
	* Debug
	* x86 (The given DLLs only support x86 not x64)
2) If an error appears over upgrading the toolset, select "Do Not Upgrade"
	* Works with v140 and v141, but most testing is done not upgrading the toolset
3) If an error appears over targetting a windows version, retarget to latest SDK
	* Above version 10
4) Compile the program
5) When successful, a bunch of DLL errors will appear
	* Go to "RequiredDLLsForWindows" folder and copy all DLL's into the directory of the exe
		* The "Debug" folder created at root

#Setup For Mac

1) Install Brew:
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

2) Using brew, install the following in this order:
brew install sdl2
brew install sdl2_image
brew install sdl2_net
brew install sdl2_mixer
brew install glew
brew cask install xquartz
brew install freeglut
brew install glfw

#How To Play Offline
When the game starts, press "2" for a two-player offline game.

In AI selection screen, three AI types are given and players pick the displayed key associated with the AI type they want

#How To Play Online
When launching the game, launch it from command line and pass it an argument which is the IP of who you wish to connect with
	* e.g. "BlizzardBallBattle.exe 192.168.43.102"
	* Optionally, a second parameter for "port" can be passed as well
	
If a player wishes to be the host, they select the H key in the home screen.
If a player wishes to be the guest, they select the J key in the home screen.

Note:
- The joining player can only join when the host has already clicked the H key to start.

#Controls
Player 1:
* WASD to move
* Press space to pickup snowball
* Press space when holding a snowball to throw it
	* Holding space longer before releasing it will increase the power you throw your snowball with
* Hold X to charge up big snowball
* When big snowball is charged, rapidly press X to charge up and fire the big snowball

Player 2:
* Up/Down/Left/Right arrow keys to move
* Press the right control button to pickup snowball
* Press the right control button when holding a snowball to throw it
	* Holding the right control button longer before releasing it will increase the power you throw your snowball with
* Hold the zero button on the numpad to charge up big snowball
* When big snowball is charged, rapidly press the zero button on the numpad to charge up and fire the big snowball