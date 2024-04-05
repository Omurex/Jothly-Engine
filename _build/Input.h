#pragma once
#include "InputCodes.hpp"
#include "Vector2.h"


namespace jothly
{
	class Input
	{
		public:

		static bool GetKeyPressed(KeyCode keyCode);
		static bool GetKeyReleased(KeyCode keyCode);
		 
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);
		 
		static bool GetMousePressed(MouseCode mouseCode);
		static bool GetMouseReleased(MouseCode mouseCode);
		 
		static bool GetMouseButtonDown(MouseCode mouseCode);
		static bool GetMouseButtonUp(MouseCode mouseCode);
		 
		static Vector2 GetMousePosition();
	};
}