#include "Input.h"


namespace jothly
{
	#define CODE_TO_INDEX(code) (unsigned short) code
	#define KEY_TO_SF(code) (sf::Keyboard::Key) code
	#define MOUSE_TO_SF(code) (sf::Mouse::Button) code

	bool Input::_justPressedKeys[CODE_TO_INDEX(KeyCode::KeyCount)] = { false };
	bool Input::_justReleasedKeys[CODE_TO_INDEX(KeyCode::KeyCount)] = { false };

	bool Input::_justPressedMouseButton[CODE_TO_INDEX(MouseCode::ButtonCount)] = { false };
	bool Input::_justReleasedMouseButton[CODE_TO_INDEX(MouseCode::ButtonCount)] = { false };


	bool Input::GetKeyJustPressed(KeyCode keyCode)
	{
		return _justPressedKeys[CODE_TO_INDEX(keyCode)];
	}


	bool Input::GetKeyJustReleased(KeyCode keyCode)
	{
		return _justReleasedKeys[CODE_TO_INDEX(keyCode)];
	}


	bool Input::GetKeyDown(KeyCode keyCode)
	{
		return sf::Keyboard::isKeyPressed(KEY_TO_SF(keyCode));
	}


	bool Input::GetKeyUp(KeyCode keyCode)
	{
		return !GetKeyDown(keyCode);
	}


	bool Input::GetMouseButtonJustPressed(MouseCode mouseCode)
	{
		return _justPressedMouseButton[CODE_TO_INDEX(mouseCode)];
	}


	bool Input::GetMouseButtonJustReleased(MouseCode mouseCode)
	{
		return _justReleasedMouseButton[CODE_TO_INDEX(mouseCode)];
	}


	bool Input::GetMouseButtonDown(MouseCode mouseCode)
	{
		return sf::Mouse::isButtonPressed(MOUSE_TO_SF(mouseCode));
	}


	bool Input::GetMouseButtonUp(MouseCode mouseCode)
	{
		return !GetMouseButtonDown(mouseCode);
	}
}