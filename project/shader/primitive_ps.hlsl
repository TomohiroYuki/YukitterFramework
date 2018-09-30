#include "primitive.hlsli"
Texture2D diffuse_map : register(t0);
Texture2D toon_map : register(t1);
SamplerState g_samLinear : register(s0); //サンプラー


float4 PS(VS_OUT_3D pin) : SV_TARGET
{
   //  //return float4(1, 1, 1, 1);
    float4 c = pin.color;
    //c.r += 0.4f;
    //c.g += 0.4f;
    //c.b += 0.4f;
    c.a = 1.0f;
   // return pin.color;
    //return float4(0.5, 0, 0, 1);

 


    return diffuse_map.Sample(g_samLinear, pin.texcoord)+c;
}

float4 PhongShader_PS(VS_OUT_3D pin) : SV_TARGET
{
   //  //return float4(1, 1, 1, 1);
    float4 c = pin.color;
    //c.r += 0.4f;
    //c.g += 0.4f;
    //c.b += 0.4f;
   // c.a = 1.0f;
   //return c;
    //return float4(0.5, 0, 0, 1);

    float4 R = normalize(light_direction - pin.normal * 2 * dot(light_direction, pin.normal));
    float spq = dot(pin.outline_pos, R);

  //  return pin.color * 1.0f;


    return diffuse_map.Sample(g_samLinear, pin.texcoord)*0.65f /*+ c*/ + pow(max(0, spq), 1.4)+ambient_color;
}

float4 GouraudShader_PS(VS_OUT_3D pin) : SV_TARGET
{
   //  //return float4(1, 1, 1, 1);
    float4 c = pin.color;
    //c.r += 0.4f;
    //c.g += 0.4f;
    //c.b += 0.4f;
   // c.a = 1.0f;
   //return c;
    //return float4(0.5, 0, 0, 1);
  
  
  //  return pin.color * 1.0f;

    return c;
    return diffuse_map.Sample(g_samLinear, pin.texcoord) * 0.65f + c ;
}

float4 ToonShader_PS(VS_OUT_3D pin) : SV_TARGET
{
   //  //return float4(1, 1, 1, 1);
    //float4 c = pin.color;
    //c.r += 0.4f;
    //c.g += 0.4f;
    //c.b += 0.4f;
   // c.a = 1.0f;
   //return c;
    //return float4(0.5, 0, 0, 1);
    float4 light_v = light_direction;

    normalize(light_v);
    float p = dot(pin.normal, -light_v);
    p = p * 0.5f + 0.5;
    p = p * p;


    float4 Col = toon_map.Sample(g_samLinear, float2(1.0f - p, 0.0f));
  //  toon_map.Sample(g_samLinear, float2(1.0f - c.r, 0)
   //色情報を格納する
    /*float4 pout = */
    return (Col * diffuse_map.Sample(g_samLinear, pin.texcoord));

  //  return pin.color * 1.0f;
    //float col_len = length(c.rgb);

    //return (diffuse_map.Sample(g_samLinear, pin.texcoord) * 0.65f + c) * toon_map.Sample(g_samLinear, float2(1.0f-c.r,0));
}