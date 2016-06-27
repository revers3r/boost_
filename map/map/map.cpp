#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/bind.hpp>

class boost_map {
	typedef boost::unordered_set<int>	id;
	typedef boost::unordered_map<std::string, id> Map;

	Map map_variable;
public:
	void Start() {
		id first;
		first.insert(1);
		first.insert(3);
		first.insert(5);
		map_variable["first"] = first;
		if (map_variable.find("first") != map_variable.end()) {
			id second;
			second = map_variable.at("first");
			for (id::iterator it = second.begin(); it != second.end(); it++) {
				std::cout << "[*] Map Data : " << *it << std::endl;
			}
			std::cout << "Line ---------------------------" << std::endl;
			second.insert(2);
			second.insert(2); // Key Collision
			for (id::iterator it = second.begin(); it != second.end(); it++) {
				std::cout << "[*] Map Data : " << *it << std::endl;
			}
			std::cout << "Line ---------------------------" << std::endl;
			second.erase(1);
			for (id::iterator it = second.begin(); it != second.end(); it++) {
				std::cout << "[*] Map Data : " << *it << std::endl;
			}
			std::cout << "Line ---------------------------" << std::endl;
		}
	}
};

int main(void) {
	boost_map bst;
	bst.Start();

	return 0;
}