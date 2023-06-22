#include <iostream>
#include <string>
#include <sstream>

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#include "LineInfo.h"

using namespace std;

const int MESSAGE_MAX_SIZE = 1024;
const int ERROR = -1;

const int SOCK_PORT  = 8888;
const int LISTEN_QUEUE_SIZE = 3;

const int HIGHEST_NO = 100;

#include "LineInfo.h"

int main(int argc, char* argv[]) {
  int    socket_desc, client_sock, read_size, addrsize, status;
  struct sockaddr_in  server, client;

  try {

    if (argc != 1)
          throw domain_error(LineInfo("Usage: ./sockserver & ", __FILE__, __LINE__));

	//Create socket socket_desc
	//$$

	//Setup the sockaddr_in structure
	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port        = htons(SOCK_PORT);

	//Bind socket_desc to server
	//$$

    //listen on socket_desc for client server requests
	//$$

    addrsize = sizeof(struct sockaddr_in);

    //accept on socket_desc the client request
	//$$
    
    //create a random number and associated random number string
    time_t t;
    srand((unsigned)time(&t));
    int randomno = (rand() % HIGHEST_NO + 1);
    stringstream randomnoss; 
    randomnoss << randomno; 
    string randomnostr = randomnoss.str();

    // set configiurationcvariables
    string playresultstr;
    int    guessno;
    string guessnostr;

	// satrt game
    do {
        //Read a guess no messages in clientGuessNoMessage from client
        char clientGuessNoMessage[MESSAGE_MAX_SIZE] = {0};
        
        guessnostr = clientGuessNoMessage; 
        
        // check if no of tries done, send 
        if (guessnostr.find("Random Number") != std::string::npos) {
            // write to client_sock the randomnostr
            throw domain_error(LineInfo("Socket write failure ", __FILE__, __LINE__));
        }

        else { 
           // its a guess no
           if      (read_size > 0) {

               string clientGuessNoMessagestr(clientGuessNoMessage);
               guessno    = stoi(clientGuessNoMessage);
               guessnostr = clientGuessNoMessage;

               if      (randomno == guessno)
                  playresultstr = "You Win !! The number is : "    + randomnostr;
               else if (randomno  > guessno) 
                  playresultstr = "The number is greater than : "  + guessnostr;
               else if (randomno  < guessno)
                  playresultstr = "The number is less than : "     + guessnostr;

               //write to client_sock playresultstr 
               //$$
           }

           else if (read_size == 0) {
              cout << "Client disconnected" << endl;
              fflush(stdout);
              break;
           }

           else if (read_size == ERROR) {
               //$$ throw Socket read failure
           }

        } 
        //else its a guess no

	} while (true);

  }//try
  catch (exception& e) {
      cout << e.what() << endl;
      exit(EXIT_FAILURE);
  }//catch

  exit(EXIT_SUCCESS);
}