

#ifndef STRINGWRITESTREAM_H
#define STRINGWRITESTREAM_H

#include <string_view>
#include <vector>

#include "noncopyable.h"

namespace zxc_json
{

class StringWriteStream: noncopyable
{
public:
    void put(char c)
    {
        buffer_.push_back(c);
    }
    void put(std::string_view str)
    {
        buffer_.insert(buffer_.end(), str.begin(), str.end());
    }
    std::string_view get() const
    {
        return std::string_view(&*buffer_.begin(), buffer_.size());
    }

private:
    std::vector<char> buffer_;
};

}

#endif //STRINGWRITESTREAM_H
