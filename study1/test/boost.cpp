#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>

class testclass {
public:
	int variable;
	testclass() {
		std::cout << ".ctor" << std::endl;
	}
	~testclass() {
		std::cout << ".dtor" << std::endl;
	}
};
void func(std::shared_ptr<testclass> parameter) {
	parameter->variable += 2;
}
int main()
{
	std::shared_ptr<testclass> test(new testclass);
	test->variable = 10;
	std::cout << "Before Variable : " << test->variable << std::endl;
	func(test);
	std::cout << "After Variable : " << test->variable << std::endl;
	return 0;
}