#include "sprite.hlsli"

Texture2D diffuse_map : register(t0);
SamplerState diffuse_map_sampler_state : register(s0);


float4 main(VS_OUT pin, float4 color : COLOR) : SV_TARGET
{
    pin.color *= color;
    float4 dif_map = diffuse_map.Sample(diffuse_map_sampler_state, pin.tex);
    dif_map.a = min(dif_map.a, color.a);
    return dif_map;


   

}