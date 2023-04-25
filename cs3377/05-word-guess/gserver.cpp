#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include "LineInfo.h"

using namespace std;

const int ARRAY_SIZE = 100;
const string KNOWN_PIPE = "known_pipe";
const int MAX_TRIES = 12;

string generate_random_word(const vector<string> &words)
{
    return words[rand() % words.size()];
}

string create_empty_slots(const string &word)
{
    return string(word.length(), '-');
}

void fill_matching_slots(char guess, const string &random_word, string &guess_word)
{
    for (size_t i = 0; i < random_word.size(); ++i)
    {
        if (random_word[i] == guess)
        {
            guess_word[i] = guess;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " words.txt" << endl;
        return 1;
    }

    srand(time(0));

    ifstream words_file(argv[1]);
    if (!words_file)
    {
        cerr << "Error: Could not open words file." << endl;
        return 1;
    }

    vector<string> words;
    copy(istream_iterator<string>(words_file), istream_iterator<string>(), back_inserter(words));

    if (mkfifo(KNOWN_PIPE.c_str(), 0666) == -1)
    {
        cerr << "Error: Could not create known named pipe." << endl;
        return 1;
    }

    int known_pipe_fd = open(KNOWN_PIPE.c_str(), O_RDONLY);
    if (known_pipe_fd == -1)
    {
        throw LineInfo("Error: Could not open known named pipe for reading.", __FILE__, __LINE__);
    }

    char client_pipe_name[ARRAY_SIZE];
    read(known_pipe_fd, client_pipe_name, ARRAY_SIZE);

    close(known_pipe_fd);
    unlink(KNOWN_PIPE.c_str());

    int client_pipe_fd = open(client_pipe_name, O_WRONLY);
    if (client_pipe_fd == -1)
    {
        throw LineInfo("Error: Could not open client created unique named pipe for writing.", __FILE__, __LINE__);
    }

    string random_word = generate_random_word(words);
    string guess_word = create_empty_slots(random_word);

    int try_count = 1;
    int child_pid = fork();

    if (child_pid == 0)
    { // Child process
        write(client_pipe_fd, to_string(try_count).c_str(), ARRAY_SIZE);

        sleep(2);

        write(client_pipe_fd, random_word.c_str(), ARRAY_SIZE);

        string child_pipe_name = "child_pipe_" + to_string(getpid());
        mkfifo(child_pipe_name.c_str(), 0666);

        write(client_pipe_fd, child_pipe_name.c_str(), ARRAY_SIZE);

        int child_pipe_fd = open(child_pipe_name.c_str(), O_RDONLY);

        while (try_count <= MAX_TRIES)
        {
            write(client_pipe_fd, guess_word.c_str(), ARRAY_SIZE);

            char guess;
            read(child_pipe_fd, &guess, 1);

            fill_matching_slots(guess, random_word, guess_word);

            ++try_count;
        }

        close(child_pipe_fd);
        unlink(child_pipe_name.c_str());
    }

    close(client_pipe_fd);
    unlink(client_pipe_name);

    return 0;
}