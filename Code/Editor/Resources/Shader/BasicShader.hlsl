cbuffer cbPerObject : register(b0)
{
    float4x4 worldViewProj[2];
};

cbuffer cbPass : register(b1)
{
    float3 light;
    float3 eye;
};

struct VertexIn
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float4 color : COLOR;
    uint instanceId : SV_InstanceID;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float3 normalW : NORMAL;
    float4 color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    vout.posH = mul(float4(vin.posL, 1.0f), worldViewProj[vin.instanceId]);
    vout.normalW = vin.normalL;
    vout.color = vin.color;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 color = mul(pin.color, 0.9f);
    float length = max(-dot(pin.normalW, normalize(float3(1.0f, -2.0f, 3.0f))), 0.1f);
    color = mul(color, length);
    return color;
}
