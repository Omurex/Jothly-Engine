#pragma once

#include "raylib.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace jothly
{
	class Transform
	{
		public:
		Vector3 pos;
		Quaternion rot;
		Vector3 scale;
	};
}