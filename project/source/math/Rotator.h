#pragma once
#include "source\math\Vector.h"
#include <DirectXMath.h>

namespace Yukitter
{

	struct Rotator
	{
	public:
		float yaw;
		float roll;
		float pitch;

		F_INLINE Rotator() :
			yaw(0), roll(0), pitch(0) {}

		F_INLINE Rotator(float yaw,float roll,float pitch) :
			yaw(yaw), roll(roll), pitch(pitch) {}

		F_INLINE Rotator& operator =  (const Rotator& r) { yaw = r.yaw; roll = r.roll; pitch = r.pitch; return *this; }

		F_INLINE Rotator& operator += (const Rotator& r) { yaw += r.yaw; roll += r.roll; pitch += r.pitch; return *this; }
		F_INLINE Rotator& operator -= (const Rotator& r) { yaw -= r.yaw; roll -= r.roll; pitch -= r.pitch; return *this; }
		
		/*inline Rotator FindLookAtRotation(Vector start,Vector target)
		{
			
			DirectX::XMMatrixRotationAxis(DirectX::XMVECTOR(start), 0);
		}*/

	};


}