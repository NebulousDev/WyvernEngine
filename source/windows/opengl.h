#pragma once
#include "header.h"

//TODO: Make color depth display dependent
#define PIXEL_COLOR_BITS 32
#define PIXEL_DEPTH_BITS 32

RESULT GLCreateContext(GraphicsContext* glContext, GraphicsDevice device);

RESULT GLMakeContextCurrent(GraphicsDevice device, GraphicsContext context);

RESULT GLDeleteContext(GraphicsContext context);