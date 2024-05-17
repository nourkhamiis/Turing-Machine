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
    char action; // R, L, Y, N
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

    // Function to execute the Turing Machine on an input tape starting at a specific head position
    void execute(string tape, int headPosition)
    {
        cout << "\n\n[EXECUTING TM INPUT: " << tape << " ]" << endl;
        int currentState = startState;
        while (true)
        {
            char currentSymbol = tape[headPosition];
            auto transitionKey = make_pair(currentState, currentSymbol);
            if (transitions.find(transitionKey) == transitions.end())
            {
                cout << "No transition defined for (q" << currentState << " , " << currentSymbol << ")\n";
                break;
            }
            Transition transition = transitions[transitionKey];
            tape[headPosition] = transition.writeSymbol;

            if (transition.action == 'R')
            {
                headPosition++;
            }
            else if (transition.action == 'L')
            {
                headPosition--;
            }
            else if (transition.action == 'Y')
            {
                cout << "[Input accepted.]\n";
                break;
            }
            else if (transition.action == 'N')
            {
                cout << "[Input rejected.]\n";
                break;
            }

            currentState = transition.nextState;

            // Display the current state of the tape
            cout << "Current State: q" << currentState << ", Tape: " << tape << ", Head Position: " << headPosition << "\n";

            // Ensure the head position is within the bounds of the tape
            if (headPosition < 0 || headPosition >= int(tape.size()))
            {
                cout << "Head moved out of tape bounds.\n";
                break;
            }
        }
    }

    // The following function just displays the configuration of the machine for validation
    void displayConfiguration() const
    {
        cout << "-------------------------------------------------\n";
        cout << "Turing Machine Configuration\n";
        cout << "-------------------------------------------------\n";
        cout << "Number of States: " << numStates << endl;
        cout << "The States: ";
        for (int i = 0; i < numStates; i++)
        {
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
    // The following TM accepts even number of a's
    tm.defineTransition(0, 'a', 1, 'a', 'R');
    tm.defineTransition(0, 'b', 0, 'b', 'R');
    tm.defineTransition(0, '#', 0, '#', 'Y');
    tm.defineTransition(1, 'a', 0, 'a', 'R');
    tm.defineTransition(1, 'b', 1, 'b', 'R');
    tm.defineTransition(1, '#', 1, '#', 'N');

    // Display TM configuration
    tm.displayConfiguration();

    // Execute TM on an input tape starting at a specific head position

    // TEST 1 : REJECTED
    tm.execute("ab#", 0);

    // TEST 2 : ACCEPTED
    tm.execute("aabaa#",0);

    // TEST 3 : ACCEPTED (no. of a's = 0)
    tm.execute("#",0);

    // TEST 4 : ACCEPTED (no. of a's = 0)
    tm.execute("bbbbbb#",0);

    // TEST 5 : REJECTED
    tm.execute("aaabaaaabbbb#",0);

    return 0;
}
