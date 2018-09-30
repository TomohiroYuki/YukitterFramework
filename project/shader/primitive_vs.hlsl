#include "primitive.hlsli"

const float3 up = (0.0f, 1.0f, 0.0f);
const float4 skyblue = float4(0.3f, 0.7f, 0.9f, 1.0f);
const float4 ground = float4(0.2f, 0.1f, 0.05f, 1.0f);

VS_OUT_3D VS(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VS_OUT_3D vout;
    normal.w = 0.0;
    normal = normalize(normal);

    //vout.outline_pos = position + normal * 0.05f;
    //vout.outline_pos = position;
    //vout.outline_pos += normal *1.15f;
    vout.position = mul(position, world_view_projection);

    //vout.outline_pos = mul(vout.outline_pos, world_view_projection);
    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));
    float4 L = normalize(-light_direction);
    vout.color = material_color * max(0, dot(L, N));
    //vout.color = material_color;

    //vout.color.a = 1;
    vout.texcoord = texcoord;
    vout.normal = N;
    return vout;
}



VS_OUT_3D PhongShader_VS(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VS_OUT_3D vout;
    normal.w = 0.0;
    normal = normalize(normal);

  
    vout.position = mul(position, world_view_projection);

  
    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));
    float4 L = normalize(-light_direction);
    vout.color = material_color * max(0, dot(L, N));
    //vout.color = material_color;

    //vout.color.a = 1;
    vout.texcoord = texcoord;
    vout.normal = N;

    
    vout.outline_pos = normalize(camera_location - position);

    //VS_OUT Out;
    //Out.pos = mul(In.pos, Transform);
    //Out.normal = In.normal.xyz;
    //Out.color = Color * max(LightColor * Brightness * dot(LightVector, In.normal.xyz), Ambient) + SelfBrightness;
    //Out.V = normalize(EyeLocation - In.pos.xyz);



    

    return vout;
}




VS_OUT_3D GouraudShader_VS(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VS_OUT_3D vout;
    normal.w = 0.0;
    normal = normalize(normal);

  
    vout.position = mul(position, world_view_projection);

  
    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));
    float4 L = normalize(-light_direction);
    
    //vout.color = material_color;

    //vout.color.a = 1;
    vout.texcoord = texcoord;
    vout.normal = N;

    
    vout.outline_pos = normalize(camera_location - position);

    //VS_OUT Out;
    //Out.pos = mul(In.pos, Transform);
    //Out.normal = In.normal.xyz;
    //Out.color = Color * max(LightColor * Brightness * dot(LightVector, In.normal.xyz), Ambient) + SelfBrightness;
    //Out.V = normalize(EyeLocation - In.pos.xyz);

    float4 R = normalize(light_direction - normal * 2 * dot(light_direction, normal));
    float spq = dot(vout.outline_pos, R);

    vout.color = material_color * max(0, dot(L, N)) * spq + ambient_color;
    

    return vout;
}




VS_OUT_3D ToonShader_VS(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VS_OUT_3D vout;
    normal.w = 0.0;
    normal = normalize(normal);

  
    vout.position = mul(position, world_view_projection);

  
    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));
    float4 L = normalize(-light_direction);
    
    //vout.color = material_color;

    //vout.color.a = 1;
    vout.texcoord = texcoord;
    vout.normal = N;

    
    vout.outline_pos = normalize(camera_location - position);

    //VS_OUT Out;
    //Out.pos = mul(In.pos, Transform);
    //Out.normal = In.normal.xyz;
    //Out.color = Color * max(LightColor * Brightness * dot(LightVector, In.normal.xyz), Ambient) + SelfBrightness;
    //Out.V = normalize(EyeLocation - In.pos.xyz);

   

    vout.color = material_color * max(0, dot(L, N)) + ambient_color;
    

    return vout;
}




VS_OUT_3D HemisphereShader(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
    VS_OUT_3D vout;
    normal.w = 0.0;
    normal = normalize(normal);

  
    vout.position = mul(position, world_view_projection);

  
    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));
    float4 L = normalize(-light_direction);
    
    //vout.color = material_color;

    //vout.color.a = 1;
    vout.texcoord = texcoord;
    vout.normal = N;

    
    vout.outline_pos = normalize(camera_location - position);

    //VS_OUT Out;
    //Out.pos = mul(In.pos, Transform);
    //Out.normal = In.normal.xyz;
    //Out.color = Color * max(LightColor * Brightness * dot(LightVector, In.normal.xyz), Ambient) + SelfBrightness;
    //Out.V = normalize(EyeLocation - In.pos.xyz);

    float4 R = normalize(light_direction - normal * 2 * dot(light_direction, normal));
    float spq = dot(vout.outline_pos, R);
    float c = dot(up, normal.xyz);
    c = (c + 1.0f) * 0.5f;
    float4 col = skyblue * c + ground * -c;
    vout.color = material_color * max(0, dot(L, N)) * spq + ambient_color + col;;
    
    vout.color = col;
    return vout;
}

//  float c=dot(up, normal.xyz);
//float4 col = skyblue * c + ground * -c;