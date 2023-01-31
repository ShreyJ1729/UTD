#include "File.h"
#include <string>

File::File(string pathname, string filename, string content) : Document(content)
{
    this->pathName = pathname;
    this->fileName = filename;
    this->content = content;
}
