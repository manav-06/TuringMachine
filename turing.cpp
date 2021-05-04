#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class Node
{
public:
    char writeChar, dir;
    string nextState;
};

class TuringMachine
{

    string file_name, tape;

    int ptr;
    set<string> accept_states;
    map<pair<string, char>, Node> mp;

public:
    TuringMachine(string File_name) : file_name(File_name),
                                       ptr(0){};
    void displayTape(string);
    void parseFile();
    //void initializeTables();
    void turingSimulator();
    void check();
};

void TuringMachine::displayTape(string present_state)
{
    cout << "\r" << tape.substr(0, ptr);
    // before the pointer head

    cout << "(" << tape[ptr] << ")";
    // display tape content under the pointer head

    if (ptr + 1 < tape.size())
        cout << tape.substr(ptr + 1);
    // display tape contents after the pointer head
    cout << "\t\t State: " << present_state;
    Sleep(200);
    cout.flush();
}

void TuringMachine::check()
{
    for (auto &[key, val] : mp)
    {
        cout << key.first << ' ' << key.second << ' ' << val.dir << ' ' << val.nextState << " " << val.writeChar << '\n';
    }
}

void TuringMachine::parseFile()
{
    // opening input file for reading
    ifstream ifs;
    ifs.open(file_name, ios::in);
    if (!ifs.is_open())
    {
        cerr << "Can't open file\n";
        return ;
    }

    string line, present_state, next_state;
    char read_char, write_char, direction;
    int present_state_id, next_state_id, read_char_id, dir_id;

    getline(ifs, tape);
    // reading tape (input)
    while (getline(ifs, line))
    {
        istringstream iss(line);
        iss >> present_state;

        if (present_state == "accept")
        {
            while (iss >> present_state)
                accept_states.insert(present_state);
            continue;
        }

        iss >> read_char >> write_char >> direction >> next_state;
        // initializing transition tables
        mp[{present_state, read_char}] = {write_char, direction, next_state};
    }

    ifs.close();
    return;
}

void TuringMachine::turingSimulator()
{
    char read_char;
    string present_state = "q0";
    displayTape(present_state);
    // cout << "In fun\n";
    while (true)
    {
        // cout << "In loop";
        read_char = tape[ptr];
        // cout << present_state << ' ' << read_char << ' ';

        if (find(accept_states.begin(), accept_states.end(), present_state) != accept_states.end())
        {
            cout << "\n> accepted";
            break;
        }

        if (mp.count({present_state, read_char}) == 0)
        {

            if (!accept_states.empty())
                cout << "\n> rejected";
            else
                cout << "\n> halted";
            break;
        }

        char writeChar = mp[{present_state, read_char}].writeChar;
        char dir = mp[{present_state, read_char}].dir;
        string nextState = mp[{present_state, read_char}].nextState;

        tape[ptr] = writeChar;
        if (dir == 'l')
            ptr--;
        else
            ptr++;
   
        if (ptr < 0)
        {
            tape = "_" + tape;
            ptr = 0;
        }
        if (ptr >= tape.size())
            tape = tape + "_";
        present_state = nextState;
        displayTape(present_state);
    }
}
int main()
{
    TuringMachine t("unaryToBinary.txt");
    t.parseFile();
    // t.check();
    t.turingSimulator();
}