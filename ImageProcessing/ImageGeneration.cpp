#define _CRT_SECURE_NO_DEPRECATE
#include "ImageGeneration.h"
#include <memory.h>
#include <stdlib.h>

ImageGeneration::ImageGeneration(std::string filename, Size size)
{
    if (size.height > 0 && size.width > 0)
    {
        this->ImageSize = size;

        /*
        Bug on image when the image is not a square ...
        */
        this->ImageSize.height = size.width;
        /**/
    }
    else
    {
        this->ImageSize = {100, 100};
    }
    this->filename = filename;

    this->ImageMatrix = new char[this->ImageSize.width * this->ImageSize.height * this->BytesPerPixel];
    for (int i = 0; i < this->ImageSize.width; i++)
    {
        for (int j = 0; j < this->ImageSize.height; j++)
        {
            *(this->ImageMatrix + i * this->ImageSize.height * this->BytesPerPixel + j * this->BytesPerPixel + 2) = this->color.r;
            *(this->ImageMatrix + i * this->ImageSize.height * this->BytesPerPixel + j * this->BytesPerPixel + 1) = this->color.g;
            *(this->ImageMatrix + i * this->ImageSize.height * this->BytesPerPixel + j * this->BytesPerPixel + 0) = this->color.b;
        }
    }
}

ImageGeneration::~ImageGeneration()
{
    delete[] this->ImageMatrix;
}

void ImageGeneration::setPixel(Point pos)
{
    *(this->ImageMatrix + pos.x * this->ImageSize.height * this->BytesPerPixel + pos.y * this->BytesPerPixel + 2) = this->color.r;
    *(this->ImageMatrix + pos.x * this->ImageSize.height * this->BytesPerPixel + pos.y * this->BytesPerPixel + 1) = this->color.g;
    *(this->ImageMatrix + pos.x * this->ImageSize.height * this->BytesPerPixel + pos.y * this->BytesPerPixel + 0) = this->color.b;
}

void ImageGeneration::setColor(Rgb color)
{
    this->color = color;
}

Rgb ImageGeneration::getColor()
{
    return this->color;
}

void ImageGeneration::updateImageMatrix()
{
    this->ImageMatrix = new char[this->ImageSize.width * this->ImageSize.height * this->BytesPerPixel];
    for (int i = 0; i < this->ImageSize.width; i++)
    {
        for (int j = 0; j < this->ImageSize.height; j++)
        {
            *(this->ImageMatrix + i * this->ImageSize.height * this->BytesPerPixel + j * this->BytesPerPixel + 2) = this->color.r;
            *(this->ImageMatrix + i * this->ImageSize.height * this->BytesPerPixel + j * this->BytesPerPixel + 1) = this->color.g;
            *(this->ImageMatrix + i * this->ImageSize.height * this->BytesPerPixel + j * this->BytesPerPixel + 0) = this->color.b;
        }
    }
}

bool ImageGeneration::setFilename(std::string name)
{
    if (name.size() > 0)
    {
        this->filename = name;
        return true;
    }
    return false;
}

std::string ImageGeneration::getFilename()
{
    return this->filename;
}

void ImageGeneration::setDefaultBackground(Rgb color)
{
    this->color = color;
    this->updateImageMatrix();
}

Rgb ImageGeneration::getDefaultBackground()
{
    return this->color;
}

bool ImageGeneration::createImage(ImageTypes type)
{

    int widthInBytes = this->ImageSize.width * this->BytesPerPixel;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;
    std::string filen = this->filename;
    switch (type)
    {
    case PNG:
        filen += ".png";
        break;
    case JPEG:
        filen += ".jpeg";
        break;
    case PPM:
        filen += ".ppm";
        break;
    case BPM:
        filen += ".bmp";
        break;
    }

    std::filesystem::path out = this->output += filen;
    std::string p = out.string();

    FILE *imageFile = fopen(p.c_str(), "wb");

    unsigned char *fileHeader = this->createFileHeader(stride);
    fwrite(fileHeader, 1, this->FileHeaderSize, imageFile);

    unsigned char *infoHeader = this->createInfoHeader();
    fwrite(infoHeader, 1, this->InfoHeaderSize, imageFile);

    for (int i = 0; i < this->ImageSize.height; i++)
    {
        fwrite(((unsigned char *)this->ImageMatrix) + (i * widthInBytes), this->BytesPerPixel, this->ImageSize.width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }
    fclose(imageFile);
    return 0;
}

bool ImageGeneration::setImageMatrix(char *matrix)
{
    if (sizeof(matrix) == sizeof(this->ImageMatrix))
    {
        this->ImageMatrix = matrix;
    }
    else
    {
        return false;
    }
}

char *ImageGeneration::getImageMatrix()
{
    return this->ImageMatrix;
}

unsigned char *ImageGeneration::createInfoHeader()
{
    static unsigned char infoHeader[] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };

    infoHeader[0] = (unsigned char)(this->InfoHeaderSize);
    infoHeader[4] = (unsigned char)(this->ImageSize.width);
    infoHeader[5] = (unsigned char)(this->ImageSize.width >> 8);
    infoHeader[6] = (unsigned char)(this->ImageSize.width >> 16);
    infoHeader[7] = (unsigned char)(this->ImageSize.width >> 24);
    infoHeader[8] = (unsigned char)(this->ImageSize.height);
    infoHeader[9] = (unsigned char)(this->ImageSize.height >> 8);
    infoHeader[10] = (unsigned char)(this->ImageSize.height >> 16);
    infoHeader[11] = (unsigned char)(this->ImageSize.height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(this->BytesPerPixel * 8);

    return infoHeader;
}

unsigned char *ImageGeneration::createFileHeader(int stride)
{
    int fileSize = this->FileHeaderSize + this->InfoHeaderSize + (stride * this->ImageSize.height);
    static unsigned char fileHeader[] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(this->FileHeaderSize + this->InfoHeaderSize);

    return fileHeader;
}

Size ImageGeneration::getImageBounds()
{
    return this->ImageSize;
}

bool ImageGeneration::setImageBounds(Size size)
{
    if (size.height > 0 && size.width > 0)
    {
        this->ImageSize = size;

        /*
        Bug on image when the image is not a square ...
        */
        this->ImageSize.height = size.width;
        /**/

        this->updateImageMatrix();
        return true;
    }
    else
    {
        return false;
    }
}

bool ImageGeneration::setOutputPath(std::filesystem::path path)
{
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        this->output = path;
        return true;
    }
    return false;
}

std::filesystem::path ImageGeneration::getOutputPath()
{
    return this->output;
}
