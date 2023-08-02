The2 Assignment: Simulation of Individual Movement and Infection
This README file provides an overview and detailed explanation of the program for the "the2" assignment. The program simulates the movement of individuals on a grid while considering factors such as infection transmission, masks, and probabilities.

Table of Contents
Introduction
Specifications
Usage
Visualizations
How to Use draw.py
Notes
Introduction
The "the2" assignment involves simulating the movement and interaction of individuals on a grid. Each individual occupies a cell on an M × N grid (with M ≤ 100 and N ≤ 100). Individuals move from one cell to a neighboring cell with probabilities determined by their previous move and certain parameters. The simulation also considers the transmission of disease between individuals, taking into account factors such as distance and mask usage.

Specifications
The specifications for the "the2" assignment are as follows:

Individuals move in an order specified by their numbering.
Each individual's move depends on their previous move and probability values.
Infection transmission probability depends on the distance between individuals and is subject to a threshold value D.
Individuals can wear masks, reducing infection transmission probability.
The simulation progresses in time frames, with new positions and infection states computed for each individual.
The new_move() function returns the next time frame's universal state.
Usage
Implement the new_move() function in the the2.py file.
Follow the given looping order to compute new positions and infection states.
Ensure that the get_data() function is available to retrieve input data.
Do not alter the looping order to prevent corruption of the evaluation process.
The program is designed to work within the constraints of concepts covered in lectures, without object-oriented programming.
Visualizations
While the program includes visualization capabilities (draw.py), these are for visualization purposes only and are not part of the grading process. The provided visualization script can help you visualize your simulation results.

How to Use draw.py
Place the2.py, draw.py, and evaluator.py in your working directory.
Run draw.py using Python. It imports the2.py and evaluator.py.
Modify the DELAY variable in draw.py to adjust the delay between successive new_move() calls.
Note that draw.py uses a coordinate system with the origin at the top-left corner.
Notes
Implement the new_move() function following the specifications provided.
The input data is error-free and can be retrieved using the get_data() function.
Only import from the math and random modules. Do not import from other files/libraries.
Make sure to adhere to the specified looping order and interaction rules.

