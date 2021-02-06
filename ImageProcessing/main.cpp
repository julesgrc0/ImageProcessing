#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "ImageGeneration.h"
#include "ImageDraw.h"

int main(int argc, const char *argv)
{
	/*
	Bug image not work if width and height are not equal
	*/
	ImageGeneration img = ImageGeneration("test", {500, 500});
	/**/

	img.setOutputPath(std::filesystem::path("C:\\Users\\jules\\OneDrive\\Images\\"));
	
	ImageDraw draw = ImageDraw(img.getImageMatrix(), img.getImageBounds());

	draw.setColor({ 169, 44, 222 });
	
	draw.DrawArc({ 10,10 }, { 100,200 }, 80, 180);

	draw.setColor({ 169, 44, 0 });
	
	draw.DrawFillTriangle({ 100,100 }, 40, 100, 20);

	draw.setColor({ 169, 0, 222 });

	draw.DrawFillCirlce({-50, 0}, 100);

	draw.setColor({255, 255, 255});

	draw.DrawRect({-50, 0}, {200, 200});

	draw.setColor({ 0, 44, 222 });

	draw.DrawLine({ 0,0 }, { 100,20 });

	img.setImageMatrix(draw.getMatrix());

	img.createImage(PNG);

	std::cout << img.getOutputPath().string() << std::endl;

	return 0;
}
