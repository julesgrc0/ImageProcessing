#pragma once
#include <iostream>
#include <filesystem>
#include "ImagesProperties.h"

class ImageGeneration
{
public:
	/**
	Setup the filename and the size of your image. Don't name your file with an extension
	y default it's PNG but when you create your image you can change the extension.
	@param filename std::string
	@param Size size
	*/
	ImageGeneration(std::string filename, Size size);
	/**
	Free image matrix
	*/
	~ImageGeneration();

	/**
	Change the image size. Warning it will clear all the pixel with the default color.
	@param Size size
	@return bool
	*/
	bool setImageBounds(Size size);
	/***
	Return the actual size of your image
	@return Size
	*/
	Size getImageBounds();

	/***
	Set a new name to your file (don't write the extension)
	@return bool
	*/
	bool setFilename(std::string name);
	/**
	Return the name of your output file
	@return std::string
	*/
	std::string getFilename();

	/**
	Set the default background color.
	@param color Rgb
	@return void
	*/
	void setDefaultBackground(Rgb color);
	/**
	Return the actual background color
	@return Rgb
	*/
	Rgb getDefaultBackground();

	/**
	Set a custom image pixel.
	@param matrix char*
	@return bool
	*/
	bool setImageMatrix(char *ImageMatrix);
	/**
	Return the actual image pixel matrix
	@return char*
	*/
	char *getImageMatrix();

	/**
	Set a pixel on image matrix.
	@param position Point
	@return bool
	*/
	void setPixel(Point position);
	/**
	Set a new color
	@param color Rgb
	@return void
	*/
	void setColor(Rgb color);
	/**
	Return the actual color
	@return Rgb
	*/
	Rgb getColor();
	/**
	Build your image with the actual matrix.
	@param ImageTypes type = PNG)
	@return bool (true if success)
	*/
	bool createImage(ImageTypes type = PNG);
	/**
	Set a new location to your image
	@param path std::filesystem::path
	@return bool
	*/
	bool setOutputPath(std::filesystem::path path);
	/**
	Return the actual location for the ouput image
	@return std::filesystem::path
	*/
	std::filesystem::path getOutputPath();

private:
	void updateImageMatrix();
	unsigned char *createFileHeader(int stride);
	unsigned char *createInfoHeader();

	Rgb color = {0, 0, 0};
	char *ImageMatrix;
	const int BytesPerPixel = 3;
	const int FileHeaderSize = 14;
	const int InfoHeaderSize = 40;
	Size ImageSize;
	std::string filename;
	std::filesystem::path output;
};
