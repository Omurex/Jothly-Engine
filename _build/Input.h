#pragma once
#include "InputCodes.hpp"
#include "Vector2.h"


namespace jothly
{
	class Input
	{
		bool GetKeyPressed(KeyCode keyCode);
		bool GetKeyReleased(KeyCode keyCode);
		
		bool GetKeyDown(KeyCode keyCode);
		bool GetKeyUp(KeyCode keyCode);

		bool GetMousePressed(MouseCode mouseCode);
		bool GetMouseReleased(MouseCode mouseCode);

		bool GetMouseButtonDown(MouseCode mouseCode);
		bool GetMouseButtonUp(MouseCode mouseCode);

		Vector2 GetMousePosition();
	};
}