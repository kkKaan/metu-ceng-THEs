"""
This file contains the circuits for the Shor code and the phase gate.
"""

from qiskit import QuantumRegister, ClassicalRegister, QuantumCircuit
from numpy import pi

# Just a simple function for using phase gate
def create_circuit_phase():
    qreg_q = QuantumRegister(1, 'q')
    creg_c = ClassicalRegister(1, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    circuit.reset(qreg_q[0])
    circuit.h(qreg_q[0])
    circuit.p(46 * pi / 33, qreg_q[0]) # Theta can be changed, it is not important
    circuit.h(qreg_q[0])
    circuit.measure(qreg_q[0], creg_c[0])
    
    return circuit

def create_circuit_9qbit_shor():
    qreg_q = QuantumRegister(9, 'q')
    creg_c = ClassicalRegister(1, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    # Reset all qubits
    for i in range(9):
        circuit.reset(qreg_q[i])

    circuit.h(qreg_q[0])
    circuit.p(46 * pi / 33, qreg_q[0])
    circuit.h(qreg_q[0])

    circuit.barrier()

    circuit.cx(qreg_q[0], qreg_q[3])
    circuit.cx(qreg_q[0], qreg_q[6])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[3])
    circuit.h(qreg_q[6])

    circuit.cx(qreg_q[0], qreg_q[1])
    circuit.cx(qreg_q[3], qreg_q[4])
    circuit.cx(qreg_q[6], qreg_q[7])

    circuit.cx(qreg_q[0], qreg_q[2])
    circuit.cx(qreg_q[3], qreg_q[5])
    circuit.cx(qreg_q[6], qreg_q[8])

    circuit.barrier()
    # The error injection
    circuit.x(qreg_q[0]) 
    circuit.z(qreg_q[0])

    circuit.barrier()

    circuit.cx(qreg_q[0], qreg_q[1])
    circuit.cx(qreg_q[3], qreg_q[4])
    circuit.cx(qreg_q[6], qreg_q[7])

    circuit.cx(qreg_q[0], qreg_q[2])
    circuit.cx(qreg_q[3], qreg_q[5])
    circuit.cx(qreg_q[6], qreg_q[8])

    circuit.ccx(qreg_q[2], qreg_q[1], qreg_q[0])
    circuit.ccx(qreg_q[5], qreg_q[4], qreg_q[3])
    circuit.ccx(qreg_q[8], qreg_q[7], qreg_q[6])

    circuit.h(qreg_q[0])
    circuit.h(qreg_q[3])
    circuit.h(qreg_q[6])

    circuit.cx(qreg_q[0], qreg_q[3])
    circuit.cx(qreg_q[0], qreg_q[6])
    circuit.ccx(qreg_q[6], qreg_q[3], qreg_q[0])

    circuit.barrier()

    # Measure the first qubit
    circuit.measure(qreg_q[0], creg_c[0])
    
    return circuit

if __name__ == "__main__":
    # Create and display the circuits
    circuit_phase = create_circuit_phase()
    print("Circuit phase:")
    print(circuit_phase.draw())
    
    circuit_shor = create_circuit_9qbit_shor()
    print("\nCircuit Shor:")
    print(circuit_shor.draw())
