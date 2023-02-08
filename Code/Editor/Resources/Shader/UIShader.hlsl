cbuffer cbPerObject : register(b0)
{
    float4x4 viewProj;
    //float4x4 world[16];
    //float ratio[16];
};

struct VertexIn
{
    float3 posL : POSITION;
    float2 texCoord : TEXCOORD;
    float4 color : COLOR;
    uint instanceId : SV_InstanceID;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float4 color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    //float4 pos = mul(float4(vin.posL, 1.0f), world[vin.instanceId]);
    //vout.posH = mul(float4(pos.x, pos.y + vin.instanceId * 100.0f, pos.z, pos.w), viewProj);
    vout.posH = mul(float4(vin.posL, 1.0f), viewProj);
    vout.texCoord = vin.texCoord;
    vout.color = vin.color;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.color;
}
