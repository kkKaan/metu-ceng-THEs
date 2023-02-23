#include "the8.h"

const int ALPHABET_SIZE = 26; // Assume alphabet consists of lowercase letters 'A' to 'Z'

// A state of the FSA
struct State 
{
    int transitions[ALPHABET_SIZE]; // Transitions to other states on different symbols
    bool isAccepting; // True if this state is an accepting state
};

// The FSA
struct FSA 
{
    std::vector<State> states; // States of the FSA
    int startState; // Start state of the FSA
};

// Builds an FSA for the given pattern and symbol mappings
FSA buildFSA(const std::string& pattern, const std::pair<std::string, std::string>& mapping) 
{
    FSA fsa;
    int n = pattern.size();

    fsa.states.resize(n + 1); // We need n+1 states for the n-length pattern
    fsa.startState = 0; // The start state is the first state
    fsa.states[n].isAccepting = true; // The last state is an accepting state

    // Set up the transitions
    for (int i = 0; i < n; i++) 
    {
        char c = pattern[i];
        fsa.states[i].isAccepting = false;

        for (int j = 0; j < ALPHABET_SIZE; j++) 
        {
            char symbol = 'A' + j;
            if (symbol == c || symbol == mapping.first[0] || symbol == mapping.second[0]) 
            {
                // Add a transition to the next state on this symbol
                fsa.states[i].transitions[j] = i + 1;
            } 
            else 
            {
                // Stay in the same state on this symbol
                fsa.states[i].transitions[j] = i;
            }
        }
    }
    return fsa;
}

void matchPattern(const std::string& sequence, const std::pair<std::string,std::string> mapping, const std::string& pattern)
{
    FSA fsa = buildFSA(pattern, mapping);

    // Initialize the current state to the start state of the FSA
    int currentState = fsa.startState;
    int n = pattern.size();
    int sequenceSize = sequence.size();
    int isNone = 1;

    // Iterate over the characters of the text
    for (int i = 0; i < sequenceSize; i++) 
    {
        char c = sequence[i];
        int symbol = c - 'A'; // Convert the character to an integer in the range [0, 25]

        // Check if the current character is a valid transition from the current state
        if (fsa.states[currentState].transitions[symbol] != currentState) 
        {
            currentState = fsa.states[currentState].transitions[symbol];
        } 

        // If the current state is an accepting state, print the index of the current character
        if (fsa.states[currentState].isAccepting) 
        {
            if(!isNone) std::cout << " ";
            std::cout << i - n + 1;
            i = i - n;
            isNone = 0;
        }
    }
    if(isNone) std::cout << "NONE";    
    std::cout << std::endl;
}