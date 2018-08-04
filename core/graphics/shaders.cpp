#include "shaders.h"
#include "graphics.h"

const ShaderHandle CreateShader(const ContextHandle context, const ShaderInfo info)
{
	Shader* pShader = NULLPTR;
	((Context*)context)->fpCreateShader(&pShader, (Context*)context, info);
	return (ShaderHandle)pShader;
}

void ReleaseShader(ShaderHandle* phShader)
{
	GetCurrentContext()->fpReleaseShader((Shader**)phShader);
	*phShader = NULLPTR;
}

RESULT BindShader(ShaderHandle hShader)
{
	return GetCurrentContext()->fpBindShader((Shader*)hShader, GetCurrentContext());
}

RESULT UnbindShader()
{
	return GetCurrentContext()->fpUnbindShader(GetCurrentContext());
}