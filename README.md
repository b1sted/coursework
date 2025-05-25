<p align="center">
  <img src="https://github.com/b1sted/coursework/blob/dev/.github/assets/logo.png" width="160" alt="Signal Analysis">
</p>
<p align="center">
  <strong>
    Electrical Signal Analyzer for Electronic Circuit Outputs
  </strong>
</p>
<h2></h2>
<p align="center">
  <a href="#features"><img
    src="https://img.shields.io/badge/features-comprehensive-brightgreen"
    alt="Features"
  /></a>
  <a href="https://github.com/b1sted/coursework/actions"><img
    src="https://github.com/b1sted/coursework/workflows/build/badge.svg"
    alt="Build"
  /></a>
  <a href="#prerequisites"><img
    src="https://img.shields.io/badge/prerequisites-GCC%20|%20WxMaxima-orange"
    alt="Prerequisites"
  /></a>
  <a href="#license"><img
    src="https://img.shields.io/badge/license-MIT-green"
    alt="License"
  /></a>
</p>
<p align="center">
  <img src="https://github.com/b1sted/coursework/blob/dev/.github/assets/screenshot.png" width="700" alt="Screenshot of the helper script menu" />
</p>
<p align="center">
  <a href="#introduction">Introduction</a> •
  <a href="#mathematical-model">Mathematical Model</a> •
  <a href="#features">Features</a> •
  <a href="#prerequisites">Prerequisites</a> •
  <a href="#installation--building">Installation</a> •
  <a href="#usage">Usage</a> •
  <a href="#examples">Examples</a> •
  <a href="#report-generation">Report Generation</a> •
  <a href="#project-structure">Project Structure</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>
<h2></h2>

## Introduction

This project provides software for analyzing signals at the output of an electrical circuit. It allows calculating two main signals, $U_{in}$ (input signal) and $U_{out}$ (output signal), as functions of time, and determining various parameters of these signals.

Key capabilities include:

* Calculating signals in the time domain.
* Determining the pulse rise time duration with specified precision.
* Outputting results to the console and files.
* Visualizing data using WxMaxima.

## Mathematical Model

### Input Signal ($U_{in}$)

The input signal $U_{in}$ is defined as a piecewise function of time $t$:

$$
U_{in}(t) = \begin{cases}
    0 & \text{for } t \le t_1 \\
    a(t-t_1) & \text{for } t_1 < t \le t_2 \\
    a(t_2-t_1) - b(t-t_2) & \text{for } t_2 < t \le t_3 \\
    a(t_2-t_1) - b(t_3-t_2) - c(t-t_3) & \text{for } t > t_3
\end{cases}
$$

where the parameters are:

* $a = 20 \text{ V/s}$
* $b = 0.5 \text{ V/s}$
* $c = 17 \text{ V/s}$
* $t_1 = 10 \text{ s}$
* $t_2 = 15 \text{ s}$
* $t_3 = 45 \text{ s}$
* $t_{start} = 5 \text{ s}$ (Calculation start time)
* $t_{end} = 50 \text{ s}$ (Calculation end time)

### Output Signal ($U_{out}$)

The output signal $U_{out}$ is defined as a function of the input signal:

$$
U_{out} = \begin{cases}
    a \cdot U_{in} + b & \text{for } U_{in} \le U_{in1} \\
    a \cdot U_{in1} + b & \text{for } U_{in} > U_{in1}
\end{cases}
$$

where the parameters are:

* $a = 2$
* $b = -5 \text{ V}$
* $U_{in1} = 20 \text{ V}$

## Features

* **Signal Calculation:** Computes the values of $U_{in}$ and $U_{out}$ signals within a specified time range $[t_{start}, t_{end}]$ for a given number of points $n$.
* **Parameter Calculation:** Calculates the duration of the rising edge (rise time) of the output signal $U_{out}$ with high precision.
* **Precision Control:** Iteratively calculates the rise time parameter with an increasing number of points ($n$) until the required relative precision (1%) is achieved.
* **Multiple Output Options:**
    * Displays calculated values in a formatted table in the console.
    * Saves data arrays to separate text files for further analysis.
    * Provides visualization via WxMaxima.
* **User-Friendly Interfaces:**
    * Interactive menu in the C program to select the operating mode.
    * Auxiliary Bash script for overall project management.
* **Report Generation:** Automated creation of technical documentation in GOST format using gostdown.

## Prerequisites

**For building and running the C program:**

* A C compiler (e.g., GCC)
* The `make` utility
* Standard C libraries including `math.h` (linking is handled by the Makefile)

**For using the Bash script:**

* Bash shell
* `flatpak`
* WxMaxima installed via Flatpak (`io.github.wxmaxima_developers.wxMaxima`)
* LibreOffice (`libreoffice`) (Used by the script to open the report document)

**For report generation:**

* Windows operating system
* Microsoft Word (2010 or higher)
* Pandoc (version 2.1.1 or higher)
* pandoc-crossref filter
* PowerShell with execution policy set to allow script execution
* PT Serif, PT Sans, and PT Mono fonts

## Installation & Building

Installing the signal analysis project is straightforward:

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/b1sted/coursework.git
    cd coursework
    ```

2.  **Compile the code:**
    ```bash
    make
    ```
    This command will:
    * Compile the source code.
    * Place intermediate object files (`.o`) in the `build/` directory.
    * Link necessary libraries.
    * Create the `bin/` directory if it doesn't exist.
    * Place the final executable (`signal_analysis`) in the `bin/` directory.

3.  **Clean build files (optional):**
    ```bash
    make clean
    ```
    This removes the `build/` directory and the executable from `bin/`.

## Usage

After building the project, you can run it in two ways:

**1. Direct Execution of the C Program**

Run the compiled C program directly:

```bash
./bin/signal_analysis
```

The program will display a splash screen (from `data/zast.txt`) and a menu:

```
Меню:
1. Контрольный расчет для n точек
2. Расчет параметра с заданной точностью
3. Запись данных в файл
Выберите опцию:
```

Follow the on-screen prompts. After each action, you will be asked whether to continue or exit the program.

**2. Using the Helper Script**

For more comprehensive project management:

1.  **Make the script executable (if needed):**
    ```bash
    chmod +x scripts/run_coursework.sh
    ```

2.  **Run the script:**
    ```bash
    ./scripts/run_coursework.sh
    ```

The script will check for dependencies and display the main menu:

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
Choose the desired action by entering the corresponding number.

## Examples

**Example Signal Calculation Output**

When selecting the "Control calculation for n points" option and entering a value for $n$, the program will output a table similar to this:

```
----------------------------------------
|  №  |     t    |    Uvx   |   Uvix   |
----------------------------------------
|   0 |    5.000 |    0.000 |   -5.000 |
|   1 |    7.500 |    0.000 |   -5.000 |
|   2 |   10.000 |    0.000 |   -5.000 |
|   3 |   12.500 |   50.000 |   35.000 |
...
----------------------------------------
```

**Example Signal Plots**

After calculating and saving data to files (option 3 in the C program or via the script), the results can be visualized using WxMaxima by selecting option 2 in the helper script (`run_coursework.sh`), which uses the `wxmaxima/plot_data.wxmx` file.

## Report Generation

The project includes functionality to generate technical documentation in GOST format using the [gostdown](https://gitlab.iaaras.ru/iaaras/gostdown) tool. This allows you to create professionally formatted reports that comply with GOST 19.xxx (ЕСПД) or GOST 7.32 (Scientific Research Report) standards in docx and PDF formats.

> **Note:** This project uses gostdown created by Dmitry Pavlov, Alyona Vodolagina with the participation of Daniel Axim © 2018-2025, available at [https://gitlab.iaaras.ru/iaaras/gostdown](https://gitlab.iaaras.ru/iaaras/gostdown)

### Report Source Files

The source files for report generation are located in the `docs/src/` directory and are organized as follows:

* `otc-beginning.md` - Introduction and initial sections of the report
* `otc-main.md` - Main body of the report, including methodology and results
* `otc-end.md` - Conclusion, references, and appendices
* `photos/` - Directory containing images for inclusion in the report:
  * `calc_leading_edge.png`
  * `calculate_with_precision.png`
  * `forming_table.png`
  * `forming_Uvx.png`
  * Various numbered images (`image1.png` through `image4.png`)
  * `main.png`
  * `output_in_file.png`

These files use the Markdown format, which allows automatic numbering of sections, tables, formulas, and figures, as well as referencing all these elements from within the text.

### Report Template and Generation Tools

The gostdown system uses the following files to ensure compliance with GOST standards:

* `docs/src/demo-template-report.docx` - Template for GOST 7.32 scientific reports, including a correctly formatted title page
* `docs/src/gost-r-7-0-5-2008-numeric-iaa.csl` - Citation style language file for bibliographic references
* `docs/src/linebreaks.lua` - Lua script for handling line breaks in the generated document

These templates contain:
* Title pages
* Text formatting styles
* Other predefined document elements

### Editing Report Content

To modify the report content:

1. Edit the corresponding markdown files:
   ```bash
   nano docs/src/otc-beginning.md  # For introduction and initial sections
   nano docs/src/otc-main.md       # For main body content
   nano docs/src/otc-end.md        # For conclusion and final sections
   ```

2. Save your changes

### Prerequisites for Report Generation

The report generation requires:

* Windows with Microsoft Word (2010 or higher)
* Pandoc (version 2.1.1 or higher)
* pandoc-crossref filter
* PowerShell with proper execution policy settings
* PT Serif, PT Sans, and PT Mono fonts (recommended)

For a full installation guide, refer to the [gostdown documentation](https://gitlab.iaaras.ru/iaaras/gostdown).

### Generating the Report

The report generation process converts the Markdown files to docx format, applies the appropriate template, and also generates a PDF version. This is handled by batch and PowerShell scripts:

1. Navigate to the project's main directory
2. Use the batch file to generate the report:
   ```bash
   ./docs/src/build-otc.bat    # Executes the PowerShell script
   ```

The PowerShell script (`build.ps1`) will:
1. Use Pandoc to convert and combine the .md files
2. Apply styles from the template
3. Insert required first pages
4. Save the result in both docx and PDF formats

The generated files (`coursework_report.docx` and `coursework_report.pdf`) will be available in the `docs/src` directory. The final report document (`coursework_report.docx`) is also placed in the `docs` directory.

## Project Structure

```
coursework/
├── bin/                  # Compiled executables (created by make)
│   └── signal_analysis
├── build/                # Intermediate object files (.o) (created by make)
├── data/                 # Data files
│   ├── array_t.txt       # Output data: time values
│   ├── array_Uvx.txt     # Output data: U_in signal
│   ├── array_Uvix.txt    # Output data: U_out signal
│   └── zast.txt          # Input data: splash screen text
├── docs/                 # Project documentation and report files
│   ├── coursework_report.doc # The main coursework report document
│   └── src/           # Source files for generating documentation/report
│       ├── build-otc.bat   # Batch script for building documentation
│       ├── build.ps1       # PowerShell script for building documentation
│       ├── coursework_report.docx  # Output document (DOCX format) generated from source
│       ├── coursework_report.pdf   # Output document (PDF format) generated from source
│       ├── demo-template-report.docx # Template document
│       ├── gost-r-7-0-5-2008-numeric-iaa.csl
│       ├── linebreaks.lua 
│       ├── otc-beginning.md # Markdown source file (part 1 of document)
│       ├── otc-end.md      # Markdown source file (part 3 of document)
│       ├── otc-main.md     # Markdown source file (main part of document)
│       └── photos/         # Images used in documentation/report
│           ├── calc_leading_edge.png
│           ├── calculate_with_precision.png
│           ├── forming_table.png
│           ├── forming_Uvx.png
│           ├── image1.png
│           ├── image2.png 
│           ├── image3.png
│           ├── image4.png
│           ├── main.png
│           └── output_in_file.png
├── include/              # C header files (.h)
│   ├── file.h
│   ├── forming.h
│   ├── input.h
│   ├── output.h
│   └── parameter.h
├── src/                  # C source files (.c)
│   ├── file.c
│   ├── forming.c
│   ├── input.c
│   ├── signal_analysis.c # Contains the main() function
│   ├── output.c
│   └── parameter.c
├── scripts/              # Helper scripts
│   └── run_coursework.sh
├── wxmaxima/             # WxMaxima files
│   ├── control_calculations.wxmx # WxMaxima file for checks (if any)
│   └── plot_data.wxmx    # WxMaxima file for plotting data
├── .github/              # GitHub specific files (like assets)
│   └── assets/
│       ├── logo.png
│       └── screenshot.png
├── Makefile              # Build script for make
└── README.md             # This file
```

## Contributing

Contributions to the project are welcome! Here's how you can help:

* **Bug Reports:** If you find a bug, please create a new issue in the repository detailing the problem.
* **Feature Suggestions:** If you have ideas for improvements, create an issue describing your suggestion.
* **Submitting Changes:**
    1.  Fork the repository.
    2.  Create a new branch for your changes: `git checkout -b feature/your-feature-name`
    3.  Make your changes and commit them: `git commit -m "Add some feature"`
    4.  Push your changes to your fork: `git push origin feature/your-feature-name`
    5.  Create a Pull Request back to the main repository.
* **Code Style:** Please adhere to the existing code style for consistency.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
