#pragma once

#include "Vector3.h"
#include "Quaternion.h"

namespace jothly
{
	class rlb_Transform
	{
		public:
		Vector3 pos;
		Quaternion rot;
		Vector3 scale;


		rlb_Transform(Vector3 _pos = Vector3(0), Quaternion _rot = Quaternion(), Vector3 _scale = Vector3(1))
			: pos(_pos), rot(_rot), scale(_scale) {}

		rlb_Transform(const rlb_Transform& trans) : pos(trans.pos), rot(trans.rot), scale(trans.scale) {}
	};
}