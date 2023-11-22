#include <iostream>
#include <string>
#include <set>

using namespace std;

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef WebsocketServer::message_ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
//����һ���ͻ������Ӽ���
set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl> > clientSet;
set<websocketpp::connection_hdl>::iterator it;

//����ص�����,��ҳ��ʱ
void OnOpen(WebsocketServer *server, websocketpp::connection_hdl hdl)
{
	clientSet.insert(hdl); //��ӵ�������
	cout << "have client connect" << endl;
}
//��ҳ�ر� or �Ͽ�����ʱ
void OnClose(WebsocketServer *server, websocketpp::connection_hdl hdl)
{
	clientSet.erase(hdl); //�Ӽ�����ɾ��
	cout << "have client disconnect" << endl;
}
//�յ��ͻ��˵���Ϣʱ
void OnMessage(WebsocketServer *server, websocketpp::connection_hdl hdl, message_ptr msg)
{
	string strMsg = msg->get_payload();
	cout << strMsg << endl;

	//������������Ϣ���ͻ��ˣ�ͨ������������λ�ͻ��ˣ��о�����hdl
	server->send(hdl, strMsg, websocketpp::frame::opcode::TEXT);
	for (it = clientSet.begin(); it != clientSet.end(); it++) //����set����ʵ�ֹ㲥
	{
		if(server->get_con_from_hdl(hdl) != server->get_con_from_hdl(*it)) //�ж��Ƿ�Ϊ�Լ�
			server->send(*it, strMsg, websocketpp::frame::opcode::TEXT);
	}
}

int main()
{
	WebsocketServer server;
	
	//������¼����
	server.set_access_channels(websocketpp::log::alevel::all);
	server.clear_access_channels(websocketpp::log::alevel::frame_payload);

	//��ʼ��asio
	server.init_asio();

	//���������ص����������ڴ����������¼���˳�����Ϣ���¼�
	server.set_open_handler(bind(&OnOpen, &server, ::_1));
	server.set_close_handler(bind(&OnClose, &server, _1));
	server.set_message_handler(bind(&OnMessage, &server, _1, _2));

	//���ü����˿�
	server.listen(12345);
	//��ʼ���ܷ��������� ,
	server.start_accept();
	//Start the ASIO io_service run loop
	server.run();
}