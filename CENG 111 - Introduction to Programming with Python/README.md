# Assignments the2 and the3: Individual Movement, Infection, and Parts Inventory

This README file provides an overview and explanation of the codes for the "the2" and "the3" assignments. The codes involve simulating the movement of individuals on a grid and constructing a parts inventory using a tree-structured database.

## Table of Contents

1. [Introduction](#introduction)
2. [the2 Code Overview](#the2-code-overview)
3. [the3 Code Overview](#the3-code-overview)
4. [Usage](#usage)
5. [Notes](#notes)

## Introduction

Both the2 and the3 assignments involve simulating complex scenarios using Python code. The "the2" assignment simulates individual movement and infection transmission on a grid, while the "the3" assignment constructs a parts inventory using a tree-structured database.

## the2 Code Overview

The code provided for "the2" (`the2.py`) implements a simulation of individual movement and infection transmission. Here's a brief breakdown of the code:

- Initialization and Constants: Constants and individual data are initialized using the `get_data()` function.
- Movement Calculation: The `new_move()` function calculates the next positions of individuals based on probabilities and movement types.
- Infection Transmission: Infection probabilities are calculated based on distances and mask usage. Infection statuses are updated for interactions.
- Universal State Update: The universal state of the population is updated with new positions, movement types, mask statuses, and infection statuses.

## the3 Code Overview

The code provided for "the3" (`the3.py`) constructs a parts inventory using a tree-structured database. Here's a brief breakdown of the code:

- Tree Creation: The `tree_creator()` function constructs a tree structure from nested lists, defining assemblies and basic parts.
- Root Finding: The `rootFinder()` function identifies the root node of the tree structure, ensuring a consistent order.
- Root Ordering: The `makeTheRootFirst()` function orders nodes from the outermost level to the innermost level while placing the root node first.
- Calculation of Total Price: The `calculate_price()` function calculates the total price of the composite object based on part quantities and unit prices.
- Required Parts Extraction: The `required_parts()` function extracts the required parts for the composite object as tuples of quantities and basic parts.
- Stock Check: The `stock_check()` function performs stock control by calculating the shortage of basic parts and returning a list of tuples indicating shortages.

## Usage

### the2 Assignment
1. Implement the `new_move()` and `new_move_helper()` functions in the `the2.py` file.
2. Use the provided constants, probabilities, and movement types to calculate next positions and infection statuses.
3. Ensure the `evaluator.py` file is available for data retrieval.

### the3 Assignment
1. Implement the functions `tree_creator()`, `rootFinder()`, `makeTheRootFirst()`, `calculate_price()`, `required_parts()`, and `stock_check()` in the `the3.py` file.
2. Construct a tree structure based on the given nested list format.
3. Calculate the total price, extract required parts, and perform stock checks using the provided algorithms.

## Notes

- The provided `evaluator.py` file is used for data retrieval in both assignments and should not be submitted.
- Ensure that the implementations adhere to the assignment specifications and requirements.
- These explanations provide a high-level overview; please refer to the actual code comments for detailed information.

---

For any further assistance or clarification, feel free to reach out to the assignment's instructors.
