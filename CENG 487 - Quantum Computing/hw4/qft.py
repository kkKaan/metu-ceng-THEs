"""
This file contains the code for the Quantum Fourier Transform
"""

from qiskit import QuantumCircuit
import math

# Function to apply a single-qubit QFT rotation to the circuit
def apply_qft_rotations(circuit, n):
    """Apply QFT rotations to the first n qubits in circuit"""
    if n == 0:
        return circuit
    n -= 1
    circuit.h(n)
    for qubit in range(n):
        circuit.cp(math.pi/2**(n-qubit), qubit, n)
    apply_qft_rotations(circuit, n)

# Function to reverse the order of qubits for the final state
def swap_registers(circuit, n):
    for qubit in range(n//2):
        circuit.swap(qubit, n-qubit-1)
    return circuit

if __name__ == "__main__":
    # Create a 6-qubit Quantum Circuit for the QFT
    num_qubits = 6
    qc = QuantumCircuit(num_qubits)

    # Initialize the qubits according to the bitstring
    bitstring = '100001'[::-1]  # Reversing the binary string to match Qiskit's order
    for i, bit in enumerate(bitstring):
        if bit == '1':
            qc.x(i)

    # Apply the QFT rotations
    apply_qft_rotations(qc, num_qubits)

    # Swap the qubits if required (as per QFT's usual implementation)
    swap_registers(qc, num_qubits)

    # Show the circuit
    print(qc.draw())
