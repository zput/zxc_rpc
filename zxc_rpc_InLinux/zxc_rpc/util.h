

#ifndef ZXC_RPC_UTIL_H
#define ZXC_RPC_UTIL_H

#include <string>
#include <string_view>

#include <zxc_json/Value.h>



#include <zxc_net/EventLoop.h>
#include <zxc_net/TcpConnection.h>

#include <zxc_net/TcpServerMulti.h>
#include <zxc_net/TcpServer.h>
//#include <zxc_net/TcpClient.h>
#include <zxc_net/InetAddress.h>
#include <zxc_net/Buffer.h>
#include <zxc_net/Logger.h>
#include <zxc_net/Callbacks.h>
#include <zxc_net/Timestamp.h>
#include <zxc_net/ThreadPool.h>
//#include <zxc_net/CountDownLatch.h>

//Acceptor.h
//Buffer.h
//Callbacks.h
//Channel.h
//EventLoop.h
//EventLoopThread.h
//EventLoopThreadPool.h
//InetAddress.h
//Logger.h
//Poller.h
//TcpConnection.h
//TcpServer.h
//TcpServerMulti.h
//ThreadPool.h
//Timer.h
//TimerQueue.h
//Timestamp.h


namespace zxc_rpc
{

	class noncopyable
	{
	public:
		noncopyable(const noncopyable&) = delete;
		void operator=(const noncopyable&) = delete;
	protected:
		noncopyable() = default;
		~noncopyable() = default;
	};


using namespace std::literals::string_view_literals;
using namespace std::literals::chrono_literals;

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

using zxc_net::EventLoop;
using zxc_net::TcpConnection;
using zxc_net::TcpServerMulti;
using zxc_net::TcpServer;
//using zxc_net::TcpClient;
using zxc_net::InetAddress;
using zxc_net::TcpConnectionPtr;
//using zxc_net::noncopyable;
using zxc_net::Buffer;
using zxc_net::ConnectionCallback;
using zxc_net::ThreadPool;
//using zxc_net::CountDownLatch;

typedef std::function<void(zxc_json::Value response)> RpcDoneCallback;

class UserDoneCallback
{
public:
    UserDoneCallback(zxc_json::Value &request,
                     const RpcDoneCallback &callback)    // typedef std::function<void(json::Value response)> RpcDoneCallback;
            : request_(request),
              callback_(callback)                    
    {}


    void operator()(zxc_json::Value &&result) const
    {
		zxc_json::Value response(zxc_json::TYPE_OBJECT);
        response.addMember("jsonrpc", "2.0");
        response.addMember("id", request_["id"]);
        response.addMember("result", result);
        callback_(response);
    }

private:
    mutable zxc_json::Value request_;
    RpcDoneCallback callback_;
};






}

#endif //ZXC_RPC_UTIL_H
