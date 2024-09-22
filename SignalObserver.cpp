#include "SignalObserver.h"
#include <iostream>


namespace jothly
{
	template<typename ...Args>
	void jothly::SignalObserver<Args...>::Test(Args ...)
	{
		std::cout << "hello world!" << std::endl;
	}
}