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

		SignalNode<Args...>* _head = nullptr;

		void AddNodeToFront(SignalNode<Args...>* node);

	public:
		SignalSubject() {}
		void Emit(Args... args);

		int Register(void* obj, FunctionType func);
		int Unregister(void* obj, FunctionType func);
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

		SignalNode<Args...>* _prev;
		SignalNode<Args...>* _next;

		SignalSubject<Args...>* _subject;

		
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
		SignalNode<Args...>* nextNode = _head;
		_head = node;
		_head->_prev = nullptr;
		_head->_next = nextNode;
	}
	
	
	template<typename ...Args>
	int SignalSubject<Args...>::Register(void* obj, FunctionType func)
	{
		SignalNode<Args...>* node = new SignalNode<Args...>(this, obj, func);

		AddNodeToFront(node);

		return 0;
	}

	template<typename ...Args>
	int SignalSubject<Args...>::Unregister(void* obj, FunctionType func)
	{
		SignalNode<Args...>* node = _head;

		while (node != nullptr)
		{
			if (node->_obj == obj && node->_func == func)
			{
				delete node;
				return 1;
			}

			node = node->next;
		}

		return 0;
	}

	
	template<typename ...Args>
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		SignalNode<Args...>* node = _head;

		while (node != nullptr)
		{
			node->CallFunction(args...);

			node = node->_next;
		}
	}
	#pragma endregion End of SignalSubject.cpp


	#pragma region SignalNode.cpp
	template<typename ...Args>
	SignalNode<Args...>::SignalNode(SignalSubject<Args...>* subject, void* obj, FunctionType func)
	{
		_subject = subject;
		_obj = obj;
		_func = func;
	}


	template<typename ...Args>
	SignalNode<Args...>::~SignalNode()
	{
		// In theory when we implement object pooling, shouldn't actually have to delete node
		// Do all logic in OnRemove so hopefully it can just be transferred over when object pooling exists
		OnRemove();
	}


	template<typename ...Args>
	void SignalNode<Args...>::CallFunction(Args ...args)
	{
		if (_obj != nullptr)
		{
			//_obj->*_func(args...);
			_obj->_func(args...);
		}
		else
		{
			_func(args...);
		}

	}


	template<typename ...Args>
	void SignalNode<Args...>::OnRemove()
	{
		if (_prev != nullptr)
		{
			_prev->_next = _next;
		}
		
		if(_next != nullptr)
		{
			_next->_prev = _prev;
		}
	}
	#pragma endregion End of SignalNode.cpp
}