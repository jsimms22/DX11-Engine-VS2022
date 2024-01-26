#pragma once
#include <DirectXMath.h>

namespace graphics
{
	struct Vertex
	{
		Vertex() { }
		Vertex(float _x, float _y)
			: pos(_x,_y) { }
		DirectX::XMFLOAT2 pos
	};
}