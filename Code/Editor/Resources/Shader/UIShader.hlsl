cbuffer cbPerObject : register(b0)
{
    float4x4 viewProj;
    float4 time;
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
    float xdist = abs(0.5f - vin.texCoord.x);
    float ydist = abs(0.5f - vin.texCoord.y);
    float dist = sqrt(xdist * xdist + ydist * ydist);
    dist = cos(dist * 50.0f + -time.x * 4.0f) * 2.0f;
    float4 pos = float4(vin.posL.x, vin.posL.y + dist, vin.posL.z, 1.0f);
    vout.posH = mul(pos, viewProj);
    vout.texCoord = vin.texCoord;
    vout.color = float4(vout.texCoord.xy, 0.0f, 1.0f);
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.color;
}
