
struct VertexInput
{
	float4 position : POSITION0;
};

struct VertexOutput
{
	float4 position : POSITION0;
};

VertexOutput VertexMain(VertexInput input)
{
	VertexOutput output;
	output.position = input.position;

	return output;
}