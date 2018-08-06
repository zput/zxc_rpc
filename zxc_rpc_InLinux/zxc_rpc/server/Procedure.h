
#ifndef ZXC_RPC_PROCEDURE_H
#define ZXC_RPC_PROCEDURE_H



#include <zxc_json/Value.h>

#include <zxc_rpc/util.h>

namespace zxc_rpc
{

typedef std::function<void(zxc_json::Value&, const RpcDoneCallback&)> ProcedureReturnCallback;
typedef std::function<void(zxc_json::Value&)> ProcedureNotifyCallback;

template <typename Func>
class Procedure: zxc_rpc::noncopyable
{
public:
    template<typename... ParamNameAndTypes>
    explicit Procedure(Func&& callback, ParamNameAndTypes&&... nameAndTypes):
            callback_(std::forward<Func>(callback))
    {
        constexpr int n = sizeof...(nameAndTypes);
        static_assert(n % 2 == 0, "procedure must have param name and type pairs");

        if constexpr (n > 0)
            initProcedure(nameAndTypes...);
    }




    // procedure call
    void invoke(zxc_json::Value& request, const RpcDoneCallback& done);
    // procedure notify
    void invoke(zxc_json::Value& request);

private:
    template<typename Name, typename... ParamNameAndTypes>
    void initProcedure(Name paramName, zxc_json::ValueType parmType, ParamNameAndTypes &&... nameAndTypes)
    {
        static_assert(std::is_same_v<Name, const char *> ||
                      std::is_same_v<Name, std::string_view>,
                      "param name must be 'const char*' or 'std::string_view'");
        params_.emplace_back(paramName, parmType);
        if constexpr (sizeof...(ParamNameAndTypes) > 0)    //  ?????
            initProcedure(nameAndTypes...);                //  ?????
    }

    template<typename Name, typename Type, typename... ParamNameAndTypes>
    void initProcedure(Name paramName, Type parmType, ParamNameAndTypes &&... nameAndTypes)
    {
        static_assert(std::is_same_v<Type, zxc_json::ValueType>, "param type must be json::ValueType");
    }        //  std::is_same_v

    void validateRequest(zxc_json::Value& request) const;
    bool validateGeneric(zxc_json::Value& request) const;

private:
    struct Param
    {
        Param(std::string_view paramName_, zxc_json::ValueType paramType_) :
                paramName(paramName_),
                paramType(paramType_)
        {}

        std::string_view paramName;        // std::string_view
		zxc_json::ValueType paramType;
    };

private:
    Func callback_;
    std::vector<Param> params_;
};


typedef Procedure<ProcedureReturnCallback> ProcedureReturn;
typedef Procedure<ProcedureNotifyCallback> ProcedureNotify;

}

#endif //ZXC_RPC_PROCEDURE_H
