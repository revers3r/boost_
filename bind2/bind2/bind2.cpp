#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/bind.hpp>

/*int main(void) {
	std::vector <int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	std::vector<int>::iterator it = vec.begin();
	std::vector<int>::iterator end = vec.end();
	while (it != end) {
		std::cout << *it << std::endl;
		it++;
	}
	return 0;
}
// Orig
*/

int main(void) {
	std::vector <int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	std::for_each(vec.begin(), vec.end(), boost::bind<int>(printf, "%d\n", _1));
	return 0;
}