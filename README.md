# Turing Machine Project

This project is developed as part of a Data Structures and Programming course at the university. It simulates various types of Turing machines, demonstrating the principles of computation theory.

## Features

- Implementation of a basic single-tape Turing machine.
- Multi-tape Turing machine support.
- Composition of Turing machines for complex operations.
- Iteration Turing machines for repetitive tasks.
- Conditional Turing machines for decision-making processes.
- Unit tests using `doctest`.
- CMake-based build system.

## Requirements

- C++ compiler
- CMake

## How to Build and Run

1. Clone the repository:
```

   git clone https://github.com/violeta-kastreva/turing_machine.git

```

2. Build the project:
```

cd turing_machine
mkdir build
cd build
cmake ..
make

```

3. Run the tests:
```

./Tests

```

## Project Structure

- **`turingmachine/`**: Contains the core implementation files for the Turing machines, including support for multi-tape, composition, iteration, and conditional operations.
- **`testFiles/`**: Holds various test files used to validate the functionality and correctness of the Turing machines.
- **`Tests.cpp`**: Contains unit tests to ensure that the Turing machines behave as expected under different scenarios.
