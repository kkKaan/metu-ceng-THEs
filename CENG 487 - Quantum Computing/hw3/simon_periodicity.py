"""
This file contains the code to create a Simon circuit for a given bit string.
"""

from qiskit import QuantumCircuit
from qiskit_textbook.tools import simon_oracle

def create_simon_circuit(b):
    n = len(b)
    simon_circuit = QuantumCircuit(n * 2, n)

    simon_circuit.h(range(n))    

    simon_circuit.barrier()
    simon_circuit &= simon_oracle(b) # Adding the oracle to the circuit
    simon_circuit.barrier()

    simon_circuit.h(range(n))
    simon_circuit.measure(range(n), range(n))

    return simon_circuit


if __name__ == "__main__":
    # Define the string 'b' for the Simon oracle
    b = '1010'

    # Create the Simon circuit
    simon_circuit = create_simon_circuit(b)

    # Draw and print the circuit
    print(simon_circuit.draw())
