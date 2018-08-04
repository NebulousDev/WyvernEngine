#include "graphics.h"

RESULT Present()
{
	return GetCurrentContext()->fpPresent(GetCurrentContext());
}