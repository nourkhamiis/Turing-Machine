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
                cout << "[HANG >> Head moved out of tape bounds.]\n";
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
    TuringMachine tm(2, 0);
    tm.addSymbol('a');
    tm.addSymbol('b');
    tm.addSymbol('#');
    tm.addSymbol('<');

    // Defining transitions
    // Parking the head
    // The Head should be parked at one step after the left mark
    // For Example: 
    // < a b a a b # 
    //   ^           
    tm.defineTransition(0, 'a', 0, 'a', 'L');
    tm.defineTransition(0, 'b', 0, 'b', 'L');
    tm.defineTransition(0, '#', 0, '#', 'L');
    tm.defineTransition(0, '<', 1, '<', 'R');
    tm.defineTransition(1, 'a', 1, 'a', 'Y');
    tm.defineTransition(1, 'b', 1, 'b', 'Y');
    tm.defineTransition(1, '#', 1, '#', 'Y');
    tm.defineTransition(1, '<', 1, '<', 'N');


    tm.displayConfiguration();

    // ASSUMING THAT THE HEAD POSITION STARTS FROM INDEX 0
    // The starting position of the head is any position on the tape

    // TEST 1 (Final Head Position: 1), ACCEPTED
    tm.execute("<ababab#", 4);

    // TEST 2 (Final Head Position: 3), ACCEPTED
    tm.execute("aa<ababab#", 6);

    // TEST 3 : HANG , the left mark "<" was not found
    tm.execute("bbbbababab#", 8);

    return 0;
}