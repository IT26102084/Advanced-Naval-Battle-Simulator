# ⚓ Advanced Naval Battle Simulator

A C-based naval combat simulation program that models a **Battleship (B)** against multiple **Escort Ships (E)** using projectile motion, configurable ship properties, power degradation, and strategic attack-order logic.

This project was developed as part of the **Programming Methodology** coursework at **SLIIT**.

---

## 📌 Project Overview

The **Advanced Naval Battle Simulator** is a command-line simulation that represents a naval combat scenario between one Battleship and multiple Escort Ships.

The simulator uses mathematical and programming concepts to calculate projectile motion, determine attack outcomes, update ship power, and manage the simulation through an interactive menu-driven interface.

The project focuses on applying fundamental C programming concepts to a realistic simulation problem.

---

## 🎯 Objectives

The main objectives of this project are to:

* Simulate combat between a Battleship and Escort Ships.
* Apply projectile motion equations to calculate firing outcomes.
* Allow users to configure simulation parameters.
* Model the effect of repeated firing on ship power.
* Implement strategic attack-order selection.
* Store and retrieve simulation data using files.
* Provide an interactive command-line user interface.
* Apply structured programming techniques using the C language.

---

## 🚢 Main Components

### Battleship

The Battleship is represented by **B** and has configurable properties such as:

* Ship type / notation
* Position
* Gun properties
* Firing parameters
* Power
* Power degradation

### Escort Ships

Escort Ships are represented by **E** and can include different ship types.

Each Escort Ship can have different:

* Ship type
* Position
* Power
* Gun properties
* Firing parameters
* Power degradation values

---

## ⚙️ Main Features

### 1. Simulation Setup

Users can configure the parameters required for the simulation, including:

* Battleship properties
* Escort Ship settings
* Projectile parameters
* Power degradation parameters
* Simulation settings

### 2. Projectile Motion

The simulator applies projectile motion equations to model firing between ships.

The calculations consider parameters such as:

* Initial velocity
* Firing angle
* Gravity
* Horizontal distance
* Projectile trajectory

### 3. Strategic Attack Order

The simulator determines the order in which targets are attacked based on the configured simulation strategy.

This allows the simulation to represent a more structured combat scenario rather than using a completely random attack sequence.

### 4. Power Degradation

Repeated firing affects the impact power of ships.

The simulator models this degradation using a power-law based approach, allowing ship effectiveness to decrease as the number of firing actions increases.

### 5. Simulation Statistics

After a simulation, the system can display information such as:

* Number of shots
* Successful hits
* Missed shots
* Remaining ships
* Ship power
* Simulation results

### 6. File Handling

The simulator supports file-based data management for storing simulation information such as:

* Configuration data
* Saved simulation data
* Simulation logs

### 7. Interactive Menu

The program provides a menu-driven command-line interface with options such as:

```text
1. Start Simulation
2. View Instructions
3. Simulation Statistics
4. Exit
```

Additional setup and configuration menus are provided within the simulation workflow.

---

## 🛠️ Technologies Used

| Technology     | Purpose                   |
| -------------- | ------------------------- |
| C              | Main programming language |
| GCC            | Compilation               |
| Linux / Ubuntu | Development environment   |
| Git            | Version control           |
| GitHub         | Source code management    |

---

## 📂 Project Structure

```text
Advanced-Naval-Battle-Simulator/
│
├── include/
│   ├── sim.h
│   ├── tui.h
│   └── file.h
│
├── src/
│   ├── main.c
│   ├── sim.c
│   ├── tui.c
│   └── file.c
│
├── data/
│   ├── config.txt
│   ├── savegame.txt
│   └── simulation.log
│
└── README.md
```

> The exact files and folders may change as the project develops.

---

## 🧠 Programming Concepts Used

This project demonstrates several fundamental C programming concepts:

* Variables and data types
* Functions
* Structures (`struct`)
* Arrays
* Pointers
* Conditional statements
* Loops
* Enumerations
* Header files
* Modular programming
* File handling
* Mathematical calculations
* Random number generation
* Input validation
* Command-line user interfaces

---

## 🧮 Mathematical Model

Projectile motion is modelled using standard equations.

For example, the horizontal component of velocity is:

```text
Vx = V₀ cos(θ)
```

The vertical component is:

```text
Vy = V₀ sin(θ)
```

Where:

* `V₀` = Initial projectile velocity
* `θ` = Firing angle

The projectile calculations are used to determine whether a fired projectile can reach the target.

---

## 💻 Compilation

Make sure GCC is installed on your system.

### Clone the repository

```bash
git clone https://github.com/IT26102084/Advanced-Naval-Battle-Simulator.git
```

### Enter the project directory

```bash
cd Advanced-Naval-Battle-Simulator
```

### Compile

```bash
gcc src/main.c src/sim.c src/tui.c src/file.c -Iinclude -lm -o naval_simulator
```

### Run

```bash
./naval_simulator
```

---

## 🖥️ Development Environment

The project was developed and tested using:

* **Ubuntu / Linux**
* **GCC Compiler**
* **Visual Studio Code**
* **Git & GitHub**

---

## 📊 Simulation Flow

```text
Start Program
      │
      ▼
 Main Menu
      │
      ├── Start Simulation
      │       │
      │       ▼
      │   Simulation Setup
      │       │
      │       ├── Battleship Properties
      │       ├── Escort Ship Settings
      │       └── Simulation Parameters
      │
      ▼
 Run Simulation
      │
      ├── Calculate Projectile Motion
      ├── Determine Attack
      ├── Update Ship Power
      ├── Update Ship Status
      └── Record Results
      │
      ▼
 Simulation Statistics
      │
      ▼
     Exit
```

---

## 🎓 Academic Purpose

This project was developed to demonstrate the practical application of programming concepts learned in the **Programming Methodology** module.

It combines:

* C programming
* Data structures
* Mathematical modelling
* Algorithms
* File handling
* User interface design
* Simulation logic

The project is intended for **educational and academic purposes**.

---

## 👨‍💻 Author

**Senith Kuruvitage**

BSc (Hons) in Computer Science
Sri Lanka Institute of Information Technology (SLIIT)

GitHub:
https://github.com/IT26102084

---

## 📜 License

This project is developed for academic purposes.
