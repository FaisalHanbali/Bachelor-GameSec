#pragma once
#include <mutex>

class Mutex
{
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
private:
	std::mutex mutex;
};

