

#include "ArithmeticServiceStub.h"

using namespace zxc_rpc;
using namespace zxc_net;

class ArithmeticService: public ArithmeticServiceStub<ArithmeticService>
{
public:
    explicit
    ArithmeticService(RpcServer& server):
            ArithmeticServiceStub(server),
            pool_(4)
    {}

    void Add(double lhs, double rhs, const UserDoneCallback& cb)
    {
        pool_.runTask([=](){
            cb(zxc_json::Value(lhs + rhs));
        });
    }

    void Sub(double lhs, double rhs, const UserDoneCallback& cb)
    {
        pool_.runTask([=](){
            cb(zxc_json::Value(lhs - rhs));
        });
    }

    void Mul(double lhs, double rhs, const UserDoneCallback& cb)
    {
        pool_.runTask([=](){
            cb(zxc_json::Value(lhs * rhs));
        });
    }

    void Div(double lhs, double rhs, const UserDoneCallback& cb)
    {
        pool_.runTask([=](){
            cb(zxc_json::Value(lhs / rhs));
        });
    }

private:
    ThreadPool pool_;
};




int main()
{
    EventLoop loop;
    InetAddress addr(9877);

    RpcServer rpcServer(&loop, addr);        //---  ArithmeticService(RpcServer& server):
    ArithmeticService service(rpcServer);    // ---  这是干什么的? 
    
    rpcServer.start();
    loop.loop();              
}
