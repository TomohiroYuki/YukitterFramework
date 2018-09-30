#include "primitive.hlsli"



VS_OUT_3D VS(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD, float4 bone_weight : WEIGHT, uint4 bone_indices : BONES)
{
    VS_OUT_3D vout;
    normal.w = 0.0;
    normal = normalize(normal);
    vout.position = mul(position, world_view_projection);
    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));
    float4 L = normalize(-light_direction);
    vout.color = material_color * max(0, dot(L, N));
    vout.texcoord = texcoord;
    vout.normal = N;
    //return vout;
 

    float3 p = { 0, 0, 0 };
    float3 n = { 0, 0, 0 };
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        p += (bone_weight[i] * mul(position, bone_transforms[bone_indices[i]])).xyz;
        n += (bone_weight[i] * mul(float4(normal.xyz, 0), bone_transforms[bone_indices[i]])).xyz;
    }
    position = float4(p, 1.0f);
    normal = float4(n, 0.0f);



    //float4 influence = { 0, 0, 0, 1 };
    //for (int s = 0; s < 4; s++)
    //{
    //    float weight = bone_weight[s];
    //    if (weight > 0.0f)
    //    {
    //        //influence.r = 1;
    //        switch (bone_indices[s])
    //        {

    //            case 0:
    //                influence.r = weight;
    //                break;
    //            case 1:
    //                influence.g = weight;
    //                break;
    //            case 2:
    //                influence.b = weight;
    //                break;
    //        }
    //    }
    //}


    ////influence.r = 1;
    //vout.color = influence;
    

    //vout.color = material_color * max(0, dot(L, N));
    vout.position = mul(position, world_view_projection);

    //vout.color.a = 1;
    vout.texcoord = texcoord;
    vout.normal = N;
    return vout;
}