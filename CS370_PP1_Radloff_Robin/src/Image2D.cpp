/*
 * Image2D.cpp
 *
 *  Created on: १ जून २०११
 *      Author: pushpak
 */

#include "Image2D.h"
#include "MathLibrary.h"

#include <iostream>
#include <fstream>
#include <math.h>


//ImageId base
uint Image2D::sIdBase = 0;

//Used for loading files
wxImage Image2D::sImage;

//A library of all the images loaded and processed
std::map<uint, Image2D *> Image2D::sImageLibrary;


/////////////////////////////////////////////////////////////////////
ImageId::operator Image2D *()
{
  return Image2D::findImage(*this);
}

/////////////////////////////////////////////////////////////////////
Image2D::Image2D()
{
	mHeight = 0;
	mWidth = 0;
	mData = NULL;
	mMaxVal = CHAR_MIN;
  mValid = false;
}

/////////////////////////////////////////////////////////////////////
Image2D::Image2D(int width, int height, uchar *data, int depth, int max)
{
  mData = NULL;
  mWidth = mHeight = mDepth = 0;
  BuildFrom(data,width,height,depth);

	mMaxVal = max;
}

/////////////////////////////////////////////////////////////////////
Image2D::~Image2D()
{
  if (mImageId.mId != ImageId::InvalidId)
    Image2D::eraseImage(mImageId);

	if( mData )
		delete [] mData;
}

/////////////////////////////////////////////////////////////////////
uchar Image2D::GetData(int x, int y, int d)
{
  //Signal-repeat sampling
  if (x < 0) x = 0;
  else if (x >= mWidth) x = mWidth-1;
  if (y < 0) y = 0;
  else if (y >= mHeight) y = mHeight-1;

  return mData[GetIndex(x,y,d)];
}

/////////////////////////////////////////////////////////////////////
void Image2D::SetData(int x, int y, int d, uchar data)
{
  mData[GetIndex(x,y,d)] = data;
}

/////////////////////////////////////////////////////////////////////
uchar *Image2D::GetData()
{
    return mData;
}

/////////////////////////////////////////////////////////////////////
uint Image2D::GetHeight()
{
    return mHeight;
}

/////////////////////////////////////////////////////////////////////
uint Image2D::GetWidth()
{
	return mWidth;
}

/////////////////////////////////////////////////////////////////////
uint Image2D::GetDepth()
{
  return mDepth;
}

/////////////////////////////////////////////////////////////////////
uchar Image2D::GetMax()
{
  return mMaxVal;
}

/////////////////////////////////////////////////////////////////////
void Image2D::SetData(uchar *data)
{
  memcpy(mData,data,mWidth*mHeight*mDepth);
}

/////////////////////////////////////////////////////////////////////
void Image2D::SetSize(int width, int height)
{
  mWidth = width;
  mHeight = height;
}

/////////////////////////////////////////////////////////////////////
void Image2D::SetDepth(int depth)
{
  mDepth = depth;
}

/////////////////////////////////////////////////////////////////////
void Image2D::ScaleTo(int newWidth, int newHeight, int scaleType)
{
  //Create a new image
  Image2D *image = new Image2D(newWidth, newHeight);
  
  //Copy data
  for (int y = 0; y < newHeight; ++y)
  {
    for (int x = 0; x < newWidth; ++x)
    {
        switch (scaleType)
        {
        case NearestNeighbor:
        {
          uint sx = float(x) / (newWidth - 1) * (mWidth - 1);
          uint sy = float(y) / (newHeight - 1) * (mHeight - 1);
          for (uint d = 0; d < image->GetDepth(); ++d)
            image->SetData(x, y, d, GetData(sx, sy, d));
          break;
        }
        case Bilinear:
        {
          // Calculate scale stuff
          float sx = float(x) / (newWidth - 1) * (mWidth - 1);
          float sy = float(y) / (newHeight - 1) * (mHeight - 1);

          // Get the neighboring pixels
          int x1 = floor(sx);
          int x2 = floor(sx + 1);
          int y1 = floor(sy);
          int y2 = floor(sy + 1);

          float alpha = (sx - x1) / (x2 - x1);
          float beta = (sy - y1) / (y2 - y1);

          // Perform linear interpolation in two directions
          for (uint d = 0; d < image->GetDepth(); ++d)
          {
            //  x1, y2               x2, y2
            //
            //  x1, y1               x2, y1

            float lowerLeft = GetData(x1, y1, d);
            float lowerRight = GetData(x2, y1, d);
            float upperLeft = GetData(x1, y2, d);
            float upperRight = GetData(x2, y2, d);

            float lower = (1 - alpha) * lowerLeft + alpha * lowerRight;
            float upper = (1 - alpha) * upperLeft + alpha * upperRight;
            float final = (1 - beta) * lower + beta * upper;

            image->SetData(x, y, d, final);
          }
          break;
        }
        };
    }
  }

  //Cleanup
  SetSize(newWidth, newHeight);
  std::swap(image->mData, mData);
  delete image;
}

/////////////////////////////////////////////////////////////////////
void Image2D::CopyFrom(Image2D *image)
{
  BuildFrom(image->GetData(),image->GetWidth(),image->GetHeight(),image->GetDepth());
}

/////////////////////////////////////////////////////////////////////
void Image2D::BuildFrom(uchar *data, int width, int height, int depth)
{
    //Make sure the mData is the correct size
    if (mHeight != height || mWidth != width || mDepth != depth)
    {
        mHeight = height;
        mWidth = width;
        mDepth = depth;

        delete [] mData;
        mData = new uchar[mHeight*mWidth*mDepth];
    }

    //Copy image mData from one image to the other
    if (data)
      SetData(data);
    
    mValid = true;
}

/////////////////////////////////////////////////////////////////////
int Image2D::GetIndex(int x, int y, int d) const
{
  //Error checking for index
  x = (x >= 0 ? (x < mWidth  ? x : mWidth  - 1) : 0);
  y = (y >= 0 ? (y < mHeight ? y : mHeight - 1) : 0);
  d = (d >= 0 ? (d < mDepth  ? d : mDepth  - 1) : 0);

  //Generate index
  return d + (x + y * mWidth) * mDepth;
}

/////////////////////////////////////////////////////////////////////
Image2D * Image2D::findImage( const ImageId &id )
{
  std::map<uint, Image2D *>::iterator it = sImageLibrary.find(id.mId);

  if(it != sImageLibrary.end())
    return it->second;

  return NULL;
}

uint Image2D::NewId()
{
  return sIdBase++;
}

/////////////////////////////////////////////////////////////////////
Image2D * Image2D::newImage( const char *name )
{
  Image2D *image = new Image2D();

  image->mImageId.mId = NewId();
  image->mImageId.mName = name;
  sImageLibrary[image->mImageId.mId] = image;

  return image;
}

/////////////////////////////////////////////////////////////////////
Image2D * Image2D::eraseImage( const ImageId &id )
{
  Image2D *image = sImageLibrary[id.mId];
  sImageLibrary.erase(id.mId);

  return image;
}

/////////////////////////////////////////////////////////////////////
bool Image2D::writeImage(const wxString & filename, Image2D & image)
{
  sImage = wxImage(image.GetWidth(),image.GetHeight(),image.GetData(),true);

  if (filename.Contains(".ppm"))
    sImage.SaveFile(filename, wxBITMAP_TYPE_PNM);
  else
    sImage.SaveFile(filename);
  //If wxWidgets is included, this should use the saving capabilities
  //of wxImage in order to allow saving of images other than just ppm
  //format. If not, then a standard text parser should be written.
    return false;
}

/////////////////////////////////////////////////////////////////////
Image2D *Image2D::readImage(const wxString &filename, const wxString &name)
{
  //If wxWidgets is included, this should use the loading capabilities
  //of wxImage in order to allow loading of images other than just ppm
  //format. If not, then a standard text parser should be written.

  Image2D *image = NULL;
  
  if (sImage.LoadFile(filename) == TRUE)
  {
    image = newImage(name.c_str());
    image->BuildFrom(sImage.GetData(),sImage.GetWidth(),sImage.GetHeight(),3);
  }

  return image;
}


std::map<uint, Image2D *> * Image2D::getImageLibrary()
{
  return &sImageLibrary;
}
