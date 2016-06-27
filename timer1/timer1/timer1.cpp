#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>

class Printer {
public:
	Printer(boost::asio::io_service& io)
		: strand_(io),
		timer1_(io, boost::posix_time::seconds(1)),
		timer2_(io, boost::posix_time::seconds(1)),
		count_(0)
	{
		timer1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
		timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
	}
	~Printer() {
		std::cout << "Final count is " << count_ << std::endl;
	}
	void print1() {
		if (count_ < 10) {
			std::cout << "Timer 1 : " << count_ << std::endl;
			++count_;

			timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
			timer1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
		}
	}
	void print2() {
		if (count_ < 10) {
			std::cout << "Timer 2 : " << count_ << std::endl;
			++count_;

			timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
			timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
		}
	}
private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer timer1_, timer2_;
	int count_;
};

/*class Timer {
public:
	Timer(boost::asio::io_service& io)
		: timer_(io, boost::posix_time::seconds(1)),
		count_(0)
	{
		timer_.async_wait(boost::bind(&Timer::print, this));
	}
	~Timer() {
		std::cout << "Final count is " << count_ << std::endl;
	}
	void print() {
		if (count_ < 5) {
			std::cout << count_ << std::endl;
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&Timer::print, this));
		}
	}
private:
	boost::asio::deadline_timer timer_;
	int count_;
};*/
// void testprint(const boost::system::error_code&) { std::cout << "Hello1" << std::endl;  }
/*void testprint(const boost::system::error_code&, boost::asio::deadline_timer* t, int* count) {
	if (*count < 5) {
		std::cout << *count << std::endl;
		++(*count);
		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(testprint, boost::asio::placeholders::error, t, count));
	}
}*/

int main(void) {
/*	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.wait();
	std::cout << "Timer Test" << std::endl;
	return 0;
*/
/*	int count = 0;
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(testprint, boost::asio::placeholders::error, &t, &count));
	io.run();
	std::cout << "Final count is " << count << std::endl;
	return 0;
*/
/*	boost::asio::io_service io;
	Timer tm(io);
	io.run();

	return 0;
*/
	boost::asio::io_service io;
	Printer p(io);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
	io.run();
	t.join();

	return 0;
}