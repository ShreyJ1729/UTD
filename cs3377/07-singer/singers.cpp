#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

#include <unistd.h>
#include <pthread.h>

#include "LineInfo.h"

using namespace std;

pthread_mutex_t lock1;
static unsigned totalLineCount;

void GetLyricLinesFromFileToVector(string lyricsFilenameStr,
                                   vector<string> &lyricLinesVector,
                                   unsigned &noOfLyricLines)
{

    ifstream lyricsFile(lyricsFilenameStr);
    string line;
    while (getline(lyricsFile, line))
    {
        lyricLinesVector.push_back(line);
    }
    noOfLyricLines = lyricLinesVector.size();
}

struct SingLinesThreadInfoStruct
{
    unsigned *singerNoIdPtr;
    vector<string> lyricLinesVector;
    unsigned noOfLyricLines;
};

void *SingLinesThread(void *singLinesThreadInfoStructPtr)
{

    SingLinesThreadInfoStruct *threadInfoPtr = (SingLinesThreadInfoStruct *)singLinesThreadInfoStructPtr;
    static unsigned previousNoId;

    const unsigned maxSingLineNo = 10;
    unsigned *singersNoIdPtr = threadInfoPtr->singerNoIdPtr;
    vector<string> lyricLinesVector = threadInfoPtr->lyricLinesVector;
    unsigned noOfLyricLines = threadInfoPtr->noOfLyricLines;

    pthread_mutex_lock(&lock1);

    cout << "Starting thread for singer " << *singersNoIdPtr << endl;

    pthread_mutex_unlock(&lock1);

    unsigned singLimit = 0;

    for (unsigned lyricLineNo = 0; lyricLineNo < noOfLyricLines; lyricLineNo += maxSingLineNo)
    {

        unsigned currentLineSungNo = lyricLineNo;
        singLimit += maxSingLineNo;

        for (; (currentLineSungNo < singLimit) && (currentLineSungNo < noOfLyricLines); currentLineSungNo++)
        {

            pthread_mutex_lock(&lock1);

            if (previousNoId != *singersNoIdPtr)
                cout << endl;

            cout << "Singer " << *singersNoIdPtr << ": " << lyricLinesVector[currentLineSungNo] << endl;

            pthread_mutex_unlock(&lock1);

            previousNoId = *singersNoIdPtr;
            totalLineCount++;
        }

        sleep(1);
    }

    pthread_mutex_lock(&lock1);

    cout << "Done with thread for singer " << *singersNoIdPtr << endl;

    pthread_mutex_unlock(&lock1);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    try
    {

        if (argc != 3)
        {
            string errorStr = "Usage : ";
            errorStr += string(argv[0]) + " <lyricsFilename> <noOfSingers>";
            throw runtime_error(errorStr);
        }

        string lyricsFilenameStr(argv[1]);
        unsigned noOfSingers = stoi(argv[2]);
        vector<string> lyricLinesVector;
        unsigned noOfLyricLines = 0;

        GetLyricLinesFromFileToVector(lyricsFilenameStr, lyricLinesVector, noOfLyricLines);

        cout << endl
             << endl;
        cout << "Lyrics Filename     : " << lyricsFilenameStr << endl;
        cout << "Number of Singers   : " << noOfSingers << endl;
        cout << "Number of Lyric Lines: " << noOfLyricLines << endl;
        cout << endl
             << endl;

        pthread_t *singersThreadIdPtr;
        unsigned *singersNoIdPtr;
        SingLinesThreadInfoStruct *singLinesThreadInfoStructPtr;

        singersThreadIdPtr = new pthread_t[noOfSingers];
        singersNoIdPtr = new unsigned[noOfSingers];
        singLinesThreadInfoStructPtr = new SingLinesThreadInfoStruct[noOfSingers];

        pthread_mutex_init(&lock1, NULL);

        for (unsigned singerNo = 0; singerNo < noOfSingers; ++singerNo)
        {

            unsigned *singerNoIdPtr = new unsigned;
            *singerNoIdPtr = singerNo + 1;

            singLinesThreadInfoStructPtr[singerNo].singerNoIdPtr = singerNoIdPtr;
            singLinesThreadInfoStructPtr[singerNo].lyricLinesVector = lyricLinesVector;
            singLinesThreadInfoStructPtr[singerNo].noOfLyricLines = noOfLyricLines;

            pthread_mutex_lock(&lock1);

            cout << "Creating thread for singer " << *singerNoIdPtr << endl;

            pthread_mutex_unlock(&lock1);

            pthread_create(&singersThreadIdPtr[singerNo], NULL, SingLinesThread, &singLinesThreadInfoStructPtr[singerNo]);
        }

        for (unsigned singerNo = 0; singerNo < noOfSingers; ++singerNo)
        {
            pthread_join(singersThreadIdPtr[singerNo], NULL);
        }

        cout << endl;
        cout << "Program done " << endl;
        cout << "Total Line count sung : " << totalLineCount << endl;
        cout << endl;

        pthread_mutex_destroy(&lock1);
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
