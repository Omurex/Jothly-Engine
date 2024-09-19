#pragma once

#include <SFML/Window.hpp>
#include "InputCodes.hpp"


namespace jothly
{
	class Input
	{
		// Have additional array + 


		static bool _justPressedKeys[];
		static bool _justReleasedKeys[(unsigned short) KeyCode::KeyCount];

		static bool _justPressedMouseButton[(unsigned short) MouseCode::ButtonCount];
		static bool _justReleasedMouseButton[(unsigned short) MouseCode::ButtonCount];


		public:

		static bool GetKeyJustPressed(KeyCode keyCode);
		static bool GetKeyJustReleased(KeyCode keyCode);

		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);

		static bool GetMouseButtonJustPressed(MouseCode mouseCode);
		static bool GetMouseButtonJustReleased(MouseCode mouseCode);

		static bool GetMouseButtonDown(MouseCode mouseCode);
		static bool GetMouseButtonUp(MouseCode mouseCode);
	};
}