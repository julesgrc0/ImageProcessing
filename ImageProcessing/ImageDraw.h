#pragma once
#include <iostream>
#include "ImagesProperties.h"
#include "ImageGeneration.h"

class ImageDraw
{
public:
	/**
	 * @param matrix char*
	 * @param size Size
	*/
	ImageDraw(char *matrix, Size size);

	/**
	 * Set a new color for draw
	 * @param color Rgb
	 * @return void
	*/
	void setColor(Rgb color);
	/**
	 * Return the actual color
	 * @return Rgb
	*/
	Rgb getColor();
	/**
	 * Change the actual matrix
	 * @param matrix char*
	 * @param size Size
	 * @return void
	*/
	void setMatrix(char *matrix, Size size);
	/**
	 * Return the final matrix result
	 * @return char*
	*/
	char *getMatrix();
	/**
	 * Set the background of your image
	 * @param color Rgb
	 * @return void
	*/
	void DrawBackground(Rgb color);
	/**
	 * Set the background of your image from the actual color
	 * @overload
	 * @return void
	*/
	void DrawBackground();
	/**
	 * Draw the perimeter of a circle
	 * @param r int
	 * @param center Point
	 * @return void
	*/
	void DrawCircle(Point center, int r);
	/**
	 * Draw a line between two point
	 * @param end Point
	 * @param start Point
	 * @return void
	*/
	void DrawLine(Point start, Point end);
	/**
	 * Draw the perimeter of a rect
	 * @param pos Point
	 * @param size Size
	 * @return void
	*/
	void DrawRect(Point pos, Size size);
	/**
	 * Draw a the perimeter of a triangle. 
	 * @param pos Point
	 * @param base int
	 * @param height int
	 * Where triangle is split
	 * @param place int
	 * @return void
	*/
	void DrawTriangle(Point pos, int base, int height, int place);
	/**
	 * Draw a rect fill
	 * @param pos Point
	 * @param size Size
	 * @return void
	*/
	void DrawFillRect(Point pos, Size size);
	/**
	 * Draw fill circle
	 * @param center Point
	 * @param r int
	 * @return void
	*/
	void DrawFillCirlce(Point center, int r);
	/**
	 * Draw a fill triangle
	 * @param pos Point
	 * @param base int
	 * @param height int
	 * @param place int
	 * @return void
	*/
	void DrawFillTriangle(Point pos, int base, int height,int place);
	/**
	 * Draw an Arc
	 * @param start Point
	 * @param size Size
	 * @param StartAngle int
	 * @param EndAngle int
	 * @return void
	*/
	void DrawArc(Point start, Size size, int StartAngle, int EndAngle);
	/**
	 * Set a pixel on matrix
	 * @param pos Point
	 * @return bool (false if not on matrix)
	*/
	bool DrawPixel(Point pos);

private:
	/**
	 * Check if a point is out of the image
	 * @param pos Point
	 * @return bool (true if out)
	*/
	bool isOut(Point pos);
	Size size = {100, 100};
	Rgb color = {0, 0, 0};
	char *matrix;
	int BytesPerPixel = 3;
	int diff = 0;
};
