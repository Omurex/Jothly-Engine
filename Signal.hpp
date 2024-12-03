#pragma once
#include <unordered_map>


namespace jothly
{
	// Solved linker error with this link:
	// https://www.reddit.com/r/cpp_questions/comments/i2u4tt/linker_error_when_using_templates/
	// Templates apparently cannot be split like normal code, must be defined in same file


	enum SignalNodeType
	{
		FUNCTION,
		OBJECT
	};



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
	// Class responsible for sending out notification

	template<typename... Args>
	class SignalSubject
	{
		// Define function pointer type for easier-to-read parameters
		typedef void (*FunctionType)(Args...);

		friend class SignalNode<Args...>;

		// Start of linked list of signal nodes, which can be either function or object
		SignalNode<Args...>* _head = nullptr;

		// Appends a node to the front of the linked list, replacing _head with node
		void AddNodeToFront(SignalNode<Args...>* node);

	public:
		SignalSubject() {}

		// Call the functions tied to each subscribed node using the arguments provided
		void Emit(Args... args);

		// Create new function node using provided function
		// Returns 1 on success
		int Register(FunctionType func);

		// Remove existing node that matches the passed in function
		// Returns 1 on success, 0 on fail
		int Unregister(FunctionType func);

		// Create new object node using provided object and member function
		// Returns 1 on success
		template<typename ObjectType>
		int Register(ObjectType* obj, void (ObjectType::*func)(Args...));

		// Remove existing node that matches passed in object and member function
		template<typename ObjectType>
		int Unregister(ObjectType* obj, void (ObjectType::* func)(Args...));
	};
	#pragma endregion



	#pragma region SignalNode.h
	// Abstract class representing a node in a linked list that
	// is able to call functionality using passed in parameters

	template<typename ...Args>
	class SignalNode
	{
		friend class SignalSubject<Args...>;

		protected:

		// Stores the previous and next nodes in the linked list
		SignalNode<Args...>* _prev = nullptr;
		SignalNode<Args...>* _next = nullptr;

		SignalSubject<Args...>* _subject = nullptr;

		SignalNode(SignalSubject<Args...>* subject);
		~SignalNode() { OnRemove(); }

		// Abstract function, used to identify node type using enum
		virtual SignalNodeType GetSignalNodeType() const = 0;

		// Abstract function, call functionality tied to node using parameters
		virtual void CallFunction(Args... args) = 0;

		// Properly remove self from linked list
		void OnRemove();
	};
	#pragma endregion



	#pragma region FunctionSignalNode.h
	// Version of a SignalNode used to call functions (no object associated with them)

	template<typename ...Args>
	class FunctionSignalNode : public SignalNode<Args...>
	{
		friend class SignalSubject<Args...>;

		// Define function type we store for clarity
		typedef void (*FunctionType)(Args...);

		// Stored function
		FunctionType _func;

		protected:
		FunctionSignalNode(SignalSubject<Args...>* subject, FunctionType func);
		~FunctionSignalNode();

		SignalNodeType GetSignalNodeType() const override;
		
		void CallFunction(Args... args) override;
	};
	#pragma endregion



	#pragma region ObjectSignalNode.h
	// Version of a SignalNode used to call methods (functions in a class definition, tied to an object)

	template<class ObjectType, typename ...Args>
	class ObjectSignalNode : public SignalNode<Args...>
	{
		friend class SignalSubject<Args...>;

		// Define function type we store for clarity
		typedef void (ObjectType::*FunctionType)(Args...);

		// Object we will call _func on
		ObjectType* _obj;

		// Stored member function
		FunctionType _func;

		protected:
		ObjectSignalNode(SignalSubject<Args...>* subject, ObjectType* obj, FunctionType func);
		~ObjectSignalNode();

		SignalNodeType GetSignalNodeType() const override;

		void CallFunction(Args... args) override;
	};
	#pragma endregion



	#pragma region SignalSubject.cpp
	template<typename ...Args>
	void SignalSubject<Args...>::AddNodeToFront(SignalNode<Args...>* node)
	{
		// If we don't have a linked list, start one using node
		if (_head == nullptr)
		{
			_head = node;
			return;
		}

		SignalNode<Args...>* nextNode = _head;

		// Update references to follow linked list requirements
		_head = node;
		_head->_next = nextNode;
		nextNode->_prev = _head;
	}


	template<typename ...Args>
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		SignalNode<Args...>* node = _head;

		// Go through all nodes and call their associated function for each one
		while (node != nullptr)
		{
			node->CallFunction(args...);

			node = node->_next;
		}
	}


	template<typename ...Args>
	int SignalSubject<Args...>::Register(FunctionType func)
	{
		FunctionSignalNode<Args...>* node = new FunctionSignalNode<Args...>(this, func);

		AddNodeToFront(node);

		return 1;
	}


	template<typename ...Args>
	int SignalSubject<Args...>::Unregister(FunctionType func)
	{
		SignalNode<Args...>* node = _head;

		// Loop through linked list searching for matching node, then delete it when found
		while (node != nullptr)
		{
			SignalNode<Args...>* currNode = node;
			node = node->_next;

			if(currNode->GetSignalNodeType() != SignalNodeType::FUNCTION) continue;

			FunctionSignalNode<Args...>* functionNode = (FunctionSignalNode<Args...>*) currNode;

			if (functionNode->_func != func) continue;

			if (currNode == _head) _head = currNode->_next;

			delete currNode;

			return 1;
		}

		// If we search whole linked list without finding match, fail
		return 0;
	}


	template<typename ...Args>
	template<typename ObjectType>
	int SignalSubject<Args...>::Register(ObjectType* obj, void(ObjectType::* func)(Args...))
	{
		ObjectSignalNode<ObjectType, Args...>* node = new ObjectSignalNode<ObjectType, Args...>(this, obj, func);

		AddNodeToFront(node);

		return 1;
	}


	template<typename ...Args>
	template<typename ObjectType>
	int SignalSubject<Args...>::Unregister(ObjectType* obj, void(ObjectType::* func)(Args...))
	{
		SignalNode<Args...>* node = _head;

		// Loop through linked list searching for matching node, then delete it when found
		while (node != nullptr)
		{
			SignalNode<Args...>* currNode = node;
			node = node->_next;

			if (currNode->GetSignalNodeType() != SignalNodeType::OBJECT) continue;

			ObjectSignalNode<ObjectType, Args...>* objectNode = (ObjectSignalNode<ObjectType, Args...>*) currNode;

			if(objectNode->_obj != obj) continue;
			if (objectNode->_func != func) continue;

			if (currNode == _head) _head = currNode->_next;

			delete currNode;

			return 1;
		}

		// If we search whole linked list without finding match, fail
		return 0;
	}
	#pragma endregion


	#pragma region SignalNode.cpp
	template<typename ...Args>
	SignalNode<Args...>::SignalNode(SignalSubject<Args...>* subject) : _subject(subject)
	{}


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


	#pragma region FunctionSignalNode.cpp
	template<typename ...Args>
	FunctionSignalNode<Args...>::FunctionSignalNode(SignalSubject<Args...>* subject, FunctionType func) : 
		SignalNode<Args...>(subject), _func(func)
	{}


	template<typename ...Args>
	FunctionSignalNode<Args...>::~FunctionSignalNode() {}


	template<typename ...Args>
	SignalNodeType FunctionSignalNode<Args...>::GetSignalNodeType() const
	{
		return SignalNodeType::FUNCTION;
	}


	template<typename ...Args>
	void FunctionSignalNode<Args...>::CallFunction(Args ...args)
	{
		_func(args...);
	}
	#pragma endregion


	#pragma region ObjectSignalNode.cpp
	template<typename ObjectType, typename ...Args>
	ObjectSignalNode<ObjectType, Args...>::ObjectSignalNode(SignalSubject<Args...>* subject, ObjectType* obj, FunctionType func) :
		SignalNode<Args...>(subject), _obj(obj), _func(func)
	{}


	template<typename ObjectType, typename ...Args>
	ObjectSignalNode<ObjectType, Args...>::~ObjectSignalNode() {}


	template<typename ObjectType, typename ...Args>
	SignalNodeType ObjectSignalNode<ObjectType, Args...>::GetSignalNodeType() const
	{
		return SignalNodeType::OBJECT;
	}


	template<typename ObjectType, typename ...Args>
	void ObjectSignalNode<ObjectType, Args...>::CallFunction(Args ...args)
	{
		(*_obj.*_func)(args...);
	}
	#pragma endregion
}