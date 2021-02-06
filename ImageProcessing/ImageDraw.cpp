#include <iostream>
#include "ImageDraw.h"

ImageDraw::ImageDraw(char *matrix, Size size)
{
	this->matrix = matrix;
	this->size = size;
	if (size.height != size.width)
	{
		if (size.width > size.height)
		{
			for (int i = size.height; i < size.width; i++)
			{
				this->diff++;
			}
		}
		else 
		{
			for (int i = size.width; i < size.height; i++)
			{
				this->diff++;
			}
		}
	}
}

void ImageDraw::setColor(Rgb color)
{
	this->color = color;
}

Rgb ImageDraw::getColor()
{
	return this->color;
}

char *ImageDraw::getMatrix()
{
	return this->matrix;
}

void ImageDraw::setMatrix(char *matrix, Size size)
{
	this->matrix = matrix;
	this->size = size;
}

bool ImageDraw::DrawPixel(Point point)
{
	Point pos = 
	{
		(this->size.height - point.y) - 1,
		point.x - this->diff* ((this->size.height - point.y) - 1)
	};
	int max = (this->size.width * this->size.height * this->BytesPerPixel + this->size.height * this->BytesPerPixel);
	int min = 0;
	int value = (pos.x * this->size.height * this->BytesPerPixel + pos.y * this->BytesPerPixel);
	if (value >= min && value < max)
	{
		if (pos.x < this->size.width && pos.y < this->size.height)
		{
			*(this->matrix + pos.x * this->size.height * this->BytesPerPixel + pos.y * this->BytesPerPixel + 2) = this->color.r;
			*(this->matrix + pos.x * this->size.height * this->BytesPerPixel + pos.y * this->BytesPerPixel + 1) = this->color.g;
			*(this->matrix + pos.x * this->size.height * this->BytesPerPixel + pos.y * this->BytesPerPixel + 0) = this->color.b;
			return true;
		}
	}
	return false;
}

void ImageDraw::DrawLine(Point start, Point end)
{
	int x1 = end.x, y1 = end.y;
	int x0 = start.x, y0 = start.y;

	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	while(true)
	{
		if (!this->isOut({ x0,y0 }))
		{
			this->DrawPixel({ x0,y0 });
		}
		if (x0 == x1 && y0 == y1)
		{
			break;
		}
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx; 
		}
		if (e2 < dy)
		{ 
			err += dx;
			y0 += sy;
		}
	}
}

void ImageDraw::DrawCircle(Point pos, int r)
{
	const double PI = 3.1415926535;

	for (double angle = 0; angle <= 360; angle += 0.5)
	{
		int x1 = r * cos(angle * PI / 180);
		int y1 = r * sin(angle * PI / 180);

		int x = (pos.x + r + x1);
		int y = (pos.y + r + y1);
		if (!this->isOut({ x,y }))
		{
			this->DrawPixel({ x,y });
		}
	}
}

void ImageDraw::DrawArc(Point pos,Size size,int StartAngle,int EndAngle)
{
	int r = size.width / 2 + size.height^2 / (8 * size.width);
	const double PI = 3.1415926535;

	for (double angle = StartAngle; angle <= EndAngle; angle += 0.5)
	{
		int x1 = r * cos(angle * PI / 180);
		int y1 = r * sin(angle * PI / 180);

		int x = (pos.x + r + x1);
		int y = (pos.y + r + y1);
		if (!this->isOut({ x,y }))
		{
			this->DrawPixel({ x,y });
		}
	}
}

void ImageDraw::DrawRect(Point pos, Size size)
{
	for (int i = pos.x; i <= pos.x + size.width; i++)
	{
		if (!this->isOut({ i, pos.y }))
		{
			this->DrawPixel({ i, pos.y });
		}

		if (!this->isOut({ i, pos.y + size.height }))
		{
			this->DrawPixel({ i, pos.y + size.height });
		}
	}
	for (int i = pos.y; i <= pos.y + size.height; i++)
	{
		if (!this->isOut({ pos.x, i }))
		{
			this->DrawPixel({ pos.x, i });
		}

		if (!this->isOut({ pos.x + size.width, i }))
		{
			this->DrawPixel({ pos.x + size.width, i });
		}
		
	}
}

void ImageDraw::DrawTriangle(Point pos, int base, int height,int place)
{
	this->DrawLine({ pos.x,pos.y }, { pos.x + base,pos.y });
	
	this->DrawLine({ pos.x,pos.y }, {pos.x+place,pos.y-height});

	this->DrawLine({ pos.x + base, pos.y }, { (pos.x + base) - place,pos.y - height });
}

void ImageDraw::DrawBackground()
{
	for (int i = 0; i <= this->size.width; i++)
	{
		for (int j = 0; j < this->size.height; j++)
		{
			this->DrawPixel({ i,j });
		}
	}
}

void ImageDraw::DrawBackground(Rgb color)
{
	Rgb last = this->getColor();
	this->setColor(color);
	for (int i = 0; i <= this->size.width; i++)
	{
		for (int j = 0; j < this->size.height; j++)
		{
			this->DrawPixel({ i,j });
		}
	}
	this->setColor(last);
}

void ImageDraw::DrawFillCirlce(Point pos, int r)
{
	int ox = pos.x + r;
	int oy = pos.y + r;

	for (int x = -r; x < r; x++)
	{
		int height = sqrt(r * r - x * x);

		for (int y = -height; y < height; y++)
		{
			if (!this->isOut({ x + ox, y + oy }))
			{
				this->DrawPixel({ x + ox, y + oy });
			}
		}
	}
}

void ImageDraw::DrawFillRect(Point pos, Size size)
{
	for (int i = pos.x; i <= pos.x + size.width; i++)
	{
		for (int j = pos.y; j <= pos.y + size.height; j++)
		{
			if (!this->isOut({ i,j }))
			{
				this->DrawPixel({ i, j });
			}
		}
	}
}

void ImageDraw::DrawFillTriangle(Point pos, int base, int height,int place)
{
	for (int i = pos.x; i <= pos.x + base; i++)
	{
		this->DrawLine({ i,pos.y }, { pos.x + place,pos.y - height });
	}
}

bool ImageDraw::isOut(Point pos)
{
	if (pos.x >= 0 && pos.x <= this->size.width && pos.y >= 0 && pos.y <= this->size.height)
	{
		return false;
	}
	return true;
}
