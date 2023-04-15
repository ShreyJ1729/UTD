#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <time.h>

#include "LineInfo.h"

using namespace std;

static const char *const QUOTES_FILE_NAME = "quotes.txt";

int const READ = 0;
int const WRITE = 1;
int const PIPE_ERROR = -1;
int const FORK_ERROR = -1;
int const CHILD_PID = 0;
int const MAX_PIPE_MESSAGE_SIZE = 1000;
int const MAX_QUOTE_LINE_SIZE = 1000;

void getQuotesArray(char *lines[], unsigned &noLines)
{
  // read in quotes line by line from quotes.txt and add to lines
  FILE *fp;
  char line[MAX_QUOTE_LINE_SIZE];
  int i = 0;

  fp = fopen(QUOTES_FILE_NAME, "r");
  if (fp == NULL)
  {
    cout << "Error opening file " << QUOTES_FILE_NAME << endl;
    exit(EXIT_FAILURE);
  }

  while (fgets(line, MAX_QUOTE_LINE_SIZE, fp) != NULL)
  {
    lines[i] = new char[strlen(line) + 1];
    strcpy(lines[i], line);
    i++;
  }
  noLines = i;
  fclose(fp);

  // print out quotes
  // cout << "Quotes read from " << QUOTES_FILE_NAME << endl;
  // for (int i = 0; i < noLines; i++)
  //   cout << lines[i];
  // cout << endl;
}

void executeParentProcess(int pipeParentWriteChildReadfds[], int pipeParentReadChildWritefds[], int noOfParentMessages2Send)
{
  // close unnecessary part of pipes that are not used.
  close(pipeParentWriteChildReadfds[READ]);
  close(pipeParentReadChildWritefds[WRITE]);

  // Create a character array for the Parent Read Child Message to hold messages from the child.
  char parentReadChildMessage[MAX_PIPE_MESSAGE_SIZE];

  // Design a loop that uses the command line argument number set at the program beginning to indicate how many Get Quote messages to send to the child
  for (int i = 0; i < noOfParentMessages2Send; i++)
  {
    // Send a Get Quote message to the child
    write(pipeParentWriteChildReadfds[WRITE], "Get Quote", strlen("Get Quote") + 1);
    cout << "In Parent: Write to pipe getQuoteMessage sent Message: Get Quote" << endl;

    // Read a Quote message from the child
    read(pipeParentReadChildWritefds[READ], parentReadChildMessage, MAX_PIPE_MESSAGE_SIZE);
    cout << "In Parent: Read from pipe pipeParentReadChildMessage read Message:" << endl;

    // Print the Quote message to the screen
    cout << parentReadChildMessage << endl;
    cout << "---------------------------------------------" << endl;
  }

  // close pipes by sending Exit message
  write(pipeParentWriteChildReadfds[WRITE], "Exit", strlen("Exit") + 1);
  cout << "In Parent: Write to pipe getQuoteMessage sent Message: Exit" << endl;
}

void executeChildProcess(int pipeParentWriteChildReadfds[], int pipeParentReadChildWritefds[], char *lines[], unsigned noLines)
{
  // infinite loop that reads message from parent, if message is exit leave loop
  // If the message is Get Quote
  // • Use random number generator to get a random quote line from the quote array.
  // • Declare and clear a char send array using correct size
  // • Copy to the send array from quote array.
  // • Write this quote to the parent.
  //   If the message is invalid
  // • Display to the screen that the message is invalid and sent back to the parent
  // • Write this invalid message to the parent

  while (true)
  {
    // close unnecessary part of pipes that are not used.
    close(pipeParentWriteChildReadfds[WRITE]);
    close(pipeParentReadChildWritefds[READ]);

    // Create a character array for the Parent Write Child Message to hold messages from the parent.
    char parentWriteChildMessage[MAX_PIPE_MESSAGE_SIZE];

    // Read a message from the parent
    read(pipeParentWriteChildReadfds[READ], parentWriteChildMessage, MAX_PIPE_MESSAGE_SIZE);

    // If the message is Exit
    if (strcmp(parentWriteChildMessage, "Exit") == 0)
    {
      // leave loop
      cout << "In Child : Read from pipe pipeParentWriteChildMessage read Message: Exit" << endl;
      break;
    }
    // If the message is Get Quote
    else if (strcmp(parentWriteChildMessage, "Get Quote") == 0)
    {
      cout << "In Child : Read from pipe pipeParentWriteChildMessage read Message: Get Quote" << endl;

      // Use random number generator to get a random quote line from the quote array.
      int randomQuoteIndex = rand() % noLines;

      // Declare and clear a char send array using correct size
      char send[MAX_PIPE_MESSAGE_SIZE];
      memset(send, 0, MAX_PIPE_MESSAGE_SIZE);

      // Copy to the send array from quote array.
      strcpy(send, lines[randomQuoteIndex]);

      // Write this quote to the parent.
      write(pipeParentReadChildWritefds[WRITE], send, strlen(send) + 1);
      cout << "In Child : Write to pipe pipeParentReadChildMessage sent Message:" << endl;
      cout << send << endl;
    }
    // If the message is invalid
    else
    {
      // Display to the screen that the message is invalid and sent back to the parent
      cout << "Invalid message: " << parentWriteChildMessage << endl;

      // Write this invalid message to the parent
      write(pipeParentReadChildWritefds[WRITE], parentWriteChildMessage, strlen(parentWriteChildMessage) + 1);
    }
  }

  // close pipes
  close(pipeParentWriteChildReadfds[READ]);
  close(pipeParentReadChildWritefds[WRITE]);
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  try
  {
    if (argc != 2)
      throw domain_error(LineInfo("Usage: ./forkpipe <number>", __FILE__, __LINE__));

    // argv[0] is the program name, argv[1] is the number, atoi = ascii to int
    int noOfParentMessages2Send = atoi(argv[1]);
    char *lines[1000];
    unsigned noLines;

    // if argv[1] is not a number, return an error message
    if (noOfParentMessages2Send == 0)
      throw domain_error(LineInfo("Usage: ./forkpipe <number>", __FILE__, __LINE__));

    getQuotesArray(lines, noLines);

    int pipeParentWriteChildReadfds[2],
        pipeParentReadChildWritefds[2];
    int pid;

    // create pipes
    if (pipe(pipeParentWriteChildReadfds) == PIPE_ERROR)
      throw domain_error(LineInfo("Unable to create pipe pipeParentWriteChildReadfds", __FILE__, __LINE__));

    if (pipe(pipeParentReadChildWritefds) == PIPE_ERROR)
      throw domain_error(LineInfo("Unable to create pipe pipeParentReadChildWritefds", __FILE__, __LINE__));

    cout << endl
         << endl;

    pid = fork();

    if (pid == FORK_ERROR)
      throw domain_error(LineInfo("Fork Error", __FILE__, __LINE__));

    else if (pid != CHILD_PID)
    {
      // Parent process
      executeParentProcess(pipeParentWriteChildReadfds, pipeParentReadChildWritefds, noOfParentMessages2Send);
    }
    else
    {
      // child process
      executeChildProcess(pipeParentWriteChildReadfds, pipeParentReadChildWritefds, lines, noLines);
    }
  } // try
  catch (exception &e)
  {
    cout << e.what() << endl;
    cout << endl
         << "Press the enter key once or twice to leave..." << endl;
    cin.ignore();
    cin.get();
    exit(EXIT_FAILURE);
  } // catch

  exit(EXIT_SUCCESS);
}
