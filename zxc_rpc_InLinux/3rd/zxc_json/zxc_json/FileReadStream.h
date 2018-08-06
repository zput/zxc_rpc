

#ifndef FILEINPUTSTREAM_H
#define FILEINPUTSTREAM_H

#include <cstdio>
#include <vector>
#include <cassert>

#include "noncopyable.h"  

namespace zxc_json
{

class FileReadStream: noncopyable
{
public:
    using Iterator = std::vector<char>::iterator;

public:
    explicit FileReadStream(FILE* input)
    {
        readStream(input);
        iter_ = buffer_.begin();
    }

	// hasNext  peek   getIter   next   assertNext

    bool hasNext() const
    { return iter_ != buffer_.end(); }
	
    char peek()
    {
        return hasNext() ? *iter_ : '\0';
    }

    const Iterator getIter() const
    { return iter_; }


	char next()
	{
		if (hasNext()) {
			char ch = *iter_;
			iter_++;
			return ch;
		}
		return '\0';
	}


    void assertNext(char ch)
    {
        assert(peek() == ch);
        next();
    }

private:
    void readStream(FILE *input)
    {
        char buf[65536];
        while(true) {
            size_t n = fread(buf, 1, sizeof(buf), input);
            if (n == 0)
                break;
            buffer_.insert(buffer_.end(), buf, buf + n);
        }
    }

private:
    std::vector<char> buffer_;
    Iterator iter_;
};

}

#endif //FILEINPUTSTREAM_H
