Texture2D mainTex : register(t0);
SamplerState mainSampler : register(s0);

struct VertexIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

struct VertexOut
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.color = vin.color;
    vout.uv = vin.uv;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 color = mainTex.Sample(mainSampler, pin.uv) * pin.color;
    return color;
}
