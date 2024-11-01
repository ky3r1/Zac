#include "Ramp_shader.hlsli"

VS_OUT main(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float3 tangent : TANGENT,
	float2 texcoord : TEXCOORD,
	float4 color : COLOR,
	float4 boneWeights : WEIGHTS,
	uint4 boneIndices : BONES
)
{
    float4 p = { 0, 0, 0, 0 };
    float3 n = { 0, 0, 0 };
    for (int i = 0; i < 4; i++)
    {
        p += (boneWeights[i] * mul(position, boneTransforms[boneIndices[i]]));
        n += (boneWeights[i] * mul(float4(normal.xyz, 0), boneTransforms[boneIndices[i]])).xyz;
    }

    VS_OUT vout;
    vout.position = mul(p, view_projection);

    float3 N = normalize(n);
    float3 L = normalize(-directional_light_direction.xyz);
    float d = dot(L, N);
    float power = max(0, d) * 0.5f + 0.5f;
    
    vout.world_normal.rgb = N;
    vout.world_position.xyz = p;
    vout.color.rgb = color.rgb * materialColor.rgb * power;
    vout.color.a = color.a * materialColor.a;
    vout.texcoord = texcoord;

    return vout;
}