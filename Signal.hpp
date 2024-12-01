#pragma once
#include <unordered_map>


namespace jothly
{
	#pragma region Forward Declarations
	template<typename ...Args>
	class SignalSubject;

	template<typename ...Args>
	class SignalNode;

	template<typename ...Args>
	class FunctionSignalNode;

	template<typename ObjectType, typename ...Args>
	class ObjectSignalNode;
	#pragma endregion



	#pragma region SignalSubject.h
	template<typename... Args>
	class SignalSubject
	{
	public:
		typedef void (*FunctionType)(Args...);

		friend class SignalNode<Args...>;

		SignalNode<Args...>* _head = nullptr;

		void AddNodeToFront(SignalNode<Args...>* node);

	public:
		SignalSubject() {}
		void Emit(Args... args);

		int Register(FunctionType func);
		int Unregister(FunctionType func);

		template<typename ObjectType>
		int Register(ObjectType* obj, void (ObjectType::*func)(Args...));

		template<typename ObjectType>
		int Unregister(ObjectType* obj, void (ObjectType::* func)(Args...));

		//int Unregister(void* obj, FunctionType func);
	};
	#pragma endregion



	#pragma region SignalNode.h
	template<typename ...Args>
	class SignalNode
	{
		friend class SignalSubject<Args...>;

		SignalNode<Args...>* _prev;
		SignalNode<Args...>* _next;

		SignalSubject<Args...>* _subject = nullptr;

		SignalNode(SignalSubject<Args...>* subject);
		~SignalNode() { OnRemove(); }

		protected:
		virtual void CallFunction(Args... args) = 0;
		void OnRemove();

		
	};
	#pragma endregion End of SignalNode.h



	#pragma region FunctionSignalNode.h
	template<typename ...Args>
	class FunctionSignalNode : public SignalNode<Args...>
	{
		friend class SignalSubject<Args...>;

		typedef void (*FunctionType)(Args...);

		FunctionType _func;

		protected:
		void CallFunction(Args... args) override;
	};
	#pragma endregion



	#pragma region ObjectSignalNode.h
	template<typename ObjectType, typename ...Args>
	class ObjectSignalNode : public SignalNode<Args...>
	{
		friend class SignalSubject<Args...>;

		ObjectType* _obj;
		typedef void (ObjectType::*FunctionType)(Args...);

		protected:
		// void (ObjectType::* func)(Args...)
		ObjectSignalNode(SignalSubject<Args...>* subject, ObjectType* obj, FunctionType func);
	};
	#pragma endregion



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
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		SignalNode<Args...>* node = _head;

		while (node != nullptr)
		{
			node->CallFunction(args...);

			node = node->_next;
		}
	}
	#pragma endregion


	#pragma region SignalNode.cpp
	template<typename ...Args>
	SignalNode<Args...>::SignalNode(SignalSubject<Args...>* subject)
	{
		_subject = subject;
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
	#pragma endregion
}