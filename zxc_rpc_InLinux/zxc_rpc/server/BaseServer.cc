


#include <zxc_json/Document.h>
#include <zxc_json/Writer.h>
#include <zxc_json/StringWriteStream.h>

#include <zxc_rpc/Exception.h>
#include <zxc_rpc/server/BaseServer.h>
#include <zxc_rpc/server/RpcServer.h>

using namespace zxc_rpc;

namespace
{

const size_t kHighWatermark = 65536;
const size_t kMaxMessageLen = 100 * 1024 * 1024;

}

namespace zxc_rpc
{

template class BaseServer<RpcServer>;

}

template <typename ProtocolServer>
BaseServer<ProtocolServer>::BaseServer(EventLoop *loop, const InetAddress& listen)
        :server_(loop, listen)
{
    server_.setConnectionCallback(std::bind(
            &BaseServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(
            &BaseServer::onMessage, this, _1, _2));
}

template <typename ProtocolServer>
void BaseServer<ProtocolServer>::onConnection(const TcpConnectionPtr& conn)
{
    //if (conn->connected()) {
    //    DEBUG("connection %s is [up]",
    //          conn->peer().toIpPort().c_str());
    //    conn->setHighWaterMarkCallback(std::bind(
    //            &BaseServer::onHighWatermark, this, _1, _2), kHighWatermark);
    //}
    //else {
    //    DEBUG("connection %s is [down]",
    //          conn->peer().toIpPort().c_str());
    //}
	DEBUG("connection void BaseServer<ProtocolServer>::onConnection(const TcpConnectionPtr& conn) ");
}

template <typename ProtocolServer>
void BaseServer<ProtocolServer>::onMessage(const TcpConnectionPtr& conn, Buffer& buffer)
{
    try {
        handleMessage(conn, buffer);
    }
    catch (RequestException& e) {
		zxc_json::Value response = wrapException(e);
        sendResponse(conn, response);
     //    conn->shutdown();

     //   WARN("BaseServer::onMessage() %s request error: %s",
     //        conn->peer().toIpPort().c_str(), e.what());
    }
    catch (NotifyException& e)
    {
     //   WARN("BaseServer::onMessage() %s notify error: %s",
     //        conn->peer().toIpPort().c_str(), e.what());
    }
}

template <typename ProtocolServer>
void BaseServer<ProtocolServer>::handleMessage(const TcpConnectionPtr& conn, Buffer& buffer)
{
	while (true) {

		const char *crlf = buffer.findCRLF();
		if (crlf == nullptr)
			break;
		if (crlf == buffer.peek()) {
			buffer.retrieve(2);
			break;
		}

		size_t headerLen = crlf - buffer.peek() + 2;

		zxc_json::Document header;
		auto err = header.parse(buffer.peek(), headerLen);
		if (err != zxc_json::PARSE_OK ||
			!header.isInt32() ||
			header.getInt32() <= 0)
		{
			throw RequestException(RPC_INVALID_REQUEST, "invalid message length");
		}

		auto jsonLen = static_cast<uint32_t>(header.getInt32());
		if (jsonLen >= kMaxMessageLen)
			throw RequestException(RPC_INVALID_REQUEST, "message is too long");

		if (buffer.readableBytes() < headerLen + jsonLen)
			break;

		buffer.retrieve(headerLen);
		auto json = buffer.retrieveAsString(jsonLen);
		convert().handleRequest(json, [conn, this](zxc_json::Value response) {
			if (!response.isNull()) {
				sendResponse(conn, response);
				//TRACE("BaseServer::handleMessage() %s request success",
				//	conn->peer().toIpPort().c_str());
			}
			else {
				//TRACE("BaseServer::handleMessage() %s notify success",
				//	conn->peer().toIpPort().c_str());
			}
		});
	}
}









template <typename ProtocolServer>
void BaseServer<ProtocolServer>::onHighWatermark(const TcpConnectionPtr& conn, size_t mark)
{
    //DEBUG("connection %s high watermark %lu",
    //     conn->peer().toIpPort().c_str(), mark);

    //conn->setWriteCompleteCallback(std::bind(
    //        &BaseServer::onWriteComplete, this, _1));
    //conn->stopRead();
}

template <typename ProtocolServer>
void BaseServer<ProtocolServer>::onWriteComplete(const TcpConnectionPtr& conn)
{
    //DEBUG("connection %s write complete",
    //     conn->peer().toIpPort().c_str());
    //conn->startRead();
}



template <typename ProtocolServer>
zxc_json::Value BaseServer<ProtocolServer>::wrapException(RequestException& e)
{
    zxc_json::Value response(zxc_json::TYPE_OBJECT);
    response.addMember("jsonrpc", "2.0");
    auto& value = response.addMember("error", zxc_json::TYPE_OBJECT);
    value.addMember("code", e.err().asCode());
    value.addMember("message", e.err().asString());
    value.addMember("data", e.detail());
    response.addMember("id", e.id());
    return response;
}

template <typename ProtocolServer>
void BaseServer<ProtocolServer>::sendResponse(const TcpConnectionPtr& conn, const zxc_json::Value& response)
{
	zxc_json::StringWriteStream os;
	zxc_json::Writer writer(os);
    response.writeTo(writer);

    // wish sso string don't allocate heap memory...
    auto message = std::to_string(os.get().length() + 2)
            .append("\r\n")
            .append(os.get())
            .append("\r\n");
    conn->send(message);
}

template <typename ProtocolServer>
ProtocolServer& BaseServer<ProtocolServer>::convert()
 {
    return static_cast<ProtocolServer&>(*this);
}

template <typename ProtocolServer>
const ProtocolServer& BaseServer<ProtocolServer>::convert() const
{
    return static_cast<const ProtocolServer&>(*this);
}


