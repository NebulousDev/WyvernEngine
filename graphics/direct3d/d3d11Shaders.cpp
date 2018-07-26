#include "d3d11Shaders.h"

RESULT D3D11CreateShader(Shader** shader, const Context* context, const ShaderInfo info)
{
	*shader = new Shader();

	//HRESULT result = D3DX11CompileFromFile;

	return SUCCESS;
}

RESULT D3D11DisposeShader(Shader* shader)
{
	delete shader;
	return SUCCESS;
}
