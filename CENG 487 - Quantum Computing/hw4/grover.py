"""
This file contains the code for the Grover's algorithm example in the Qiskit
"""

import math

# Imports from Qiskit
from qiskit import QuantumCircuit
from qiskit.circuit.library import GroverOperator, MCMT, ZGate

# Imports from Qiskit Runtime
from qiskit_ibm_runtime import QiskitRuntimeService, Session


class Batch(Session):
    """Class for creating a batch mode in Qiskit Runtime."""

    pass

def grover_oracle(marked_states):
    """Build a Grover oracle for multiple marked states

    Here we assume all input marked states have the same number of bits

    Parameters:
        marked_states (str or list): Marked states of oracle

    Returns:
        QuantumCircuit: Quantum circuit representing Grover oracle
    """
    if not isinstance(marked_states, list):
        marked_states = [marked_states]
    # Compute the number of qubits in circuit
    num_qubits = len(marked_states[0])

    qc = QuantumCircuit(num_qubits)
    # Mark each target state in the input list
    for target in marked_states:
        # Flip target bit-string to match Qiskit bit-ordering
        rev_target = target[::-1]
        # Find the indices of all the '0' elements in bit-string
        zero_inds = [ind for ind in range(num_qubits) if rev_target.startswith("0", ind)]
        # Add a multi-controlled Z-gate with pre- and post-applied X-gates (open-controls)
        # where the target bit-string has a '0' entry
        qc.x(zero_inds)
        qc.compose(MCMT(ZGate(), num_qubits - 1, 1), inplace=True)
        qc.x(zero_inds)
    return qc

if __name__ == "__main__":
    # To run on hardware, select the backend with the fewest number of jobs in the queue
    service = QiskitRuntimeService(channel="ibm_quantum", token="<YOUR_API_TOKEN>")
    backend = service.least_busy(operational=True, simulator=False)

    marked_states = ["100001"] # 2448546 -> 33 -> 100001

    oracle = grover_oracle(marked_states)
    grover_op = GroverOperator(oracle)

    optimal_num_iterations = math.floor(
        math.pi / 4 * math.sqrt(2**grover_op.num_qubits / len(marked_states))
    )

    qc = QuantumCircuit(grover_op.num_qubits)
    # Create even superposition of all basis states
    qc.h(range(grover_op.num_qubits))
    # Apply Grover operator the optimal number of times
    qc.compose(grover_op.power(optimal_num_iterations), inplace=True)
    # Measure all qubits
    qc.measure_all()
    qc.draw(output="mpl", style="iqp")
