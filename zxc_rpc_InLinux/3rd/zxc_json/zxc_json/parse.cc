#include <cstdio>

#include "Reader.h"
#include "Writer.h" 
#include "FileReadStream.h"
#include "FileWriteStream.h"

using namespace zxc_json;

int main()
{
    FileReadStream is(stdin);
    FileWriteStream os(stdout);
    Writer writer(os);

    ParseError err = Reader::parse(is, writer);
    if (err != PARSE_OK) {
        printf("%s\n", parseErrorStr(err));
    }
}