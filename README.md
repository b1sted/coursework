<p align="center">
  <img src="https://raw.githubusercontent.com/b1sted/coursework/refs/heads/main/.github/assets/logo.png" width="160" alt="signal analysis">
  <br>
    signal_analysis
  <br>
</p>

<p align="center">
  <strong>
    A comprehensive signal analysis toolset built with
    <a href="https://gcc.gnu.org/">GCC</a> and supported by
    <a href="https://wxmaxima-developers.github.io/wxmaxima/">WxMaxima</a>
  </strong>
</p>

<h2></h2>

<p align="center">
  <a href="#features"><img
    src="https://img.shields.io/badge/features-comprehensive-brightgreen"
    alt="Features"
  /></a>
  <a href="#installation--building"><img
    src="https://img.shields.io/badge/build-makefile-blue"
    alt="Build"
  /></a>
  <a href="#prerequisites"><img
    src="https://img.shields.io/badge/prerequisites-GCC%20|%20WxMaxima-orange"
    alt="Prerequisites"
  /></a>
</p>

<p align="center">
  <img src="https://github.com/b1sted/coursework/blob/main/.github/assets/screenshot.png?raw=true" width="700" />
</p>

<p align="center">
  <a href="#introduction">Introduction</a> •
  <a href="#features">Features</a> •
  <a href="#prerequisites">Prerequisites</a> •
  <a href="#installation--building">Installation</a> •
  <a href="#usage">Usage</a> •
  <a href="#file-structure">File Structure</a>
</p>

<h2></h2>

## Introduction

This project focuses on analyzing signals at the output of an electrical circuit. It provides a robust C program that calculates signal characteristics based on time, determines specific parameters like pulse edge duration, and outputs the results both to the console and to files for further analysis.

The project includes a helper Bash script to manage the execution of the C program, visualize data using WxMaxima, and access related project documents. A `Makefile` simplifies the compilation process, using a separate `build/` directory for intermediate object files.

At its core, the C program (`bin/signal_analysis`) calculates two signals, `Uvx` and `Uvix`, as functions of time `t`. `Uvx` is defined as a piecewise function of time, and `Uvix` is derived from `Uvx`.

## Features

- **Signal Calculation:** Computes `Uvx` and `Uvix` signal values over a specified time range `[tn, tk]` for a user-defined number of points `n`.

- **Parameter Calculation:** Calculates the duration of the *leading edge* of the `Uvix` signal with precision.

- **Precision Control:** Iteratively calculates the leading edge parameter with increasing numbers of points (`n`) until a desired relative precision (1%) is achieved.

- **Comprehensive Output Options:**
  - Displays calculated values in a formatted table in the console
  - Saves the calculated arrays to separate text files for further analysis
  - Supports visualization through WxMaxima

- **User-Friendly Interfaces:**
  - Interactive menu in the C program for different calculation modes
  - Helper Bash script providing a menu-driven project workflow

- **Streamlined Build Process:** Simplified compilation with organized output directories via Makefile

## Prerequisites

### For Building and Running the C Program:

- A C compiler (e.g., GCC)
- `make` utility
- The `math.h` library (linking is handled by the `Makefile`)

### For Using the `run_coursework.sh` Helper Script:

- Bash shell
- `flatpak`
- WxMaxima installed via Flatpak (`io.github.wxmaxima_developers.wxMaxima`)
- LibreOffice (`libreoffice` command)
- All necessary project files (source code, scripts, data files, WxMaxima files, report document)

## Installation & Building

Setting up the Signal Analysis project is straightforward:

1. **Compile the C code:**

   Navigate to the project's root directory and run:
   ```bash
   make
   ```
   
   This command will:
   - Compile the source code 
   - Place intermediate object files in the `build/` directory
   - Link necessary libraries
   - Create the `bin/` directory if needed
   - Place the final executable (`signal_analysis`) in the `bin/` directory

2. **Clean Build Files (Optional):**

   To remove compiled files and start fresh:
   ```bash
   make clean
   ```

## Usage

There are two main ways to run the analysis after building the project:

### 1. Direct Execution (C Program)

Run the compiled C program directly:

```bash
./bin/signal_analysis
```

The program will display a banner (`data/zast.txt`) and a menu:

```
Меню:
1. Контрольный расчет для n точек
2. Расчет параметра с заданной точностью
3. Запись данных в файл
Выберите опцию:
```

Follow the prompts. After each action, you'll be asked if you want to continue (`Хотите продолжить? (да/нет):`). Enter `да` or `нет`.

### 2. Using the Helper Script

For a more integrated experience with easy access to plotting and report files:

1. **Make the script executable (if necessary):**
   ```bash
   chmod +x scripts/run_coursework.sh
   ```

2. **Run the script:**
   ```bash
   ./scripts/run_coursework.sh
   ```

The script will perform dependency checks and display its main menu:

```
+-------------------------------------------------------+
|                                                       |
|           КУРСОВАЯ РАБОТА ПО АНАЛИЗУ СИГНАЛА          |
|                                                       |
+-------------------------------------------------------+
|                                                       |
| 1. Запустить программу расчета                        |
| 2. Построить графики в WxMaxima                       |
| 3. Открыть контрольный расчет                         |
| 4. Открыть пояснительную записку                      |
| 5. Завершить работу                                   |
|                                                       |
| Подсказка: Ctrl+C для экстренного выхода из программы |
|                                                       |
+-------------------------------------------------------+

Выберите действие [1-5]:
```

Select the desired option by typing the number and pressing Enter.

## File Structure

```
coursework-main/
├── bin/                  # Output: Compiled executable (created by make)
│   └── signal_analysis
├── build/                # Output: Intermediate object files (.o) (created by make)
├── data/                 # Data files
│   ├── array_t.txt       # Output: Time data
│   ├── array_Uvx.txt     # Output: Uvx signal data
│   ├── array_Uvix.txt    # Output: Uvix signal data
│   └── zast.txt          # Input: Banner text
├── docs/                 # Documentation (Referenced by script)
│   └── coursework_report.doc
├── include/              # C header files (.h)
│   ├── file.h
│   ├── forming.h
│   ├── input.h
│   ├── output.h
│   └── parameter.h
├── scripts/              # Helper scripts
│   └── run_coursework.sh
├── src/                  # C source files (.c)
│   ├── file.c
│   ├── forming.c
│   ├── input.c
│   ├── signal_analysis.c # Contains main()
│   ├── output.c
│   └── parameter.c
├── wxmaxima/             # WxMaxima files (Referenced by script)
│   ├── control_calculations.wxmx
│   └── plot_data.wxmx
├── Makefile              # Build script for make
└── README.md             # This file
```
