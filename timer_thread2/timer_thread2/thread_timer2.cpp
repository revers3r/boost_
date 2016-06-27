#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <iostream>
#include <vector>

class ThreadService {
public:
	typedef boost::unordered_set<int>						num_;
	typedef boost::unordered_map<std::string, num_>			Map;
	
	Map map_variable;
	num_ num;
	ThreadService(boost::asio::io_service& io)
		: strand_(io),
		t1(io, boost::posix_time::seconds(1)),
		t2(io, boost::posix_time::seconds(1)),
		count_(1) {
		num.insert(1);
		num.insert(2);
		num.insert(3);
		num.insert(4);
		num.insert(5);
		num.insert(6);
		num.insert(7);
		num.insert(8);

		map_variable["first"] = num;
		t1.async_wait(strand_.wrap(boost::bind(&ThreadService::Start1, this)));
		t2.async_wait(strand_.wrap(boost::bind(&ThreadService::Start2, this)));
	}
	~ThreadService() {
		std::cout << "[*] End Count : " << count_ << std::endl;
	}
	void Start1() {
		if (count_ < 8) {
			for(num_::iterator it = num.begin(); it != num.end(); it++) std::cout << "Start1 -> " << *it << std::endl;
			num.erase(count_);
			++count_;
			std::cout << "---------------------------------" << std::endl;
			t1.expires_at(t1.expires_at() + boost::posix_time::seconds(1));
			t1.async_wait(strand_.wrap(boost::bind(&ThreadService::Start1, this)));
		}
	}
	void Start2() {
		if (count_ < 8) {
			for (num_::iterator it = num.begin(); it != num.end(); it++) std::cout << "Start2 -> " << *it << std::endl;
			num.erase(count_);
			++count_;
			std::cout << "---------------------------------" << std::endl;
			t2.expires_at(t2.expires_at() + boost::posix_time::seconds(1));
			t2.async_wait(strand_.wrap(boost::bind(&ThreadService::Start2, this)));
		}
	}
private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer t1, t2;
	int count_;
};

int main(void) {
	boost::asio::io_service io;
	ThreadService t(io);

	boost::thread th(boost::bind(&boost::asio::io_service::run, &io));
	io.run();
	th.join();

	return 0;
}