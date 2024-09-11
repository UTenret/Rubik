# Rubik's Cube Solver using Thistlethwaite's Algorithm

This project implements a Rubik's Cube solver using **Thistlethwaite's Algorithm**. The solver reduces any cube configuration into four phases and solves it efficiently. It includes a 3D visualization to demonstrate the solving process.

## Installation

To compile and run the solver:

```bash
git clone https://github.com/UTenret/Rubik.git
cd Rubik
make
```

## Usage

Run the solver with a valid scramble sequence. Optionally, you can disable the visualizer with the --novisualizer flag.


```bash
./RubiksCubeSolver "U F2 R' D B2 L2" [--novisualizer]
```

## Parameters:
<scramble>: A valid scramble sequence (e.g., "U F2 R' D B2 L2")
[--novisualizer]: (Optional) Disable the 3D visualizer.