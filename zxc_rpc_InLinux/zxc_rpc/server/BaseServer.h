
#ifndef ZXC_RPC_CONNECTION_MANAGER_H
#define ZXC_RPC_CONNECTION_MANAGER_H

#include <zxc_json/Value.h>

#include <zxc_rpc/RpcError.h>
#include <zxc_rpc/util.h>

namespace zxc_rpc
{
class  noncopyable;
class  RequestException;

template <typename ProtocolServer>
class BaseServer: public noncopyable
{
public:
    void setNumThread(size_t n) { server_.setNumThread(n); }

    void start() { server_.start(); }

protected:
    // CRTP pattern base class
    BaseServer(EventLoop* loop, const InetAddress& listen);
    // avoid this:
    //  BaseServer* cm = &ProtocalServer;
    //  delete cm;
    ~BaseServer() = default;

private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer& buffer);
    void onHighWatermark(const TcpConnectionPtr& conn, size_t mark);
    void onWriteComplete(const TcpConnectionPtr& conn);

    void handleMessage(const TcpConnectionPtr& conn, Buffer& buffer);

    void sendResponse(const TcpConnectionPtr& conn, const zxc_json::Value& response);

    ProtocolServer& convert();
    const ProtocolServer& convert() const;

protected:
	zxc_json::Value wrapException(RequestException& e);

private:
	TcpServerMulti server_;
};



}



#endif //ZXC_RPC_CONNECTION_MANAGER_H
