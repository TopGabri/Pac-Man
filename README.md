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

## ⚙️ Hardware & Implementation Details

The goal was to design and implement a fully functional version of the Pac-Man game on the **LandTiger** Arm development board, featuring the **NXP LPC1768 SoC** with a **Cortex-M3** core.
The code was entirely developed in **C** (exploiting the **CMSIS**), and the physical board was programmed and debugged with Arm's **ULINK2/ME** adapter via JTAG interface, using Arm's **Keil uVision** IDE.

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

### Implementation Details

To implement the game, I had to exploit several peripherals of the LPC1768 SoC and components of the board, including:
- The 320x240 **TFT LCD display** to render the game graphics, including the maze, Pac-Man, ghosts, pellets, and score.
- The **joystick** to control Pac-Man's movement.
- **timers and interrupts** to manage game timing, Pac-Man movement, ghost movement, pellet consumption, and game over conditions.
- The **DAC** (Digital-To-Analog Converter) and the **buzzer** to play sound effects


For those who are interested, I will now go through all the development steps, referencing the associated source code (all the code is inside <a href="./code/Source/">code/Source/</a>):

- design of the **game board** and all of its elements:
  In <a href="./code/Source/Pacman/labirynth.c">labyrinth.c</a> the maze is created, using the functions to draw lines specified in <a href="./code/Source/GLCD/">GLCD</a> folder to fit exactly **240** standard pellets, and I mapped each square of 3x3 pixels of the display to a cell in a **two-dimensional array** called `labyrinth_mat`. Each cell of the matrix is assigned a value (`WALL`, `SPACE`, `STD_PILL`) depending on what object is found at the corresponding location in the maze. 

Implementing and managing Pac-Man:
implementing Pac-Man as a C struct with assigned properties (position, direction, etc.), placing it in the game board array
making it move only within the walls and not go through them
ensuring the movement was fluid and responsive, without sudden steps or glitches
managing every possible event without causing significant slowdowns or crashes

implementing and managing the ghost:
creating shortest path algorithm that was not too memory and time consuming (definitely not A*) for the ghost's movement, making it chase Pac-Man
increasing its speed over time or at certain points in the game
handling the behavior when power pellets are eaten, making the ghost vulnerable and allowing Pac-Man to eat it





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



