# Algorithm Benchmark

This project provides a tool for benchmarking three of the most common sorting algorithms and two of the most common search algorithms. It allows users to evaluate the performance of these algorithms under different conditions and provides timing and time complexity analysis.

## Features

- **Sorting Algorithms**:
  - Benchmarks three sorting algorithms.
  - Allows selection of the best, worst, or average-case scenarios.

- **Search Algorithms**:
  - Benchmarks two search algorithms.
  - Includes case-specific performance evaluations.

- **Timing and Complexity Analysis**:
  - Records the time taken to execute the selected algorithm.
  - Outputs a time complexity analysis alongside the timing data.

## Requirements

- A C++ compiler supporting C++11 or later.
- GNU Make (if using the `Makefile`).

## Installation

1. Clone the repository:
   ```bash
   git clone git@github.com:SilasvanderWaal/AlgorithmBenchmark.git
   ```
2. Navigate to the project directory:
   ```bash
   cd AlgorithmBenchmark
   ```

## Usage

1. Compile the project using the provided `Makefile`:
   ```bash
   make
   ```

2. Run the program:
   ```bash
   ./build/main
   ```

3. Follow the on-screen instructions to:
   - Select the desired algorithm (sorting or searching).
   - Specify the case (best, worst, or average).
   - View the timing results and complexity analysis.

## File Structure

- **`include/`**: Contains header files for the algorithms and utility functions.
- **`src/`**: Contains the source code implementing the algorithms and benchmarking logic.
- **`Makefile`**: Automates the build process.
- **`.vscode/`**: Optional Visual Studio Code configuration files for development.
