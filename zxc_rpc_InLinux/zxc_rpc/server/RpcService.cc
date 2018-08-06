

#include <zxc_rpc/Exception.h>
#include <zxc_rpc/server/RpcService.h>

using namespace zxc_rpc;

void RpcService::callProcedureReturn(std::string_view methodName,
									 zxc_json::Value& request,
                                     const RpcDoneCallback& done)
{
    auto it = procedureReturn_.find(methodName);
    if (it == procedureReturn_.end()) {
        throw RequestException(RPC_METHOD_NOT_FOUND,
                               request["id"],
                               "method not found");
    }
    it->second->invoke(request, done);
};

void RpcService::callProcedureNotify(std::string_view methodName, zxc_json::Value& request)
{
    auto it = procedureNotfiy_.find(methodName);
    if (it == procedureNotfiy_.end()) {
        throw NotifyException(RPC_METHOD_NOT_FOUND,
                              "method not found");
    }
    it->second->invoke(request);
};