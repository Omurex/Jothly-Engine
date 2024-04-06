#include "Input.h"
#include "include/raylib-cpp.hpp"

namespace jothly
{
	bool Input::GetKeyJustPressed(KeyCode keyCode)
	{
		return IsKeyPressed((int) keyCode);
	}


	bool Input::GetKeyJustReleased(KeyCode keyCode)
	{
		return IsKeyReleased((int) keyCode);
	}


	bool Input::GetKeyDown(KeyCode keyCode)
	{
		return IsKeyDown((int) keyCode);
	}


	bool Input::GetKeyUp(KeyCode keyCode)
	{
		return IsKeyUp((int) keyCode);
	}


	bool Input::GetMouseJustPressed(MouseCode mouseCode)
	{
		return IsMouseButtonPressed((int) mouseCode);
	}


	bool Input::GetMouseJustReleased(MouseCode mouseCode)
	{
		return IsMouseButtonReleased((int) mouseCode);
	}


	bool Input::GetMouseButtonDown(MouseCode mouseCode)
	{
		return IsMouseButtonDown((int) mouseCode);
	}


	bool Input::GetMouseButtonUp(MouseCode mouseCode)
	{
		return IsMouseButtonUp((int) mouseCode);
	}


	Vector2 Input::GetMousePosition()
	{
		return RMouse::GetPosition();
	}
}