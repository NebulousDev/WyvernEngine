
struct VertexOutput
{
	float4 position : SV_Position;
};

struct PixelOutput
{
	float4 color : SV_Target;
};

PixelOutput PixelMain(VertexOutput input)
{
	PixelOutput output;
	output.color = input.position;
	return output;
}