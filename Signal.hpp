#pragma once
#include <unordered_map>


namespace jothly
{
	#pragma region Forward Declarations
	template<typename ...Args>
	class SignalSubject;

	template<typename ...Args>
	class SignalNode;


	#pragma region SignalSubject.h
	template<typename... Args>
	class SignalSubject
	{
		typedef void (*FunctionType)(Args...);

		friend class SignalNode<Args...>;

		std::unordered_map<FunctionType, SignalNode<Args...>*> funcToNode;

		SignalNode<Args...>* headNode = nullptr;

		void AddNodeToFront(SignalNode<Args...>* node);

	public:
		SignalSubject() {}
		void Emit(Args... args);

		int Register(void* obj, FunctionType func);
		int Unregister(FunctionType observer);
	};
	#pragma endregion End of SignalSubject.h


	#pragma region SignalNode.h
	template<typename ...Args>
	class SignalNode
	{
		typedef void (*FunctionType)(Args...);

		friend class SignalSubject<Args...>;

		void* _obj;
		FunctionType _func;

		SignalNode<Args...>* _prevSubjectNode;
		SignalNode<Args...>* _nextSubjectNode;

		SignalNode<Args...>* _prevObserverNode;
		SignalNode<Args...>* _nextObserverNode;

		
		void CallFunction(Args... args);
		void OnRemove();


		public:
		SignalNode(SignalSubject<Args...>* subject, void* obj, FunctionType func);

		~SignalNode();
	};
	#pragma endregion End of SignalNode.h



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
	int SignalSubject<Args...>::Register(void* obj, FunctionType observer)
	{
		SignalNode<Args...>* node = new SignalNode<Args...>(this, obj, observer);

		funcToNode[observer] = node;

		return 0;
	}

	template<typename ...Args>
	int SignalSubject<Args...>::Unregister(FunctionType observer)
	{
		return 0;
	}

	
	template<typename ...Args>
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		SignalNode<Args...>* node = headNode;

		while (node != nullptr)
		{
			node->CallFunction(args...);

			node = node->_nextSubjectNode;
		}
	}
	#pragma endregion End of SignalSubject.cpp


	#pragma region SignalNode.cpp
	template<typename ...Args>
	SignalNode<Args...>::SignalNode(SignalSubject<Args...>* subject, void* obj, FunctionType func)
	{
		_obj = obj;
		_func = func;

		subject->AddNodeToFront(this);
	}


	template<typename ...Args>
	SignalNode<Args...>::~SignalNode()
	{
		// In theory when we implement object pooling, shouldn't actualy have to delete node
		// Do all logic in OnRemove so hopefully it can just be transferred over when object pooling exists
		OnRemove();
	}


	template<typename ...Args>
	void SignalNode<Args...>::CallFunction(Args ...args)
	{
		if (_obj != nullptr)
		{
			_obj->*_func(args...);
		}
		else
		{
			_func(args...);
		}

	}


	template<typename ...Args>
	void SignalNode<Args...>::OnRemove()
	{
		
	}
	#pragma endregion End of SignalNode.cpp
}