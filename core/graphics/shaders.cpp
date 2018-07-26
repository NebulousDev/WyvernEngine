#include "shaders.h"
#include "graphics.h"

const ShaderHandle CreateShader(const ContextHandle context, const ShaderInfo info)
{
	Shader* shader = NULLPTR;
	((Context*)context)->fpCreateShader(&shader, (Context*)context, info);
	return (ShaderHandle)shader;
}

void DisposeShader(ShaderHandle* shader)
{
	GetCurrentContextData()->fpDisposeShader((Shader**)shader);
	*shader = NULLPTR;
}
