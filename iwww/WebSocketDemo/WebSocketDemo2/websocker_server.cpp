#include "websocket_server.h"

websocket_server::websocket_server()
{
	////初步登录设置
	//m_server.set_access_channels(websocketpp::log::alevel::all);
	//m_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
	//初始化asio
	m_server.init_asio();
	//绑定三个回调函数到server

	m_server.set_open_handler(::bind(&websocket_server::OnOpen, this, ::_1));
	m_server.set_close_handler(::bind(&websocket_server::OnClose, this, ::_1));
	m_server.set_message_handler(::bind(&websocket_server::OnMessage, this, ::_1, ::_2));
}

websocket_server::~websocket_server(){}

void websocket_server::OnOpen(websocketpp::connection_hdl hdl)
{
	{
		lock_guard<mutex> guard(m_action_lock);
		m_actions.push(action(SUBSCRIBE, hdl));
	}
	m_action_cond.notify_one();
}

void websocket_server::OnClose(websocketpp::connection_hdl hdl)
{
	{
		lock_guard<mutex> guard(m_action_lock);
		m_actions.push(action(UNSUBSCRIBE, hdl));
	}
	m_action_cond.notify_one();
}

void websocket_server::OnMessage(websocketpp::connection_hdl hdl, message_ptr msg)
{
	{
		lock_guard<mutex> guard(m_action_lock);
		m_actions.push(action(MESSAGE, hdl,msg));
	}
	m_action_cond.notify_one();
}

void websocket_server::run(unsigned int port)
{
	//开始监听 port端口
	m_server.listen(port);
	//开始接受客户端连接
	m_server.start_accept();

	try
	{
		//开启asio io_service
		m_server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
//处理action 队列
void websocket_server::process_messages()
{
	while (1)
	{
		unique_lock<mutex> lock(m_action_lock);

		while (m_actions.empty()) {   //如果队列为空，阻塞线程，知道actions队列有任务，释放锁
			m_action_cond.wait(lock);
		}

		action a = m_actions.front();
		m_actions.pop();

		lock.unlock();

		if (a.type == SUBSCRIBE) {           //客户端连接
			lock_guard<mutex> guard(m_connection_lock);
			m_connections.insert(a.hdl);
		}
		else if (a.type == UNSUBSCRIBE) {    //连接断开
			lock_guard<mutex> guard(m_connection_lock);
			m_connections.erase(a.hdl);
		}
		else if (a.type == MESSAGE) {        //收到消息
			lock_guard<mutex> guard(m_connection_lock);

			con_list::iterator it;           //队列迭代器实现广播（群聊效果）
			for (it = m_connections.begin(); it != m_connections.end(); ++it) {
				m_server.send(*it, a.msg);
			}
		}
		else {
			// undefined.
		}
	}
}
