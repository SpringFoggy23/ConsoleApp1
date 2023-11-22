#include "websocket_server.h"

int main() {
	try {
		websocket_server server;


		// ��һ���̵߳�������actions���У������¼���
		thread t(bind(&websocket_server::process_messages, &server));

		//��ʼ�����˿�
		server.run(9002);

		t.join();

	}
	catch (websocketpp::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}
