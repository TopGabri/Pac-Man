# 🟡 Pac-Man 

Welcome to the **Pac-Man Project** — a recreation of the iconic 1980 arcade game, implemented on the Arm's **LandTiger** development board.

---

## 🎓 About the Project

This project was developed by myself as an **extrapoint assignment** in the *Computer Architectures* course, during my **first year of the Master’s degree in Computer Engineering** at **Politecnico di Torino**.

The challenge was to **fully implement Pac-Man** — the classic Japanese videogame — not on a PC, but on **embedded hardware** (the LandTiger board).  
You can try the original online version here: [freepacman.org](https://freepacman.org/).

---

## 📹 Result

To see the gameplay on the board, check out my dedicated Portfolio Website page 👉 [here](https://topgabri.github.io/my-portfolio-website/projects/pacman.html) 

---

## ⚙️ Hardware & Features Implemented

The goal was to design and implement a fully functional version of the Pac-Man game on the **LandTiger** Arm development board, featuring the **NXP LPC1768 SoC** with a **Cortex-M3** core.
The code was entirely developed in **C** (exploiting the **CMSIS**), and the physical board was programmed and debugged with Arm's **ULINK2/ME** adapter via JTAG interface, using Arm's **Keil uVision** IDE.

---

### Features Implemented
- 🎮 Joystick to control Pac-Man's moves  
- 🖥️ LCD display rendering (custom graphics routines) 
- 🔊 Buzzer sound effects 
- 🟢 Real-time game logic with walls, pills, a ghost chasing us, scoring and a countdown timer

---

## 🧩 Provided Material & Dependencies

For this assignment, we were given **a set of helper functions** to interface with the board peripherals — for example, functions to:
- Read button and joystick inputs  
- Draw on the LCD display 
- Handle timers 

These were built upon **ARM’s CMSIS library** for the LPC1768 microcontroller.

---

## 🛠️ Implementation Details

To implement the game, I had to exploit several peripherals of the LPC1768 SoC and components of the board, including:
- The 320x240 **TFT LCD display** to render the game graphics, including the maze, Pac-Man, ghosts, pellets, and score.
- The **joystick** to control Pac-Man's movement.
- **timers and interrupts** to manage game timing, Pac-Man movement, ghost movement, pellet consumption, and game over conditions.
- The **DAC** (Digital-To-Analog Converter) and the **buzzer** to play sound effects


For those who are interested, I will now go through all the development steps, referencing the associated source code (all the code is inside <a href="./code/Source/">code/Source/</a>):

- design of the **game board** and all of its elements:
  - in <a href="./code/Source/Pacman/labirynth.c">labyrinth.c</a> the maze is created, using the functions to draw lines on the LCD display defined in the <a href="./code/Source/GLCD/">GLCD</a> folder. The maze has a regular structure and is made to fit exactly **240** standard pellets
  - With the functions defined in <a href="./code/Source/Pacman/mapping.c">mapping.c</a>, each square of 3x3 pixels of the display is mapped to a cell of `labyrinth_mat`, a **two-dimensional array** that stores the state of the game board at all times. Each cell of the matrix is assigned a value (e.g `WALL`, `SPACE`, `STD_PILL`,...) depending on what object is found at the corresponding location in the maze. 

- implementation and handling of **Pac-Man**:
    - the main character (i.e Pac-Man) is implemented as an instance of a C struct with assigned attributes (position, direction, etc.), called `CHR_TypeDef` and defined in <a href="./code/Source/Pacman/game.h">game.h</a>. 
    - its coordinates (`row`,`col`) represent its position in the `labyrinth_mat` matrix at a given time. Wherever it's at, its matrix coordinates are mapped to the corresponding pixel coordinates on the LCD display, which are used to draw it using the functions in <a href="./code/Source/Pacman/pacman.c">pacman.c</a>. By drawing it at the new position and erasing it at the old position, the perception of movement is created
    - the starting point of its movement control is the **joystick** on the board. Each direction of the joystick is connected to a **GPIO** input pin of the LPC1768 microcontroller, which is raised to high whenever the joystick is moved in the corresponding direction. The GPIO pins of the joystick are periodically polled in the interrupt handler of the **RIT** (Repetitive Interrupt Timer), defined in <a href="./code/Source/RIT/IRQ_RIT.c">IRQ_RIT.c</a>, where a good portion of the game timing logic is implemented. 
    - whenever a joystick movement in a certain direction is detected in the RIT interrupt handler, Pac-Man's coordinates are updated accordingly, and functions from <a href="./code/Source/Pacman/game.c">game.c</a> are called to handle the movement request
    - The functions in <a href="./code/Source/Pacman/game.c">game.c</a> take care of:
      - checking that the requested movement is valid, i.e that there is no wall in the direction of movement
      - check that a pellet is present in the new position, updating the score and removing the pellet from the maze if so
      - redrawing Pac-Man at the new position
      - updating the game state accordingly
- implementation and handling of the **ghost**:
    - the ghost is also implemented as an instance of the `CHR_TypeDef` struct, with its own attributes and position in the maze
    - its movement timing is handled by the **Timer 1** interrupt handler, defined in <a href="./code/Source/timer/IRQ_timer.c">IRQ_timer.c</a>, which is set to trigger at regular intervals to update the ghost's position
    - its movement logic is implemented in <a href="./code/Source/Pacman/ghost.c">ghost.c</a>, where functions are defined to compute the ghost's **path** towards Pac-Man, update its position, **draw** it on the display and handle **collisions**
    - the path of the ghost is computed using a custom **shortest path algorithm** that considers the maze structure and avoids walls, and it is periodically updated to adapt to Pac-Man's changing position
    - **collision** **detection** between Pac-Man and the ghost generates the assertion of a variable called `hit`, which is then handled in the RIT interrupt handler to manage lives and game over conditions
    - the ghost has two modes: **chase** mode and **frightened** mode. In chase mode, it actively pursues Pac-Man, while in frightened mode (triggered when Pac-Man eats a power pellet), it moves in a random manner for a limited time before returning to chase mode
    - the **speed** of the ghost is increased over time (with 3 levels of difficulty), by reducing the number of Timer 1 interrupts that must pass before updating its position, making the game progressively more challenging

---

## 📈 Skill and Experience Gained

This project allowed me to strengthen a broad set of technical skills:

- Embedded Programming and Firmware Development
- Game Design and problem solving applied to Low Level Programming
- System Design thinking
- Microcontroller Peripherals and Low Level Hardware
- Debugging and MCU Development Workflow
- C programming

---

## ⚖️ License & Copyright ©

This project is licensed under the **Creative Commons Attribution–NonCommercial 4.0 International (CC BY-NC 4.0)** license.

This means you are free to:
- Share and adapt the code for **non-commercial** purposes
- Credit must be given to the original author

Commercial use of any part of this project is **not allowed**.

👉 [Read the full license](https://creativecommons.org/licenses/by-nc/4.0/)

---

## 🧠 Educational Purpose

This project was created solely for **academic and learning purposes** — exploring the intersection of **embedded systems programming** and **classic game design**.

---

## 💬 Contact

For inquiries or collaboration proposals, feel free to reach out via:

📧 [gabriarci02@gmail.com]  
🌐 [TopGabri](https://github.com/TopGabri)

![C](https://img.shields.io/badge/language-C-blue)
![Platform](https://img.shields.io/badge/platform-LandTiger%20LPC1768-lightgrey)
[![License: CC BY-NC 4.0](https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc/4.0/)



