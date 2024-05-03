# Jothly Engine
An in-development open-source game engine created by Joseph Lyons.

# Playing The Snake Game
1) Start up 3 instances of Visual Studio, and run the project (NOTE: There's currently a bug where you may have to click Build->Clean Solution Jothly before it will run)
2) Press 0 on one of the instances to start the server
3) Press 1 on the other two instances to start the clients
4) Use WASD while focused on the client windows to move the snakes. Every second you move, your snake gets longer
5) You win by having the other person's snake head hit into your body or their own body
6) Restart by pressing space once a player has died

## Note:
If you run the project and receive linker errors, clean the Jothly project file! There is currently a bug causing linker errors whenever a change is detected in a header file. This will be fixed in a future commit.
