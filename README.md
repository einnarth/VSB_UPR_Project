# Epidemic Spread Simulator (SIR Model) 🦠

> A C program that predicts the spread of an epidemic using the mathematical SIR model and compares it with real-world data via SVG visualization.

This project simulates how an infection spreads through a population based on custom input parameters. It reads actual historical data from a CSV file, calculates the theoretical spread using the SIR (Susceptible, Infectious, Recovered) model, and generates a comparative graph.

## ✨ Features & Program Flow
- **CLI Configuration:** Parses command-line arguments to set simulation parameters dynamically.
- **Data Processing:** Reads and extracts real epidemic data from a provided `.csv` file.
- **SIR Simulation:** Computes the mathematical model using dynamically allocated arrays to store daily ratios.
- **Data Visualization:** Generates a custom `.svg` graph from scratch. Real data is plotted with a solid line, while the model's prediction uses a dashed line.
- **Precision Rendering:** Handles coordinate scaling by computing mathematical ratios in `double` and casting to `int` for pixel-accurate SVG rendering.

## 🛠️ Tech Stack
* **Language:** C
* **Concepts:** Mathematical Modeling, Dynamic Memory Allocation, File I/O (CSV parsing, SVG generation)
* **Build Tool:** Makefile
