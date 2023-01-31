#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <string>
using namespace std;

class Document
{
public:
    string content;

    Document();
    Document(string content);

    virtual string getContent();

    virtual void setContent(string content);
};

#endif