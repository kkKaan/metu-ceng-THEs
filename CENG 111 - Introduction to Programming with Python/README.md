# The2 Assignment: Simulation of Individual Movement and Infection

This README file provides an overview and explanation of the code for the "the2" assignment. The code simulates the movement of individuals on a grid, considering factors such as infection transmission, masks, and probabilities.

## Table of Contents

1. [Introduction](#introduction)
2. [Code Overview](#code-overview)
3. [Usage](#usage)
4. [Notes](#notes)

## Introduction

The "the2" assignment involves simulating the movement and interaction of individuals on a grid. Each individual occupies a cell on an M × N grid, with various parameters affecting their movement and infection status.

## Code Overview

The code provided (`the2.py`) implements the simulation using the `new_move()` function. Here's a breakdown of the code:

1. Importing Libraries and Modules:
    - The code imports the necessary modules including `math`, `random`, and `evaluator` to retrieve input data.

2. Initialization and Constants:
    - The code initializes the `moves` list and extracts the constants and individual data using the `get_data()` function.

3. Movement Calculation (`new_move()` Function):
    - The `new_move()` function calls `new_move_helper()` to calculate the next positions of individuals.

4. `new_move_helper()` Function:
    - This function calculates the next positions and infection statuses for individuals.
    - It uses probabilities defined in the assignment specifications for different movement types.

5. Movement Calculations:
    - The code iterates through each individual, calculating the next position based on the chosen movement type.
    - It considers boundary constraints and checks if the calculated position is already occupied by another individual.

6. Infection Transmission:
    - The code calculates infection transmission probabilities between individuals based on their distances and mask usage.
    - It updates infection statuses of individuals based on interactions, considering infection states and mask usage.

7. Universal State Update:
    - The code updates the universal state of the population, incorporating new positions, movement types, mask statuses, and infection statuses.

## Usage

1. Use the `new_move()` function in the `the2.py` file.
2. Follow the given structure of the `new_move_helper()` function to calculate next positions and infection statuses.
3. Ensure that the `get_data()` function from `evaluator.py` is available to retrieve input data.
4. The code automatically follows the specified looping order for evaluating movements and infections.

## Notes

- The code adheres to the guidelines provided in the assignment, including movement probabilities and infection transmission.
- Only import modules specified in the assignment: `math` and `random`.
- The `evaluator.py` file is used to obtain input data and is not submitted.
- Ensure the code follows the assignment's constraints and specifications for proper evaluation.

