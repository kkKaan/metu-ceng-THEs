from qiskit import QuantumCircuit, Aer, execute
from qiskit.visualization import plot_histogram
import matplotlib.pyplot as plt

id = '100001'

qc = QuantumCircuit(len(id), len(id))

for i, bit in enumerate(id):
    if bit == '1':
        qc.x(i)

# Applying Quantum Fourier Transform
qc.h(0)
qc.cp(3.14159/2, 0, 1) # CU1(pi/2) from qubit 0 to qubit 1
qc.h(1)
qc.cp(3.14159/4, 0, 2) # CU1(pi/4) from qubit 0 to qubit 2
qc.cp(3.14159/2, 1, 2) # CU1(pi/2) from qubit 1 to qubit 2
qc.h(2)
qc.cp(3.14159/8, 0, 3) # CU1(pi/8) from qubit 0 to qubit 3
qc.cp(3.14159/4, 1, 3) # CU1(pi/4) from qubit 1 to qubit 3
qc.cp(3.14159/2, 2, 3) # CU1(pi/2) from qubit 2 to qubit 3
qc.h(3)
qc.cp(3.14159/16, 0, 4) # CU1(pi/16) from qubit 0 to qubit 4
qc.cp(3.14159/8, 1, 4) # CU1(pi/8) from qubit 1 to qubit 4
qc.cp(3.14159/4, 2, 4) # CU1(pi/4) from qubit 2 to qubit 4
qc.cp(3.14159/2, 3, 4) # CU1(pi/2) from qubit 3 to qubit 4
qc.h(4)
qc.cp(3.14159/32, 0, 5) # CU1(pi/32) from qubit 0 to qubit 5
qc.cp(3.14159/16, 1, 5) # CU1(pi/16) from qubit 1 to qubit 5
qc.cp(3.14159/8, 2, 5) # CU1(pi/8) from qubit 2 to qubit 5
qc.cp(3.14159/4, 3, 5) # CU1(pi/4) from qubit 3 to qubit 5
qc.cp(3.14159/2, 4, 5) # CU1(pi/2) from qubit 4 to qubit 5
qc.h(5)

# Swap the qubits to get them in the right order for the inverse QFT
qc.swap(0, 5)
qc.swap(1, 4)
qc.swap(2, 3)

# Draw the circuit
circuit_diagram = qc.draw(output='mpl')

# circuit_diagram.show()

circuit_diagram.savefig('qft2_circuit.png')