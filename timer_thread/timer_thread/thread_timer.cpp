#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>

class Service {
public:
	Service(boost::asio::io_service& io)
		: st(io),
		t1(io, boost::posix_time::seconds(1)),
		t2(io, boost::posix_time::seconds(1)),
		count_(0){
		t1.async_wait(st.wrap(boost::bind(&Service::Start1, this)));
		t2.async_wait(st.wrap(boost::bind(&Service::Start2, this)));
	}
	~Service() {
		std::cout << "End Count : " << count_ << std::endl;
	}
	void Start1() {
		if (count_ < 20) {
			std::cout << " T1 -> " << count_ << std::endl;
			++count_;

			t1.expires_at(t1.expires_at() + boost::posix_time::seconds(3.5));
			t1.async_wait(st.wrap(boost::bind(&Service::Start1, this)));
		}
	}
	void Start2() {
		if (count_ < 20) {
			std::cout << "T2 ->" << count_ << std::endl;
			++count_;

			t2.expires_at(t2.expires_at() + boost::posix_time::seconds(2));
			t2.async_wait(st.wrap(boost::bind(&Service::Start2, this)));
		}
	}
private:
	boost::asio::strand st;
	boost::asio::deadline_timer t1;
	boost::asio::deadline_timer t2;
	int count_;
};

int main(void) {
	boost::asio::io_service io;
	Service sv(io);
	boost::thread th(boost::bind(&boost::asio::io_service::run, &io));

	io.run();
	th.join();
	return 0;
}