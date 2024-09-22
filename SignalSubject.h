#pragma once
#include <vector>
#include <iostream>


namespace jothly
{
	class SignalObserver;


	template<typename T, typename... Args>
	class SignalSubject
	{
		public:
			void DoSomething(Args... argPack)
			{
				//std::cout << argPack[0];
			}


			/*void DoSomething(T base)
			{
				
			}


			void DoSomething(T curr, Args... argPack)
			{
				std::cout << curr << std::endl;
			}*/
	};


	//template<typename T>
	//class SignalSubject1 : public SignalSubject
	//{
	//};
}

