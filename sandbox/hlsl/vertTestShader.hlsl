
struct VSInput
{
	float3 vertPosition : POSITION;
	float4 vertColor : COLOR;
};

struct VSOutput
{
	float3 interpPosition : POSITION;
	float4 interpColor : COLOR;
};

VSOutput VertexMain(VSInput input)
{
	VSOutput output;
	output.interpPosition = input.vertPosition;
	output.interpColor = input.vertColor;

	return output;
}