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
		// Get rid of
		std::vector<SignalObserver<Args...>*> observers;

		// SignalNode<Args...>* headNode;

		public:
		SignalSubject() {}
		void Emit(Args... args);

		int Register(SignalObserver<Args...>& _observer);
		


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


	// Solved linker error with this link:
	// https://www.reddit.com/r/cpp_questions/comments/i2u4tt/linker_error_when_using_templates/
	// Templates apparently cannot be split like normal code, must be defined in same file
	template<typename ...Args>
	int SignalSubject<Args...>::Register(SignalObserver<Args...>& _observer)
	{
		observers.push_back(& _observer);

		return 0;
	}


	//template<typename T>
	//class SignalSubject1 : public SignalSubject
	//{
	//};
}

