// Shrey Joshi and Smirthi Gunasekaran
// SXJ210081 and sxg210188
#include <iostream>
#include <string>
#include "Document.h"
#include "Email.h"
#include "File.h"

using namespace std;

bool containsKey(Document *d, string keyword) {
    string content = d->getContent();
    if (content.find(keyword)!=string::npos) return true;

    Email *docEmail = dynamic_cast<Email*>(d);
    File *docFile = dynamic_cast<File*>(d);

    if (docEmail)
    {
        string title = docEmail->getTitle();
        string sender = docEmail->getSender();
        string recipient = docEmail->getRecipient();
        if (title.find(keyword)!=string::npos || 
            sender.find(keyword)!=string::npos ||
            recipient.find(keyword)!=string::npos ) return true;

    } else if (docFile) {
        string filename = docFile->getFileName();
        string pathname = docFile->getPathName();
        if (filename.find(keyword)!=string::npos || 
            pathname.find(keyword)!=string::npos) return true;
    }

    return false;
}

int main() {
    Document *d = new Document("hello12345");
    Email *e = new Email("smirthi", "shrey", "some code", "public static void main");
    File *f = new File("/Document/Users/test.txt", "test.txt", "testing123");

    cout << containsKey(d, "ello") << endl;
    cout << containsKey(e, "shre") << endl;
    cout << containsKey(f, "123") << endl;
}