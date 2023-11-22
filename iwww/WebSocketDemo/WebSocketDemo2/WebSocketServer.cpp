#include "websocket_server.h"

int main() {
	try {
		websocket_server server;


		// 开一个线程单独处理actions队列（三种事件）
		thread t(bind(&websocket_server::process_messages, &server));

		//开始监听端口
		server.run(9002);

		t.join();

	}
	catch (websocketpp::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}
