
from numpy import pi
from qiskit import QuantumCircuit
from qiskit.visualization import plot_distribution
from itertools import islice
from qiskit_ibm_runtime import QiskitRuntimeService, Session
from qiskit.primitives import Sampler

class Batch(Session):
    """Class for creating a batch mode in Qiskit Runtime."""

    pass

# To run on hardware, select the backend with the fewest number of jobs in the queue
service = QiskitRuntimeService(channel="ibm_quantum", token="<YOUR_API_TOKEN>")
backend = service.least_busy(operational=True, simulator=False)

# qc = QuantumCircuit(3)

# qc.h(2)
# circuit_diagram = qc.draw(output='mpl')
# circuit_diagram.savefig('qiskit_circuit.png')

def qft_rotations(circuit, n):
    """Performs qft on the first n qubits in circuit (without swaps)"""
    if n == 0:
        return circuit
    n -= 1
    circuit.h(n)
    for qubit in range(n):
        circuit.cp(pi/2**(n-qubit), qubit, n)
    # At the end of our function, we call the same function again on
    # the next qubits (we reduced n by one earlier in the function)
    qft_rotations(circuit, n)


def swap_registers(circuit, n):
    for qubit in range(n//2):
        circuit.swap(qubit, n-qubit-1)
    return circuit

def qft(circuit, n):
    """QFT on the first n qubits in circuit"""
    qft_rotations(circuit, n)
    swap_registers(circuit, n)
    return circuit

id = '100001'
qc = QuantumCircuit(len(id), len(id))
qc.x(0)
qc.x(5)

qft(qc,6)

qc.barrier()

qc.measure(range(6), range(6))

qc.draw(output='mpl', style='iqp', filename='qft_rotations.png')

# Run the circuit and get the distribution
with Batch(backend=backend) as batch:
    sampler = Sampler()
    dist = sampler.run(qc, shots=10000).result().quasi_dists[0]

dist_fig = plot_distribution(dist, title='Quantum Fourier Transform')
dist_fig.savefig('qft_dist.png')  # Saves the plot as a PNG file

# Convert integer keys to binary strings, filling with leading zeros up to the number of qubits
binary_dist = {format(k, f'0{len(id)}b'): v for k, v in dist.items()}

# Sort the binary distribution by the state's binary value
sorted_dist = dict(sorted(binary_dist.items(), key=lambda item: int(item[0], 2)))

def chunks(data, SIZE=4):
    it = iter(data)
    for i in range(0, len(data), SIZE):
        yield {k: data[k] for k in islice(it, SIZE)}

# Convert the sorted dictionary into chunks of four
chunked_dist = list(chunks(sorted_dist))

# Now we can print this in a table-like format with four columns
print("State  |  Prob || " * 4)
print("-" * (15 * 4))
for chunk in chunked_dist:
    for state, probability in chunk.items():
        print(f"{state} | {probability:.4f} ||", end="")
    print()  # Newline at the end of a row