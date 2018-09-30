#define MAX_BONES 64

cbuffer constant_buffer : register(b0)
{
    row_major float4x4 world_view_projection;
    row_major float4x4 world_inverse_transpose;
    float4 material_color;
    float4 light_direction;
    row_major float4x4 bone_transforms[MAX_BONES];
    float4 camera_location;
    float4 ambient_color;
};




struct VS_OUT_3D
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float2 texcoord : TEXCOORD;
    float4 outline_pos : OUTLINE;

};