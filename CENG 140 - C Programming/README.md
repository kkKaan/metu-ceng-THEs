# C Programming Assignments

## Assignment 1

This section provides explanations for the first C Programming course assignment.

### Table of Contents

1. [Introduction](#introduction)
2. [Code Overview](#code-overview)
3. [Usage](#usage)
4. [Notes](#notes)

### Introduction

The provided code (`the1.c`) is designed for basic image processing. It includes functions to manipulate pixel values in a 2D array representing an image.

### Code Overview

The code for this assignment includes the following key elements:

- **Global Variables:** Various global variables are declared to store pixel coordinates, colors, and other parameters used for image processing.

- **Neighbor Finder Function:** The `neighbourFinder` function recursively identifies suitable positions in the image based on color matching and boundaries.

- **Main Function:** The `main` function reads input data, including image pixel values, operation type, and parameters for various image processing operations. It then executes the selected operation.

- **Operations:** The code supports three operations: "F" for Flood Fill, "P" for Copy Paste, and "R" for Rotate. These operations manipulate the image's pixel values according to given criteria.

- **Final Image Output:** After applying the selected operation, the code prints the modified image's pixel values to the console.

### Usage

To use this code, follow these steps:

1. Compile the code using a C compiler (e.g., `gcc the1.c -o the1`).
2. Run the compiled executable (`./the1`).
3. Enter input data as specified by the program.
4. The program will execute the selected operation and display the modified image.

### Notes

- The code contains comments and explanations to help you understand its functionality.
- Ensure that the input data adheres to the specified format for successful execution.
- Use this code to perform individual image processing operations such as flood fill, copy-paste, and rotation.

## Assignment 2

This section provides explanations for the C Programming course Assignment 2.

### Table of Contents

1. [Introduction](#introduction)
2. [Code Overview](#code-overview)
3. [Usage](#usage)
4. [Notes](#notes)

### Introduction

The provided code (`functions.c`) is designed for handling race data, including sector times, lap times, and driver statistics. It involves reading and processing data to extract valuable insights.

### Code Overview

The code for this assignment includes the following key elements:

- **Input Processing:** The code reads input data regarding sector times, lap times, and driver positions during races.

- **Data Structures:** The code employs dynamic memory allocation to store and manipulate sector times, lap times, and driver positions efficiently.

- **Lap Time Calculation:** It calculates lap times by summing up sector times for each driver.

- **Fastest Lap Finder:** The code determines the driver with the fastest lap by comparing lap times across all drivers.

- **Driver Statistics:** It computes statistics for each driver, such as the lap number with the fastest time.

- **Sorting Functions:** The code includes functions for sorting arrays, such as the selection sort and reversal of arrays.

- **Points Calculation:** It calculates total points earned by each driver across multiple races.

- **Season Ranking:** The code ranks drivers based on their total points for the entire season.

### Usage

To use this code, follow these steps:

1. Compile the code using a C compiler (e.g., `gcc functions.c -o race`).

2. Run the compiled executable (`./race`).

3. Enter input data as specified by the program, including sector times, lap times, and driver positions.

4. The program will execute the calculations and display results such as the fastest lap, driver statistics, and season rankings.

### Notes

- The code contains comments and explanations to help you understand its functionality.

- Ensure that the input data adheres to the specified format for successful execution.

- Use this code to analyze and compute statistics for race data, including lap times and driver rankings.

## Assignment 3

This section provides explanations for the C Programming course Assignment 3.

### Table of Contents

1. [Introduction](#introduction)
2. [Code Overview](#code-overview)
3. [Usage](#usage)
4. [Notes](#notes)

### Introduction

The provided code (`the3.c`) focuses on managing apartments and flats within them. It provides functionalities to add flats, merge apartments, relocate flats, and more.

### Code Overview

The code for this assignment includes the following key elements:

- **Structures:** The code defines structures for apartments and flats, including properties like apartment name, maximum bandwidth, flat ID, and initial bandwidth.

- **Apartment Management:** It offers functions to add and remove apartments, as well as merge apartments to combine their maximum bandwidths.

- **Flat Management:** The code provides functions to add flats to apartments, make flats empty, and relocate flats to the same or different apartments.

- **Data Validation:** The code includes checks to ensure that flats do not exceed apartment bandwidth limits and can be relocated effectively.

### Usage

To use this code, follow these steps:

1. Compile the code using a C compiler (e.g., `gcc the3.c -o the3`).

2. Run the compiled executable (`./the3`).

3. Enter input data as specified by the program to manage apartments and flats.

4. The program will execute the requested operations and display relevant information.

### Notes

- The code contains comments and explanations to help you understand its functionality.

- Ensure that the input data adheres to the specified format for successful execution.

- Use this code to manage apartments, add and relocate flats, and efficiently utilize available bandwidth.

For any questions or clarifications regarding the code, please refer to the assignment guidelines or contact me.

