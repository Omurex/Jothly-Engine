#pragma once


namespace jothly
{
	#pragma region Forward Declarations
	template<typename ...Args>
	class SignalObserver;

	template<typename ...Args>
	class SignalSubject;

	template<typename ...Args>
	class SignalNode;
	

	#pragma region SignalObserver.h
	template<typename ...Args>
	class SignalObserver
	{

		SignalNode<Args...>* headNode;

	public:
		void CallFunction(Args... args);
		void (*linkedFunction)(Args... args);

	};
	#pragma endregion End of SignalObserver.h


	#pragma region SignalSubject.h
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
	};
	#pragma endregion End of SignalSubject.h


	#pragma region SignalNode.h
	template<typename ...Args>
	class SignalNode
	{
		SignalObserver<Args...>* observer;

		SignalNode<Args...>* prevSubjectNode;
		SignalNode<Args...>* nextSubjectNode;

		SignalNode<Args...>* prevObserverNode;
		SignalNode<Args...>* nextObserverNode;
	};
	#pragma endregion End of SignalNode.h




	#pragma region SignalObserver.cpp
	template<typename ...Args>
	void SignalObserver<Args...>::CallFunction(Args ...args)
	{
		linkedFunction(args...);
	}
	#pragma endregion End of SignalObserver.cpp


	#pragma region SignalSubject.cpp
	// Solved linker error with this link:
	// https://www.reddit.com/r/cpp_questions/comments/i2u4tt/linker_error_when_using_templates/
	// Templates apparently cannot be split like normal code, must be defined in same file
	template<typename ...Args>
	int SignalSubject<Args...>::Register(SignalObserver<Args...>& _observer)
	{
		observers.push_back(&_observer);

		return 0;
	}

	
	template<typename ...Args>
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		observers[0]->CallFunction(args...);

		//for (int i = 0; i < _observers.size(); i++)
		//{
		//	//_observers[i].Test(args);
		//}
	}
	#pragma endregion End of SignalSubject.cpp


	#pragma region SignalNode.cpp
	#pragma endregion End of SignalNode.cpp
}