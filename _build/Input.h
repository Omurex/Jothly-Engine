#pragma once
#include "InputCodes.hpp"
#include "Vector2.h"


namespace jothly
{
	class Input
	{
		public:

		static bool GetKeyJustPressed(KeyCode keyCode);
		static bool GetKeyJustReleased(KeyCode keyCode);
		 
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);
		 
		static bool GetMouseJustPressed(MouseCode mouseCode);
		static bool GetMouseJustReleased(MouseCode mouseCode);
		 
		static bool GetMouseButtonDown(MouseCode mouseCode);
		static bool GetMouseButtonUp(MouseCode mouseCode);
		 
		static Vector2 GetMousePosition();
	};
}