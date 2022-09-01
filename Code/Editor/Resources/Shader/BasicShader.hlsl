cbuffer cbPerObject : register(b0)
{
    float4x4 viewProj;
    float4x4 world[3];
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
    float4 pos = mul(float4(vin.posL, 1.0f), world[vin.instanceId]);
    vout.posH = mul(pos, viewProj);
    vout.normalW = mul(float4(vin.normalL, 1.0f), world[vin.instanceId]);
    vout.color = vin.color;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 color = mul(pin.color, 0.9f);
    float length = max(dot(pin.normalW, normalize(light)), 0.1f);
    color = mul(color, length);
    return color;
}
