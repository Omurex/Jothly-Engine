#pragma once

#include "Vector3.h"
#include "Quaternion.h"

namespace jothly
{
	class rlb_Transform
	{
		public:
		rlb_Vector3 pos;
		rlb_Quaternion rot;
		rlb_Vector3 scale;


		rlb_Transform(rlb_Vector3 _pos = rlb_Vector3(0), rlb_Quaternion _rot = rlb_Quaternion(), rlb_Vector3 _scale = rlb_Vector3(1))
			: pos(_pos), rot(_rot), scale(_scale) {}

		rlb_Transform(const rlb_Transform& trans) : pos(trans.pos), rot(trans.rot), scale(trans.scale) {}
	};
}