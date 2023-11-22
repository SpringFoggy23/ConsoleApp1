#include "websocket_server.h"

websocket_server::websocket_server()
{
	////������¼����
	//m_server.set_access_channels(websocketpp::log::alevel::all);
	//m_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
	//��ʼ��asio
	m_server.init_asio();
	//�������ص�������server

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
	//��ʼ���� port�˿�
	m_server.listen(port);
	//��ʼ���ܿͻ�������
	m_server.start_accept();

	try
	{
		//����asio io_service
		m_server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
//����action ����
void websocket_server::process_messages()
{
	while (1)
	{
		unique_lock<mutex> lock(m_action_lock);

		while (m_actions.empty()) {   //�������Ϊ�գ������̣߳�֪��actions�����������ͷ���
			m_action_cond.wait(lock);
		}

		action a = m_actions.front();
		m_actions.pop();

		lock.unlock();

		if (a.type == SUBSCRIBE) {           //�ͻ�������
			lock_guard<mutex> guard(m_connection_lock);
			m_connections.insert(a.hdl);
		}
		else if (a.type == UNSUBSCRIBE) {    //���ӶϿ�
			lock_guard<mutex> guard(m_connection_lock);
			m_connections.erase(a.hdl);
		}
		else if (a.type == MESSAGE) {        //�յ���Ϣ
			lock_guard<mutex> guard(m_connection_lock);

			con_list::iterator it;           //���е�����ʵ�ֹ㲥��Ⱥ��Ч����
			for (it = m_connections.begin(); it != m_connections.end(); ++it) {
				m_server.send(*it, a.msg);
			}
		}
		else {
			// undefined.
		}
	}
}
