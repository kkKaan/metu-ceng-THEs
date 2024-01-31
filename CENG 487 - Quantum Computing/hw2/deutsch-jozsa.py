"""
This file contains the circuits for the Deutsch and Deutsch-Jozsa algorithms.
"""

from qiskit import QuantumRegister, ClassicalRegister, QuantumCircuit

# A function to create Deutsch Algorithm circuit for f(x) = x
def create_circuit_x():
    qreg_q = QuantumRegister(2, 'q')
    creg_c = ClassicalRegister(1, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    circuit.reset(qreg_q[0])
    circuit.reset(qreg_q[1])
    circuit.h(qreg_q[0])
    circuit.x(qreg_q[1])
    circuit.h(qreg_q[1])
    circuit.cx(qreg_q[0], qreg_q[1])
    circuit.h(qreg_q[0])
    circuit.measure(qreg_q[0], creg_c[0])
    
    return circuit

# A function to create Deutsch Algorithm circuit for f(x) = 1
def create_circuit_1():
    qreg_q = QuantumRegister(2, 'q')
    creg_c = ClassicalRegister(1, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    circuit.reset(qreg_q[0])
    circuit.reset(qreg_q[1])
    circuit.h(qreg_q[0])
    circuit.x(qreg_q[1])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.measure(qreg_q[0], creg_c[0])
    
    return circuit

# A function to create Deutsch-Jozsa Algorithm circuit for f(x) = x0 ⊕ x1 ⊕ x2
def create_circuit_3xor():
    qreg_q = QuantumRegister(4, 'q')
    creg_c = ClassicalRegister(3, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    circuit.reset(qreg_q[0])
    circuit.reset(qreg_q[1])
    circuit.reset(qreg_q[2])
    circuit.reset(qreg_q[3])
    circuit.x(qreg_q[3])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.h(qreg_q[2])
    circuit.h(qreg_q[3])
    circuit.cx(qreg_q[0], qreg_q[3])
    circuit.cx(qreg_q[1], qreg_q[3])
    circuit.cx(qreg_q[2], qreg_q[3])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.h(qreg_q[2])
    circuit.measure(qreg_q[0], creg_c[0])
    circuit.measure(qreg_q[1], creg_c[1])
    circuit.measure(qreg_q[2], creg_c[2])
    
    return circuit

# A function to create Deutsch-Jozsa Algorithm circuit for f(x) = 1
def create_circuit_x1():
    qreg_q = QuantumRegister(3, 'q')
    creg_c = ClassicalRegister(2, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    circuit.reset(qreg_q[0])
    circuit.reset(qreg_q[1])
    circuit.reset(qreg_q[2])
    circuit.x(qreg_q[2])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.h(qreg_q[2])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.measure(qreg_q[0], creg_c[0])
    circuit.measure(qreg_q[1], creg_c[1])
    
    return circuit

# A function to create Deutsch-Jozsa Algorithm circuit for f(x) = x0 ⊕ x3 ⊕ (x1 · x2)
def create_circuit_4d():
    qreg_q = QuantumRegister(5, 'q')
    creg_c = ClassicalRegister(4, 'c')
    circuit = QuantumCircuit(qreg_q, creg_c)

    circuit.reset(qreg_q[0])
    circuit.reset(qreg_q[1])
    circuit.reset(qreg_q[2])
    circuit.reset(qreg_q[3])
    circuit.reset(qreg_q[4])
    circuit.x(qreg_q[4])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.h(qreg_q[2])
    circuit.h(qreg_q[3])
    circuit.h(qreg_q[4])
    circuit.barrier(qreg_q[0], qreg_q[1], qreg_q[2], qreg_q[3], qreg_q[4])
    circuit.cx(qreg_q[0], qreg_q[4])
    circuit.cx(qreg_q[1], qreg_q[4])
    circuit.ccx(qreg_q[1], qreg_q[2], qreg_q[4])
    circuit.barrier(qreg_q[0], qreg_q[1], qreg_q[2], qreg_q[3], qreg_q[4])
    circuit.h(qreg_q[0])
    circuit.h(qreg_q[1])
    circuit.h(qreg_q[2])
    circuit.h(qreg_q[3])
    circuit.measure(qreg_q[0], creg_c[0])
    circuit.measure(qreg_q[1], creg_c[1])
    circuit.measure(qreg_q[2], creg_c[2])
    circuit.measure(qreg_q[3], creg_c[3])
    
    return circuit


if __name__ == "__main__":
    # Display the circuits
    circuits = [create_circuit_x(), create_circuit_1(), create_circuit_3xor(), create_circuit_x1(), create_circuit_4d()]
    for i, circuit in enumerate(circuits):
        print(f"Circuit {i+1}")
        print(circuit.draw())  # This will print the text-based circuit
