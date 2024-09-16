# Jothly Engine
An in-development open-source game engine created by Joseph Lyons.

**THIS README IS A WORK IN PROGRESS!** It will be more organized and explain how everything in the engine works in the future, but for now here's a list of what is in the engine:
- Raylib backend, with abstractions to allow for easy switching to other game frameworks
- Component-based gameobject system
- Quaternions

Projects that have been implemented in this engine:
- Wave Function Collapse algorithm for random tile map generation, on branch waveFunctionCollapse
- Tic-Tac-Toe AI that you can play against, on branch minimax
- AI navmesh for dynamic agent movement around obstacles using A*, on branch navMesh
- Networked competitve game where two snakes fight to be the last player standing, on branch networking2

# Playing The Networked Snake Game
1) Start up 3 instances of Visual Studio, and run the project (NOTE: There's currently a bug where you may have to click Build->Clean Solution Jothly before it will run)
2) Press 0 on one of the instances to start the server
3) Press 1 on the other two instances to start the clients
4) Use WASD while focused on the client windows to move the snakes. Every second you move, your snake gets longer
5) You win by having the other person's snake head hit into your body or their own body
6) Restart by pressing space once a player has died

## Note:
If you run the project and receive linker errors, clean the Jothly project file! There is currently a bug causing linker errors whenever a change is detected in a header file. This will be fixed in a future commit.
This project is in the process of being cleaned and refactored after a semester of rapidly implementing projects in it, stay tuned for documentation / improved project architecture / editor tooling for interfacing with the engine.
