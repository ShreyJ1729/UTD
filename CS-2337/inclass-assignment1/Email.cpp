#include <iostream>
#include <string>
#include "Email.h"

using namespace std;

Email::Email() : Document() {
    this->sender = "";
    this->recipient = "";
    this->title = "";
}

Email::Email(string sender, string recipient, string title, string content) : Document(content)
{
    this->sender = sender;
    this->recipient = recipient;
    this->title = title;
    this->content = content;
}

string Email::getSender() { return this->sender; }

string Email::getRecipient() { return this->recipient; }

string Email::getTitle() { return this->title; }

void Email::setSender(string sender) { this->sender = sender; }

void Email::setRecipient(string recipient) { this->recipient = recipient; }

void Email::setTitle(string title) { this->title = title; }