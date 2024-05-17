#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

struct Transition
{
    int nextState;
    char writeSymbol;
    char action;
};

using TransitionFunction = map<pair<int, char>, Transition>;

struct TuringMachine
{
    int numStates;
    int startState;
    set<char> alphabet;
    TransitionFunction transitions;

    // Constructor to initialize the number of states and start state
    TuringMachine(int num, int start) : numStates(num), startState(start) {}

    // Function to add symbols to the alphabet
    void addSymbol(char symbol)
    {
        alphabet.insert(symbol);
    }

    // Function to define a transition
    void defineTransition(int state, char symbol, int nextState, char writeSymbol, char action)
    {
        transitions[make_pair(state, symbol)] = {nextState, writeSymbol, action};
    }

    // The following function just displays the configuration of the machine for validation
    void displayConfiguration() const
    {
        cout << "-------------------------------------------------\n";
        cout << "Turing Machine Configuration\n";
        cout << "-------------------------------------------------\n";
        cout << "Number of States: " << numStates << endl;
        cout << "The States: ";
        for(int i=0 ; i<numStates ; i++){
            cout << "q" << i << " ";
        }
        cout << "\nStart State: " << startState << endl;
        cout << "Alphabet: ";
        for (auto symbol : alphabet)
        {
            cout << symbol << " ";
        }
        cout << "\nTransition Function:\n";
        for (const auto &trans : transitions)
        {
            cout << "(q" << trans.first.first << " , " << trans.first.second << ") , (q"
                 << trans.second.nextState << " , " << trans.second.writeSymbol << " , "
                 << trans.second.action << ")\n";
        }
        cout << "-------------------------------------------------\n";
    }
};

int main()
{
    TuringMachine tm(2, 0); // Initialize TM with 2 states, start state is 0
    tm.addSymbol('a');
    tm.addSymbol('b');
    tm.addSymbol('#');

    // Defining transitions
    tm.defineTransition(0, 'a', 1, 'a', 'R');
    tm.defineTransition(0, 'b', 0, 'b', 'R');
    tm.defineTransition(0, '#', 0, '#', 'N');
    tm.defineTransition(1, 'a', 0, 'b', 'L');
    tm.defineTransition(1, 'b', 1, 'b', 'L');
    tm.defineTransition(1, '#', 1, '#', 'Y');

    // Display TM configuration
    tm.displayConfiguration();

    return 0;
}
