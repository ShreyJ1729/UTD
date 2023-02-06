#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Term.h"
#include "BinTree.h"

using namespace std;

vector<string> split(const string &str, const string &delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

string remove_ws(const string &str)
{
    string str_no_ws;
    for (char c : str)
        if (!isspace(c))
            str_no_ws += c;
    return str_no_ws;
}

string remove_char(const string &str, const char &chr)
{
    string str_no_ws;
    for (char c : str)
        if (c != chr)
            str_no_ws += c;
    return str_no_ws;
}

string remove_leading_plus(const string &str)
{
    return (str.at(0) == '+') ? str.substr(1) : str;
}

vector<string> polyStringToVector(const string &line)
{
    regex exp("([+-]?[^-+]+)");
    smatch res;
    vector<string> prePoly = vector<string>();

    string::const_iterator searchStart(line.cbegin());
    while (regex_search(searchStart, line.cend(), res, exp))
    {
        prePoly.push_back(res[0]);
        searchStart = res.suffix().first;
    }

    vector<string> poly = vector<string>();
    int i = 0;
    while (i < prePoly.size())
    {
        string element = prePoly.at(i);
        bool currPower = (element.at(element.length() - 1) == '^');
        string toAdd = currPower ? prePoly.at(i) + prePoly.at(i + 1) : prePoly.at(i);
        if (currPower)
            i++;

        if (toAdd != " ")
        {
            poly.push_back(remove_leading_plus(remove_ws(toAdd)));
        }
        i++;
    }

    return poly;
}

Payload stringToPayload(const string &str)
{
    // if constant
    if (str.find('x') == string::npos)
        return Payload(Fraction(stoi(str)), 0);

    // if degree 1 (^ not in it but x in it)
    if (str.find('^') == string::npos && str.find('x') != string::npos)
    {
        if (str == "x")
            return Payload(Fraction(1), 1);
        if (str == "-x")
            return Payload(Fraction(-1), 1);
        string newstr = remove_char(str, 'x');
        return Payload(Fraction(stoi(newstr)), 1);
    }

    // degree 2 and higher
    string exponent = str.substr(str.find('^') + 1);
    string before = str.substr(0, str.find('^'));

    if (before == "x")
        return Payload(Fraction(1), stoi(exponent));
    if (before == "-x")
        return Payload(Fraction(1), stoi(exponent));

    string newstr = remove_char(str, 'x');
    return Payload(Fraction(stoi(newstr)), stoi(exponent));
}

string printFraction(Fraction frac)
{
    if (frac.denum == 1)
        return to_string(frac.num);
    else
        return to_string(frac.num) + "/" + to_string(frac.denum);
}

int findGCD(int a, int b)
{
    if (b == 0)
        return a;
    return findGCD(b, a % b);
}

Fraction reduceFraction(Fraction frac)
{
    int num1 = frac.num;
    int num2 = frac.denum;
    int denom;
    denom = findGCD(num1, num2);
    num1 /= denom;
    num2 /= denom;
    if (num1 > 0 && num2 < 0)
    {
        num1 *= -1;
        num2 *= -1;
    }
    return Fraction(num1, num2);
}

void printPoly(vector<Payload> *poly, bool plusC)
{
    // for (Payload term : *poly)
    for (int i = 0; i < poly->size(); i++)
    {
        Payload term = poly->at(i);
        term.coefficient = reduceFraction(term.coefficient);

        // print stuff between terms
        if (term.coefficient.num > 0 && i != 0)
            cout << " + ";
        else if (term.coefficient.num < 0 && i != 0)
            cout << " - ";

        int sign = term.coefficient.num < 0 ? -1 : 1;
        if (term.coefficient.num < 0)
            term.coefficient.num *= -1;

        // print constant if constant
        if (term.exponent == 0)
        {
            if (term.coefficient.denum == 1)
                cout << ((sign==-1&&i==0) ? "-" : "") << term.coefficient.num; // whole number
            else
                cout << "(" << ((sign == -1 && i == 0) ? "-" : "") << term.coefficient.num << "/" << term.coefficient.denum << ")" << endl; // fraction
        }
        else if (term.exponent == 1)
        {
            if (term.coefficient.denum == 1 && term.coefficient.num == 1)
                cout << ((sign==-1&&i==0) ? "-" : "") << "x";
            else if (term.coefficient.denum == 1)
                cout << ((sign==-1&&i==0) ? "-" : "") << term.coefficient.num << "x";
            else
                cout << "(" << ((sign==-1&&i==0) ? "-" : "") << term.coefficient.num << "/" << term.coefficient.denum << ")x";
        }
        else
        {
            if (term.coefficient.denum == 1 && term.coefficient.num == 1)
                cout << ((sign==-1&&i==0) ? "-" : "") << "x^" << term.exponent;
            else if (term.coefficient.denum == 1)
                cout << ((sign==-1&&i==0) ? "-" : "") << term.coefficient.num << "x^" << term.exponent;
            else
                cout << "(" << ((sign == -1 && i == 0) ? "-" : "") << term.coefficient.num << "/" << term.coefficient.denum << ")x^" << term.exponent;
        }
    }

    if (plusC)
        cout << " + C";
}

int main()
{
    string infilename;
    cin >> infilename;

    ifstream inFile;
    inFile.open(infilename);

    string line;

    while (inFile.is_open() && !inFile.eof())
    {
        BST *bst = new BST();
        getline(inFile, line);
        bool indefinite = (line.at(0) == '|');
        int intStart;
        int intEnd;

        // cout << "reading in: " << line << endl;
        if (indefinite)
        {
            // delete pipe from beginning of string and dx (last 2 chars) from end
            line = line.substr(1, line.length() - 3);
        }
        else
        {
            // delete pipe and start/end indicators (first 3 chars) from beginning of string and dx (last 2 chars) from end
            int pipeIndex = line.find("|");
            string intStartString = line.substr(0, pipeIndex);
            intStart = stoi(intStartString);
            // cout << "intstart:"<<intStartString<<endl;

            bool encounteredWhitespace = false;
            string intEndString = "";
            int index = pipeIndex;
            while (!encounteredWhitespace)
            {
                index++;
                if (line.at(index) == ' ')
                    break;
                intEndString += line.at(index);
            }
            intEnd = stoi(intEndString);

            // cout << "intEnd:" << intEndString;
            line = line.substr(index);
            line = line.substr(0, line.length() - 3);
        }

        // cout << "processed:" << line<<endl;

        const vector<string> poly = polyStringToVector(line);

        // for (string el : poly)
        // {
        //     cout << "El:" << el << endl;
        // }

        // over here check if a constant is in poly, if it is make bool flag for C term true for outputting
        for (string i : poly)
        {
            Payload term = stringToPayload(i);
            bst->Insert(term);
        }

        vector<Payload> *polyInorder = bst->Inorder(false);

        //  for (Payload el : *polyInorder)
        // {
        //     cout << "El:" << el.coefficient.num<<"/"<<el.coefficient.denum << " " << el.exponent << endl;
        // }

        BST *integral = new BST();
        bst->Integrate(integral, bst->root);
        // cout << "INTEGRAL INORDER:" << endl;
        vector<Payload> *integrated = integral->Inorder(true);

        printPoly(integrated, indefinite);

        if (!indefinite)
        {
            // evaluate integral at start and end
            double value = integral->Evaluate(integral->root, intEnd) - integral->Evaluate(integral->root, intStart);
            cout << ", " << intStart << "|" << intEnd << " = " << value;
        }

        cout << endl;
    }

    inFile.close();
}
