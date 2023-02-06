#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include "Document.h"

class Email : public Document
{
private:
    string sender;
    string recipient;
    string title;

public:
    Email();
    Email(string sender, string recipient, string title, string content);

    string getSender();

    string getRecipient();

    string getTitle();

    void setSender(string sender);

    void setRecipient(string recipient);

    void setTitle(string title);
};

#endif