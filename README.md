# CMP303 Network Final Project

**Student Name:** Francisco Diaz  
**Student ID:** 1902654  

## External Libraries:
- [SFML 2.5.1 (32-bit)](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)
- [ImGui](https://github.com/ocornut/imgui)
- [ImGui-SFML](https://eliasdaler.github.io/using-imgui-with-sfml-pt1/)

## Project Demonstration
- [Watch the Project Demonstration](https://youtu.be/tYNNJiDg3No?feature=shared)

## How to Run and Control This Program

**Overview:**

This project is a client-server network implementation. It uses TCP for essential game actions such as joining or exiting, and UDP for fast real-time player position updates.

### Server:
- Configure server settings, including options like fake latency.
- Click **"Run"** to start the server, and **"Stop"** to terminate it.
- The server interface displays relevant data such as the number of connected players and active games.

### Client:
- In the **Selection** screen, choose server settings, player color, and enemy prediction modes.
- Click **"Find a Game"** to connect. If the server is unavailable, the button will be disabled temporarily; otherwise, the player will be connected to an available game.
- In the **Level** screen, move the player using the **WASD** keys. To exit the level, press **"Esc"** or click the "X" button to close the game window.

## GitHub Repository
- [CMP303 Network Final Project Repository](https://github.com/FranciscoDiaz-dev/CMP303_Network_FinalProject)

