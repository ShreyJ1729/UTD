// #include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <chrono>

using namespace std;
using namespace chrono;

int countlocations(const string &s)
{
    stack<int> st;
    int count = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else if (s[i] == ')')
        {
            if (!st.empty() && s[st.top()] == '(')
            {
                st.pop();
                count += 2;
            }
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    ifstream inputFile;
    inputFile.open(inputFileName);

    string s;
    getline(inputFile, s);

    auto timeStart = steady_clock::now();
    int count = countlocations(s);
    auto timeElapsed = duration_cast<nanoseconds>(steady_clock::now() - timeStart);

    ofstream outputFile;
    outputFile.open(outputFileName);

    outputFile << "Time Elapsed (nano) : " << timeElapsed.count() << endl;
    outputFile << "Found Pattern Count : " << count << endl;
    outputFile << "Searched Pattern : " << s << endl;

    return 0;
}
