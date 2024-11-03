#pragma once
#include <iostream>


namespace jothly
{
	template<typename ...Args>
	class [[deprecated]] SignalObserver
	{
		// Linked function - look up syntax

		// SignalNode* headNode;

		public:
		void Test(Args...);
	};


	template<typename ...Args>
	void SignalObserver<Args...>::Test(Args ...)
	{
		std::cout << "hello world!" << std::endl;
	}
}

