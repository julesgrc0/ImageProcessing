#pragma once

typedef enum ImageTypes
{
	PNG,
	JPEG,
	BPM,
	PPM
} ImageTypes;

typedef struct Size
{
	int width;
	int height;
} Size;

typedef struct Rgb
{
	int r, g, b;
} Rgb;

typedef struct Point
{
	int x, y;
} Point;
