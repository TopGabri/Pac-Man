# 🟡 Pac-Man 

Welcome to the **Pac-Man Project** — a recreation of the iconic 1980 arcade game, implemented on the **LandTiger board** featuring the **NXP LPC1768 SoC**.

---

## 🎓 About the Project

This project was developed by myself as an **assignment for up to 4 bonus points** in the *Computer Architectures* course, during my **first year of the Master’s degree in Computer Engineering** at **Politecnico di Torino**.

The challenge was to **fully implement Pac-Man** — the classic Japanese videogame — not on a PC, but on embedded hardware.  
You can try the original online version here: [freepacman.org](https://freepacman.org/).

---

## ⚙️ Hardware & Implementation Details

We programmed the **LPC1768 SoC** (by **NXP**) in **C**, using the peripherals available on the **LandTiger** development board to recreate a complete gaming experience.

### Features Implemented
- 🎮 Joystick to control Pac-Man's moves  
- 🖥️ LCD display rendering (custom graphics routines) 
- 🔊 Buzzer sound effects 
- 🟢 Real-time game logic with walls, pills, a ghost chasing us, scoring and a countdown timer 

---

## 📹 Demo

Curious to see the result?  
👉 Check out the gameplay here: [YouTube Link](https://www.youtube.com/)

---

## 🧩 Provided Material & Dependencies

For this assignment, we were given **a set of helper functions** to interface with the board peripherals — for example, functions to:
- Turn LEDs on/off  
- Read button and joystick inputs  
- Draw on the LCD display  

These were built upon **ARM’s CMSIS library** for the LPC1768 microcontroller.

Due to **copyright restrictions**, the CMSIS files and related proprietary material are **excluded** from this repository.  
You can find the official CMSIS package here:  
👉 [ARM CMSIS for LPC1768 (Keil)](https://www.keil.arm.com/devices/nxp-lpc1768/features/)

---

## ⚖️ License & Copyright ©

This project is licensed under the **Creative Commons Attribution–NonCommercial 4.0 International (CC BY-NC 4.0)** license.

This means you are free to:
- Share and adapt the code for **non-commercial** purposes
- Credit must be given to the original author: **Gabriele Arcidiacono**

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
![License](https://img.shields.io/badge/license-All%20Rights%20Reserved-red)

