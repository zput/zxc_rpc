


#ifndef ARITHMETICSERVICESTUB_H
#define ARITHMETICSERVICESTUB_H

#include "zxc_json/Value.h"

#include "zxc_rpc/util.h"
#include "zxc_rpc/server/RpcServer.h"
#include "zxc_rpc/server/RpcService.h"    

class ArithmeticService;

namespace zxc_rpc
{

template <typename S>
class ArithmeticServiceStub: noncopyable
{
protected:
    explicit
    ArithmeticServiceStub(RpcServer& server)
    {
        static_assert(std::is_same_v<S, ArithmeticService>,
                      "derived class name should be 'ArithmeticService'");
        auto service = new RpcService;
       
		service->addProcedureReturn("Add", new ProcedureReturn(             //  construct 
				std::bind(&ArithmeticServiceStub::AddStub, this, _1, _2)
				, 
		"lhs", zxc_json::TYPE_DOUBLE, 
		"rhs", zxc_json::TYPE_DOUBLE
		));
		service->addProcedureReturn("Sub", new ProcedureReturn(
				std::bind(&ArithmeticServiceStub::SubStub, this, _1, _2)
				, 
		"lhs", zxc_json::TYPE_DOUBLE,
		"rhs", zxc_json::TYPE_DOUBLE
		));
		service->addProcedureReturn("Mul", new ProcedureReturn(
				std::bind(&ArithmeticServiceStub::MulStub, this, _1, _2)
				, 
		"lhs", zxc_json::TYPE_DOUBLE,
		"rhs", zxc_json::TYPE_DOUBLE
		));
		service->addProcedureReturn("Div", new ProcedureReturn(
				std::bind(&ArithmeticServiceStub::DivStub, this, _1, _2)
				, 
		"lhs", zxc_json::TYPE_DOUBLE,
		"rhs", zxc_json::TYPE_DOUBLE
		));
        server.addService("Arithmetic", service);
    }




    ~ArithmeticServiceStub() = default;

private:

	    void AddStub(zxc_json::Value& request, const RpcDoneCallback& done)    //当在Message后, 发现需要调用AddStub,的话, 会吧request, and done 传递进来. 
		{
			auto& params = request["params"];

			if (params.isArray()) {
				auto lhs = params[0].getDouble();
				auto rhs = params[1].getDouble();

				convert().Add(lhs, rhs,  UserDoneCallback(request, done));
			}
			else {
				auto lhs = params["lhs"].getDouble();
				auto rhs = params["rhs"].getDouble();

				convert().Add(lhs, rhs,  UserDoneCallback(request, done));    //class UserDoneCallback
			}
		}



			void SubStub(zxc_json::Value& request, const RpcDoneCallback& done)
{
    auto& params = request["params"];

    if (params.isArray()) {
        auto lhs = params[0].getDouble();
auto rhs = params[1].getDouble();

        convert().Sub(lhs, rhs,  UserDoneCallback(request, done));
    }
    else {
        auto lhs = params["lhs"].getDouble();
auto rhs = params["rhs"].getDouble();

        convert().Sub(lhs, rhs,  UserDoneCallback(request, done));
    }
}






			void MulStub(zxc_json::Value& request, const RpcDoneCallback& done)
{
    auto& params = request["params"];

    if (params.isArray()) {
        auto lhs = params[0].getDouble();
auto rhs = params[1].getDouble();

        convert().Mul(lhs, rhs,  UserDoneCallback(request, done));
    }
    else {
        auto lhs = params["lhs"].getDouble();
auto rhs = params["rhs"].getDouble();

        convert().Mul(lhs, rhs,  UserDoneCallback(request, done));
    }
}



			void DivStub(zxc_json::Value& request, const RpcDoneCallback& done)
{
    auto& params = request["params"];

    if (params.isArray()) {
        auto lhs = params[0].getDouble();
auto rhs = params[1].getDouble();

        convert().Div(lhs, rhs,  UserDoneCallback(request, done));
    }
    else {
        auto lhs = params["lhs"].getDouble();
auto rhs = params["rhs"].getDouble();

        convert().Div(lhs, rhs,  UserDoneCallback(request, done));
    }
}


private:
    S& convert()
    {
        return static_cast<S&>(*this);
    }
};

}

#endif //ARITHMETICSERVICESTUB_H
