#pragma once
#include <vector>
#include <iostream>


namespace jothly
{
	template<typename... Args>
	class SignalObserver;


	template<typename... Args>
	class SignalSubject
	{
		//std::vector<SignalObserver<Args...>> _observers;


		public:
		SignalSubject() {}
		void Emit(Args... args);
		


		//void DoSomething(Args... argPack)
		//{
		//	//std::cout << argPack[0];
		//}


		/*void DoSomething(T base)
		{
				
		}


		void DoSomething(T curr, Args... argPack)
		{
			std::cout << curr << std::endl;
		}*/


		/*auto DoSomething(Args ...args)
		{
			std::cout << args << std::endl;
			return ...;
		}*/


		/*auto sum(Args ...args)
		{
			std::cout << (args + ...) << std::endl;
			return (args + ...);
		}*/

	};


	//template<typename T>
	//class SignalSubject1 : public SignalSubject
	//{
	//};
}

