#include "Input.h"
#include "include/raylib-cpp.hpp"

namespace jothly
{
	bool Input::GetKeyPressed(KeyCode keyCode)
	{
		return IsKeyPressed(keyCode);
	}


	bool Input::GetKeyReleased(KeyCode keyCode)
	{
		return IsKeyReleased(keyCode);
	}


	bool Input::GetKeyDown(KeyCode keyCode)
	{
		return IsKeyDown(keyCode);
	}


	bool Input::GetKeyUp(KeyCode keyCode)
	{
		return IsKeyUp(keyCode);
	}


	bool Input::GetMousePressed(MouseCode mouseCode)
	{
		return IsMouseButtonPressed(mouseCode);
	}


	bool Input::GetMouseReleased(MouseCode mouseCode)
	{
		return IsMouseButtonReleased(mouseCode);
	}


	bool Input::GetMouseButtonDown(MouseCode mouseCode)
	{
		return IsMouseButtonDown(mouseCode);
	}


	bool Input::GetMouseButtonUp(MouseCode mouseCode)
	{
		return IsMouseButtonUp(mouseCode);
	}


	Vector2 Input::GetMousePosition()
	{
		return RMouse::GetPosition();
	}
}