#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
#include "Document.h"
using namespace std;

class File : public Document
{
public:
    string pathName;
    string fileName;

    File(string pathname, string filename, string content);

    string getPathName() { return this->pathName; }
    void setPathName(string pathName) { this->pathName = pathName; }

    string getFileName() { return this->fileName; }
    void setfileName(string fileName) { this->fileName = fileName; }
};

#endif