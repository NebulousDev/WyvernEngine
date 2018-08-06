
struct VSInput
{
	float3 vertPosition : POSITION;
	float4 vertColor : COLOR;
};

struct VSOutput
{
	float4 interpPosition : SV_POSITION;
	float4 interpColor : COLOR;
};

VSOutput VertexMain(VSInput input)
{
	VSOutput output;
	output.interpPosition = float4(input.vertPosition, 1.0f);
	output.interpColor = input.vertColor;
	return output;
}