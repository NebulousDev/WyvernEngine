#include "layout.h"
#include "graphics.h"

static InputLayout	sLayouts[MAX_INPUT_LAYOUTS] = {};
static uint32		sNextLayout = 0;
static bool8		sInitialized = false;

bool8 ValidateLayoutHandle(InputLayoutHandle hHandle)
{
	return hHandle > -1 && hHandle < (MAX_INPUT_LAYOUTS + 1) && sLayouts[hHandle].valid;
}

const InputLayoutHandle CreateInputLayout(const InputLayoutInfo info)
{
	if (!sInitialized)
	{
		for (uint32 i = 0; i < MAX_INPUT_LAYOUTS; i++)
		{
			sLayouts[i].hID = i;
			sLayouts[i].hNext = i + 1;
		}

		sInitialized = true;
	}

	InputLayoutHandle hLayout = sNextLayout;

	if (sNextLayout > MAX_INPUT_LAYOUTS)
	{
		//TODO: throw error?
		return INVALID_HANDLE;
	}

	InputLayout* pLayout = &sLayouts[hLayout];
	pLayout->pElements = info.pElements;
	pLayout->elementCount = info.elementCount;
	pLayout->valid = true;

	if (!GetCurrentContext()->fpCreateInputLayout(&pLayout, GetCurrentContext(), info))
	{
		//TODO: throw error?
		return INVALID_HANDLE;
	}

	sNextLayout = sLayouts[hLayout].hNext;

	return hLayout;
}

RESULT ReleaseInputLayout(InputLayoutHandle* phInputLayout)
{
	if (phInputLayout != NULLPTR && ValidateLayoutHandle(*phInputLayout))
	{
		InputLayout* pInputLayout = &sLayouts[*phInputLayout];
		if (GetCurrentContext()->fpReleaseInputLayout(&pInputLayout, GetCurrentContext()))
		{
			sLayouts[*phInputLayout].hNext = sNextLayout;
			sNextLayout = sLayouts[*phInputLayout].hID;
			pInputLayout->valid = false;
			*phInputLayout = INVALID_HANDLE;
			return SUCCESS;
		}
	}

	return FAILURE;
}

RESULT BindInputLayout(InputLayoutHandle hInputLayout)
{
	if (ValidateLayoutHandle(hInputLayout))
		return GetCurrentContext()->fpBindInputLayout(&sLayouts[hInputLayout], GetCurrentContext());
	return FAILURE;
}

RESULT UnbindInputLayout(InputLayoutHandle hInputLayout)
{
	if (ValidateLayoutHandle(hInputLayout))
		return GetCurrentContext()->fpUnbindInputLayout(&sLayouts[hInputLayout], GetCurrentContext());
	return FAILURE;
}