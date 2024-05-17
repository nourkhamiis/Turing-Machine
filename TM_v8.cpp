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

            cout << "Current State: q" << currentState << ", Tape: " << tape << ", Head Position: " << headPosition << "\n";

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
    // Only one state (which is the start state: q0)
    TuringMachine tm(1, 0);
    tm.addSymbol('a');
    tm.addSymbol('b');
    tm.addSymbol('#');

    // Defining transitions
    // TM that erases the tape and stop on first #
    tm.defineTransition(0, 'a', 0, '#', 'R');
    tm.defineTransition(0, 'b', 0, '#', 'R');
    tm.defineTransition(0, '#', 0, '#', 'Y');

    tm.displayConfiguration();

    // TEST 1 : ACCEPTED
    tm.execute("ab#", 0);

    // TEST 2 : ACCEPTED
    tm.execute("aabaa#",0);

    // TEST 3 : ACCEPTED
    tm.execute("#",0);

    // TEST 4 : ACCEPTED
    tm.execute("bbbbbb#",0);

    // TEST 5 : ACCEPTED
    tm.execute("aaaaa#",0);

    // TEST 6 : ACCEPTED
    tm.execute("aa#",0); 

    // TEST 7 : REJECTED (c is not from the alphabet)
    tm.execute("abcc#",0); 

    return 0;
}
