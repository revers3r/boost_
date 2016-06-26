#include <iostream>
#include <boost/bind.hpp>

class testclass {
public:
	std::string str;
	testclass(const char *s) {
		str = s;
	}
	testclass(const testclass &test) {
		str = test.str;
	}
	~testclass() {
	}
	void func(const char *msg) {
		std::cout << str.c_str() << " : " << msg << std::endl;
	}
};
int main(void) {
	testclass ts("rev");
	boost::bind(&testclass::func, ts, "Hi")();
	boost::bind(&testclass::func, _1, "Hello")(ts);

	return 0;
}