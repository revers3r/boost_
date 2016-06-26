#include <iostream>
#include <Windows.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class threadvec {
public:
	std::string name;
	threadvec(const char *data) {
		name = data;
	}
	void func(const char *msg) {
		printf("[%d] %s: %s\n", GetCurrentThreadId(), name.c_str(), msg);
	}
};
int main() {
	threadvec a("a");
	threadvec b("b");

	boost::thread th1(boost::bind(&threadvec::func, a, "Hello"));
	boost::thread th2(boost::bind(&threadvec::func, b, "Bye"));

	th1.join();
	th2.join();
	return 0;
}