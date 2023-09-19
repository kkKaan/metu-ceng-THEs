# C Programming Assignments

## Assignment 1

This README file provides an overview and explanation of the code for the "Individual Image Processing" assignment.

### Table of Contents

1. [Introduction](#introduction)
2. [Code Overview](#code-overview)
3. [Usage](#usage)
4. [Notes](#notes)

### Introduction

The provided code (`the1.c`) is designed for individual image processing. It includes functions to manipulate pixel values in a 2D array representing an image.

### Code Overview

The code for this assignment includes the following key elements:

- **Global Variables:** Various global variables are declared to store pixel coordinates, colors, and other parameters used for image processing.

- **Neighbour Finder Function:** The `neighbourFinder` function recursively identifies suitable positions in the image based on color matching and boundaries.

- **Main Function:** The `main` function reads input data, including image pixel values, operation type, and parameters for various image processing operations. It then executes the selected operation.

- **Operations:** The code supports three operations: "F" for Flood Fill, "P" for Copy Paste, and "R" for Rotate. These operations manipulate the image's pixel values according to given criteria.

- **Final Image Output:** After applying the selected operation, the code prints the modified image's pixel values to the console.

### Usage

To use this code, follow these steps:

1. Compile the code using a C compiler (e.g., `gcc -o image_processing the1.c`).
2. Run the compiled executable (`./image_processing`).
3. Enter input data as specified by the program.
4. The program will execute the selected operation and display the modified image.

### Notes

- The code contains comments and explanations to help you understand its functionality.
- Ensure that the input data adheres to the specified format for successful execution.
- Use this code to perform individual image processing operations such as flood fill, copy-paste, and rotation.

For any questions or clarifications regarding the code, please refer to the assignment guidelines or contact the author.

## Assignment 2
