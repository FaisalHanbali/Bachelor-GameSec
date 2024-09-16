#include "pch.h"
#include "Mutex.h"

Mutex::Mutex()
{
	lock();
}
Mutex::~Mutex()
{
	unlock();
}
void Mutex::lock() 
{
	mutex.lock();
}
void Mutex::unlock()
{
	mutex.unlock();
}