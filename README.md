CMP303_Coursework

Student Name: Francisco Diaz
Student ID: 1902654

External libraries:
- SFML 2.5.1 32bit: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
- ImGui: https://github.com/ocornut/imgui
- Imgui - SFML : https://eliasdaler.github.io/using-imgui-with-sfml-pt1/


* GitHub Repository: https://github.com/FMGameDev/CMP303_Coursework
* MS Stream link to video: https://web.microsoftstream.com/video/a4707351-b5c9-4f63-a904-34b827e33f06?list=studio

* How to run and control this program:
Brief Description:
Client-Server network using TCP for determinant actions such as joining or exiting a game and UDP for sending-reciving player positions.
- Server:
    - Select the server to run and the features such as fake latency, etc
    - Click "Run" when ready to run the server selected and "stop" for stop it.
    - Server data (how many players conected, games created etc) will be displayed on screen.
- Client:
    - On the Selection screen choose the server, player, colour, enemies prediction mode of calculating it, etc
    When ready click on "Find a game". This will disable the button for a few seconds if the server chosen is not available or will
    send the player to a game provided by the server.
    - On the Level Screen the player can be moved using the keyboards WASD, for exiting the level press "Esc" or click on the "X" windows button to close the game.
