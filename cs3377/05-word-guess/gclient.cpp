#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>
#include <cstring>
#include "LineInfo.h"

using namespace std;

const int ARRAY_SIZE = 100;
const string KNOWN_PIPE = "known_pipe";
const int MAX_TRIES = 12;

int main()
{
    srand(time(0));

    string client_pipe_name = "client_pipe_" + to_string(getpid());
    mkfifo(client_pipe_name.c_str(), 0666);

    int known_pipe_fd = open(KNOWN_PIPE.c_str(), O_WRONLY);
    if (known_pipe_fd == -1)
    {
        cerr << LineInfo("Error: Could not open known named pipe for writing.", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    write(known_pipe_fd, client_pipe_name.c_str(), ARRAY_SIZE);

    int client_pipe_fd = open(client_pipe_name.c_str(), O_RDONLY);
    if (client_pipe_fd == -1)
    {
        cerr << LineInfo("Error: Could not open client created unique named pipe for reading.", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    char try_number[ARRAY_SIZE];
    read(client_pipe_fd, try_number, ARRAY_SIZE);

    char random_word[ARRAY_SIZE];
    read(client_pipe_fd, random_word, ARRAY_SIZE);

    char child_pipe_name[ARRAY_SIZE];
    read(client_pipe_fd, child_pipe_name, ARRAY_SIZE);

    int child_pipe_fd = open(child_pipe_name, O_WRONLY);
    if (child_pipe_fd == -1)
    {
        cerr << LineInfo("Error: Could not open child created unique named pipe for writing.", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    int num_tries = 0;
    cout << "Game Start" << endl;
    cout << "You have 12 letter guesses to win" << endl;

    while (num_tries < MAX_TRIES)
    {
        char guess_word[ARRAY_SIZE];
        read(client_pipe_fd, guess_word, ARRAY_SIZE);

        if (strcmp(guess_word, random_word) == 0)
        {
            cout << "You Win!" << endl;
            break;
        }

        if (num_tries == MAX_TRIES - 1)
        {
            cout << "Out of tries: 12 allowed" << endl;
            cout << "The word is: " << random_word << endl;
            break;
        }

        cout << "Client: " << try_number << endl;
        cout << "No of tries: " << num_tries << endl;
        cout << "(Guess) Enter a letter in the word: " << guess_word << endl;

        char guess;
        cin >> guess;

        write(child_pipe_fd, &guess, 1);

        ++num_tries;
    }

    close(child_pipe_fd);
    close(client_pipe_fd);
    close(known_pipe_fd);
    unlink(child_pipe_name);
    unlink(client_pipe_name.c_str());

    return 0;
}