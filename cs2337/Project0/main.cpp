// Shrey Joshi
// Net ID: 2021630898

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// takes in records arraylist and processes it to populate the stats arrays
void parseFileDataToArrays(string records[], int hits[], int atBats[], int walks[], int hbp[], int appearances[], int strikeouts[], double BA[], double OB[], int length)
{
    // iterate over all records of people
    for (int iRecord = 0; iRecord < length; iRecord++)
    {
        string record = records[iRecord];

        // for each record, process characters to each array based on the baseball rules using a switch statement
        for (int j = 0; j < record.length(); j++)
        {
            char letter = record[j];
            appearances[iRecord] += 1;
            switch (letter)
            {
            case 'H':
                hits[iRecord]++;
                atBats[iRecord]++;
                break;
            case 'O':
                atBats[iRecord]++;
                break;
            case 'K':
                atBats[iRecord]++;
                strikeouts[iRecord]++;
                break;
            case 'W':
                walks[iRecord]++;
                break;
            case 'P':
                hbp[iRecord]++;
                break;
            case 'S':
                break;
            default:
                appearances[iRecord] -= 1;
                break;
            }
        }
    }
    // fill BA and OB arrays using the other statistics
    for (int i = 0; i < length; i++)
    {
        if (atBats[i] == 0)
        {
            BA[i] = 0.0;
        }
        else
        {
            BA[i] = (hits[i] / (double)atBats[i]);
        }
        OB[i] = (hits[i] + walks[i] + hbp[i]) / ((double)appearances[i]);
    }
}

// print individual stats for each person
void printIndividualStats(string names[], double BA[], double OB[], int hits[], int walks[], int strikeouts[], int hbp[], int length)
{
    // iterate over all names and print individual stats for each person
    for (int i = 0; i < length; i++)
    {
        cout << names[i] << endl;
        cout << fixed << setprecision(3);
        cout << "BA: " << BA[i] << endl;
        cout << "OB%: " << OB[i] << endl;
        cout << "H: " << hits[i] << endl;
        cout << "BB: " << walks[i] << endl;
        cout << "K: " << strikeouts[i] << endl;
        cout << "HBP: " << hbp[i] << endl;
    }
}

// gets index of max element in a double[] array (for OB and BA)
int getIndexOfMax(double arr[], int length)
{
    int iOfMax = 0;
    // iterate over array, updating index if a new max is found
    for (int i = 0; i < length; i++)
    {
        iOfMax = arr[iOfMax] < arr[i] ? i : iOfMax;
    }
    return iOfMax;
}

// same overloaded method for int[] arrays
int getIndexOfMax(int arr[], int length, bool getMax)
{
    int iOfMax = 0;
    for (int i = 0; i < length; i++)
    {
        if (getMax)
        {
            iOfMax = arr[iOfMax] < arr[i] ? i : iOfMax;
        }
        else
        {
            iOfMax = arr[iOfMax] > arr[i] ? i : iOfMax;
        }
    }
    return iOfMax;
}

void getAndPrintLeagueLeaders(string names[], double BA[], double OB[], int hits[], int walks[], int strikeouts[], int hbp[], int length)
{

    // initalize variables for league leaders
    // we do this in case there are multiple leaders for each statistic
    string BALeaders = "";
    string OBLeaders = "";
    string HLeaders = "";
    string BBLeaders = "";
    string KLeaders = "";
    string HBPLeaders = "";

    // Calculate league leaders
    // get max element of each array (except K for which we get min)
    int BAiMax = getIndexOfMax(BA, length);
    int OBiMax = getIndexOfMax(OB, length);
    int HiMax = getIndexOfMax(hits, length, true);
    int BBiMax = getIndexOfMax(walks, length, true);
    int KiMin = getIndexOfMax(strikeouts, length, false);
    int HBPiMax = getIndexOfMax(hbp, length, true);

    // Get names of league leaders --> if there's more than one, a comma and space separates them
    for (int i = 0; i < length; i++)
    {
        if (names[i]=="") continue;
        if (BA[i] == BA[BAiMax])
            BALeaders += ", " + names[i];
        if (OB[i] == OB[OBiMax])
            OBLeaders += ", " + names[i];
        if (hits[i] == hits[HiMax])
            HLeaders += ", " + names[i];
        if (walks[i] == walks[BBiMax])
            BBLeaders += ", " + names[i];
        if (strikeouts[i] == strikeouts[KiMin])
            KLeaders += ", " + names[i];
        if (hbp[i] == hbp[HBPiMax])
            HBPLeaders += ", " + names[i];
    }

    // Print league leaders --> use replaceAll function to remove the comma space at the beginning of the string
    cout << "LEAGUE LEADERS" << endl;
    cout << fixed << setprecision(3);
    cout << "BA: " << BALeaders.substr(2, BALeaders.length() - 2).c_str() << " " << BA[BAiMax] << endl;
    cout << "OB%: " << OBLeaders.substr(2, OBLeaders.length() - 2).c_str() << " " << OB[OBiMax] << endl;
    cout << "H: " << HLeaders.substr(2, HLeaders.length() - 2).c_str() << " " << hits[HiMax] << endl;
    cout << "BB: " << BBLeaders.substr(2, BBLeaders.length() - 2).c_str() << " " << walks[BBiMax] << endl;
    cout << "K: " << KLeaders.substr(2, KLeaders.length() - 2).c_str() << " " << strikeouts[KiMin] << endl;
    cout << "HBP: " << HBPLeaders.substr(2, HBPLeaders.length() - 2).c_str() << " " << hbp[HBPiMax] << endl;
}

int main()
{
    // get user input for input file name
    string inputFileName;
    cin >> inputFileName;

    ifstream inFile;
    inFile.open(inputFileName);

    // read from file to name/record arrays
    string names[30];
    string records[30];
    int length = 0;
    while (inFile.is_open() && !inFile.eof())
    {
        inFile >> names[length];
        inFile >> records[length];
        length++;
    }
    inFile.close();

    // create arrays for hits, atBats, walks, hbp, plate appearances, strikeouts, and BA/OB to populate with records data
    int hits[30] = {};
    int atBats[30] = {};
    int walks[30] = {};
    int hbp[30] = {};
    int appearances[30] = {};
    int strikeouts[30] = {};
    double BA[30] = {};
    double OB[30] = {};

    // use data in records array to populate the rest
    parseFileDataToArrays(records, hits, atBats, walks, hbp, appearances, strikeouts, BA, OB, length);

    // print stats for each person
    printIndividualStats(names, BA, OB, hits, walks, strikeouts, hbp, length);

    // use array data to determine league leaders for each statistic and print it out
    getAndPrintLeagueLeaders(names, BA, OB, hits, walks, strikeouts, hbp, length);

    return 0;
}