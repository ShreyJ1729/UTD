#include <iostream>
#include <string>
#include "Document.h"

using namespace std;

Document::Document() {this->content = ""; }
Document::Document(string content) { this->content = content; }

string Document::getContent() { return this->content; }

void Document::setContent(string content) { this->content = content; }