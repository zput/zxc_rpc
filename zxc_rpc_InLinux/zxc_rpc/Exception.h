

#ifndef ZXC_RPC_EXCEPTION_H
#define ZXC_RPC_EXCEPTION_H

#include <exception>

#include <zxc_json/Value.h>
#include <zxc_rpc/RpcError.h>

namespace zxc_rpc
{

class NotifyException: public std::exception
{
public:
    explicit NotifyException(RpcError err, const char* detail):
            err_(err),
            detail_(detail)
    {}

    const char* what() const noexcept
    {
        return err_.asString();
    }
    RpcError err() const
    {
        return err_;
    }
    const char* detail() const
    {
        return detail_;
    }

private:
    RpcError err_;
    const char* detail_;
};

class RequestException: public std::exception
{
public:
    RequestException(RpcError err, zxc_json::Value id, const char* detail):
            err_(err),
            id_(new zxc_json::Value(id)),
            detail_(detail)
    {}
    explicit RequestException(RpcError err, const char* detail):
            err_(err),
            id_(new zxc_json::Value(zxc_json::TYPE_NULL)),
            detail_(detail)
    {}


    const char* what() const noexcept
    {
        return err_.asString();
    }
    RpcError err() const
    {
        return err_;
    }
	zxc_json::Value& id()
    {
        return *id_;
    }
    const char* detail() const
    {
        return detail_;
    }

private:
    RpcError err_;
    std::unique_ptr<zxc_json::Value> id_;
    const char* detail_;
};

class ResponseException: public std::exception
{
public:
    explicit ResponseException(const char* msg):
            hasId_(false),
            id_(-1),
            msg_(msg)
    {}
    ResponseException(const char* msg, int32_t id):
            hasId_(true),
            id_(id),
            msg_(msg)
    {}

    const char* what() const noexcept
    {
        return msg_;
    }

    bool hasId() const
    {
        return hasId_;
    }

    int32_t Id() const
    {
        return id_;
    }

private:
    const bool hasId_;
    const int32_t id_;
    const char* msg_;
};

class StubException: std::exception
{
public:
    explicit StubException(const char* msg):
            msg_(msg)
    {}

    const char* what() const noexcept
    {
        return msg_;
    }

private:
    const char* msg_;
};




}

#endif //ZXC_RPC_EXCEPTION_H
