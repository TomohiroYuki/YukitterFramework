#include "primitive.hlsli"

struct GSOutput
{
    float4 pos : SV_POSITION;
};

[maxvertexcount(6)]
void main(
	triangle VS_OUT_3D input[3] : SV_POSITION,
	inout TriangleStream<VS_OUT_3D> output
)
{
    VS_OUT_3D Out = (VS_OUT_3D) 0;

    uint i = 0;
    for (i = 0; i < 3; i++)
    {
       
        Out.position = input[i].position;
        Out.normal = input[i].normal;
        Out.color = input[i].color;
        Out.texcoord = input[i].texcoord;
        output.Append(Out);
    }
    output.RestartStrip();
    //a
    for (i = 0; i < 3; i++)
    {
        Out.position = input[2 - i].outline_pos;
        Out.normal = input[2 - i].normal;
        Out.color = float4(1,1,1,1);
        Out.texcoord = input[2 - i].texcoord;
        output.Append(Out);
    }
    output.RestartStrip();

    //aa


    //for (i = 0; i < 3; i++)
    //{
       
    //    Out.position = input[i].position + float4(200,0,0,0);
    //    Out.normal = input[i].normal;
    //    Out.color = input[i].color;
    //    Out.texcoord = input[i].texcoord;
    //    output.Append(Out);
    //}
    //output.RestartStrip();


    //for (int j = 2; j >= 0; j--)
    //{
       
    //    //Out.position = mul(input[j - 1].position + input[j - 1].normal /** 0.05f*/, world_view_projection) + float4(200, 0, 0, 0);
    //    //Out.position = input[j - 1].outline_pos;
    //    //Out.normal = -input[j - 1].normal;
    //    //Out.color = float4(0, 0, 0, 1);
    //    //Out.texcoord = input[j - 1].texcoord;
    //    //output.Append(Out);
    //    Out.position = input[j ].outline_pos;
    //    Out.normal = input[j ].normal;
    //    Out.color.rgb = 0.0;
    //    Out.color.a = 1.0;
    //    Out.texcoord = input[j ].texcoord;
    //    output.Append(Out);
    //}
    //output.RestartStrip();


    //for (uint j = 2; j <= 0; j--)
    //{
    //    GSOutput element;
    //    element.pos = input[j].position*input[j].normal*0.5f;
    //    output.Append(element);
    //}

    //output.RestartStrip();
}