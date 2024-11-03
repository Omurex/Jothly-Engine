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
		friend class SignalSubject<Args...>;
		friend class SignalNode<Args...>;

		SignalNode<Args...>* headNode = nullptr;

		void AddNodeToFront(SignalNode<Args...>* node);

	public:
		void CallFunction(Args... args);
		void (*linkedFunction)(Args... args);

	};
	#pragma endregion End of SignalObserver.h


	#pragma region SignalSubject.h
	template<typename... Args>
	class SignalSubject
	{
		friend class SignalObserver<Args...>;
		friend class SignalNode<Args...>;

		SignalNode<Args...>* headNode = nullptr;

		void AddNodeToFront(SignalNode<Args...>* node);

	public:
		SignalSubject() {}
		void Emit(Args... args);

		int Register(SignalObserver<Args...>& observer);
	};
	#pragma endregion End of SignalSubject.h


	#pragma region SignalNode.h
	template<typename ...Args>
	class SignalNode
	{
		friend class SignalSubject<Args...>;
		friend class SignalObserver<Args...>;

		SignalObserver<Args...>* _observer;

		SignalNode<Args...>* _prevSubjectNode;
		SignalNode<Args...>* _nextSubjectNode;

		SignalNode<Args...>* _prevObserverNode;
		SignalNode<Args...>* _nextObserverNode;

		
		void OnRemove();


		public:
		SignalNode(SignalSubject<Args...>* subject, SignalObserver<Args...>* observer);

		~SignalNode();
	};
	#pragma endregion End of SignalNode.h




	#pragma region SignalObserver.cpp
	template<typename ...Args>
	void SignalObserver<Args...>::AddNodeToFront(SignalNode<Args...>* node)
	{
		SignalNode<Args...>* nextNode = headNode;
		headNode = node;
		headNode->_prevObserverNode = nullptr;
		headNode->_nextObserverNode = nextNode;
	}


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
	// TODO: Add object pooling so we don't have constant dynamic memory allocation
	template<typename ...Args>
	void SignalSubject<Args...>::AddNodeToFront(SignalNode<Args...>* node)
	{
		SignalNode<Args...>* nextNode = headNode;
		headNode = node;
		headNode->_prevSubjectNode = nullptr;
		headNode->_nextSubjectNode = nextNode;
	}
	
	
	template<typename ...Args>
	int SignalSubject<Args...>::Register(SignalObserver<Args...>& observer)
	{
		// TODO: Make this take function as parameter and return new signal observer (reference that node owns?)

		SignalNode<Args...>* nextSubjectNode = headNode;
		SignalNode<Args...>* nextObserverNode = observer.headNode;

		new SignalNode<Args...>(this, &observer);

		return 0;
	}

	
	template<typename ...Args>
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		SignalNode<Args...>* node = headNode;

		while (node != nullptr)
		{
			node->_observer->CallFunction(args...);
			node = node->_nextSubjectNode;
		}

		//observers[0]->CallFunction(args...);

		//for (int i = 0; i < _observers.size(); i++)
		//{
		//	//_observers[i].Test(args);
		//}
	}
	#pragma endregion End of SignalSubject.cpp


	#pragma region SignalNode.cpp
	template<typename ...Args>
	SignalNode<Args...>::SignalNode(SignalSubject<Args...>* subject, SignalObserver<Args...>* observer)
	{
		_observer = observer;

		subject->AddNodeToFront(this);
		observer->AddNodeToFront(this);
	}


	template<typename ...Args>
	SignalNode<Args...>::~SignalNode()
	{
		// In theory when we implement object pooling, shouldn't actualy have to delete node
		// Do all logic in OnRemove so hopefully it can just be transferred over when object pooling exists
		OnRemove();
	}


	template<typename ...Args>
	void SignalNode<Args...>::OnRemove()
	{
	}
	#pragma endregion End of SignalNode.cpp
}