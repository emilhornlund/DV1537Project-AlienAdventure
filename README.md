# DV1537Project-AlienAdventure
My ambition was to write a simple side-scrolling game as a project in one of my early c++ courses at Blekinge Institute of Technology back in 2016.

It uses SFML and TinyXML2, is solely written in c++11 and builds using cmake.

**Some of the project requirements**
- The program should be composed of 5-10 custom classes.
- File management (read from and write to file) should be included (if applicable).
- Inheritance should be included (if relevant).
- The project should use SFML for the graphic part if you are doing a moving graphics game and Qt if you are doing a GUI application.
- The result should be a well-functioning and well-documented application / game based on object-oriented principles.

*I may have over-killed it :)*

## Building from Source

    git clone --recursive https://github.com/emilhornlund/DV1537Project-AlienAdventure.git
    mkdir DV1537Project-AlienAdventure/build
    cd DV1537Project-AlienAdventure/build
    cmake ..
    make && make install
    ./game/AlienAdventure

**Tested on**
- macOS Mojave (10.14.2), SFML (2.4.2), CMake (3.13.4)
- Ubuntu (18.10), SFML (2.5), CMake (3.12.1)

## Screenshots

![Screenshot01](https://github.com/emilhornlund/DV1537Project-AlienAdventure/raw/master/ScreenShot01.png)
![Screenshot01](https://github.com/emilhornlund/DV1537Project-AlienAdventure/raw/master/ScreenShot02.png)