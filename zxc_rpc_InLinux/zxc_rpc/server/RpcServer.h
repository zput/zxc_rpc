
#ifndef ZXC_RPC_RPCSERVER_H
#define ZXC_RPC_RPCSERVER_H

#include <memory>
#include <unordered_map>

#include <zxc_json/Value.h>

#include <zxc_rpc/util.h>
#include <zxc_rpc/server/RpcService.h>
#include <zxc_rpc/server/BaseServer.h>

namespace zxc_rpc
{
class RpcServer: public BaseServer<RpcServer>
{

public:
    RpcServer(EventLoop* loop, const InetAddress& listen):
            BaseServer(loop, listen)
    {}
    ~RpcServer() = default;

    // used by user stub
    void addService(std::string_view serviceName, RpcService* service);

    // used by connection manager
    void handleRequest(const std::string& json,
                       const RpcDoneCallback& done);

private:
    void handleSingleRequest(zxc_json::Value& request,
                             const RpcDoneCallback& done);
    void handleBatchRequests(zxc_json::Value& requests,
                             const RpcDoneCallback& done);
    void handleSingleNotify(zxc_json::Value& request);

    void validateRequest(zxc_json::Value& request);
    void validateNotify(zxc_json::Value& request);

private:
    typedef std::unique_ptr<RpcService> RpcServeicPtr;
    typedef std::unordered_map<std::string_view, RpcServeicPtr> ServiceList;

    ServiceList services_;
};

}

#endif //ZXC_RPC_RPCSERVER_H
