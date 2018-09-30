#include "sprite.hlsli"

VS_OUT main(float4 pos : POSITION, float4 color : COLOR,float2 texcoord:TEXCOORD)
{

	VS_OUT vout;
	vout.pos = pos;
    vout.pos.w = 1.0f;
	vout.color = color;
    vout.tex = texcoord;
	return vout;
}