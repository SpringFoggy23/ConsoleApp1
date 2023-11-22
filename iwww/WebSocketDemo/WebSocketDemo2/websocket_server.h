#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <set>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/thread.hpp>

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef WebsocketServer::message_ptr message_ptr;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using websocketpp::lib::thread;
using websocketpp::lib::mutex;
using websocketpp::lib::lock_guard;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;
enum action_type {
	SUBSCRIBE,    //页面连接
	UNSUBSCRIBE,  //连接断开
	MESSAGE		  //收到消息
};

struct action
{
	action(action_type t, connection_hdl h) : type(t), hdl(h) {}
	action(action_type t, connection_hdl h, WebsocketServer::message_ptr m)
		: type(t), hdl(h), msg(m) {}

	action_type type;
	websocketpp::connection_hdl hdl;
	WebsocketServer::message_ptr msg;
};

class websocket_server
{
public:
	websocket_server();
	~websocket_server();

	/*定义三个回调函数，连接，断开，消息*/
	void OnOpen(websocketpp::connection_hdl hdl);  //定义回调函数，处理客户端连接服务器时的事件
	void OnClose(websocketpp::connection_hdl hdl); //定义回调函数，处理客户端断开连接的事件
	void OnMessage(websocketpp::connection_hdl hdl, message_ptr msg); //定义接收到客户端发来数据的事件

	void run(unsigned int port);	//开始监听
	void process_messages();        //用于处理action队列

private:
	//typedef std::unorderset<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl> > con_list;
	typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl> > con_list;
	con_list m_connections;
	std::queue<action> m_actions;

	WebsocketServer m_server; //websocket服务器
	//锁机制，维护线程安全
	mutex m_action_lock;        
	mutex m_connection_lock;
	condition_variable m_action_cond;
};

