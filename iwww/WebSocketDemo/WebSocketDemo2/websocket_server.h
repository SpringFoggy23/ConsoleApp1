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
	SUBSCRIBE,    //ҳ������
	UNSUBSCRIBE,  //���ӶϿ�
	MESSAGE		  //�յ���Ϣ
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

	/*���������ص����������ӣ��Ͽ�����Ϣ*/
	void OnOpen(websocketpp::connection_hdl hdl);  //����ص�����������ͻ������ӷ�����ʱ���¼�
	void OnClose(websocketpp::connection_hdl hdl); //����ص�����������ͻ��˶Ͽ����ӵ��¼�
	void OnMessage(websocketpp::connection_hdl hdl, message_ptr msg); //������յ��ͻ��˷������ݵ��¼�

	void run(unsigned int port);	//��ʼ����
	void process_messages();        //���ڴ���action����

private:
	//typedef std::unorderset<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl> > con_list;
	typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl> > con_list;
	con_list m_connections;
	std::queue<action> m_actions;

	WebsocketServer m_server; //websocket������
	//�����ƣ�ά���̰߳�ȫ
	mutex m_action_lock;        
	mutex m_connection_lock;
	condition_variable m_action_cond;
};

