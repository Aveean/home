/*
 * Image2D.h
 *
 *  Created on: १ जून २०११
 *      Author: pushpak
 */

#ifndef IMAGE2D_H_
#define IMAGE2D_H_

#include "wx/wx.h"
#include <map>
#include <string>

typedef unsigned char uchar;
typedef unsigned int  uint;

class Image2D;

enum ScaleTypes
{
  NearestNeighbor,
  Bilinear
};

//ImageId's are used to reference images from the image library
struct ImageId
{
  enum { InvalidId = -1 };

  ImageId() : mId(InvalidId) {}
  operator Image2D * ();

  uint mId;
  std::string mName;
};

class Image2D {
public:
	enum readStates
	{
		READ_HEADER,
		READ_ROWS,
		READ_COLS,
		READ_MAX,
		READ_ELEMENTS,
		READ_INVALID
	};
	// static methods to read & write the image
  static Image2D * newImage( const char *name = 0 );
  static Image2D * eraseImage( const ImageId &id );
  static Image2D * findImage( const ImageId &id );
	static Image2D * readImage( const wxString &filename, const wxString &name );
	static bool      writeImage( const wxString &filename, Image2D &image );

  static std::map<uint, Image2D *> * getImageLibrary();


	Image2D();
  Image2D(int width, int height, uchar *data = 0, int depth = 3, int max = UCHAR_MAX);
	virtual ~Image2D();

	uchar GetData(int x, int y, int d);
	void SetData(int x, int y, int d, uchar data);

  uchar * GetData();
  uchar   GetMax();

	uint GetHeight();
	uint GetWidth();
  uint GetDepth();

  ImageId GetId() { return mImageId; }

  bool IsValid() { return mValid; }

  void SetData(uchar *data);
  void SetDepth(int depth);
	void SetSize(int width, int height);
  void ScaleTo(int width, int height, int scaleType);

	void CopyFrom(Image2D *image);

private:
  void BuildFrom(uchar *data, int width, int height, int depth);
  int  GetIndex(int x, int y, int d) const;

  //Image Id
  ImageId mImageId;
  // the image data
  uchar *mData;
  // image dimensions
  int mWidth, mHeight, mDepth;

  //Max color value
  int mMaxVal;
  
  bool mValid;

  //Id generator
  static uint NewId();

  //ImageId base
  static uint sIdBase;

  //Used for loading files
  static wxImage sImage;

  //A library of all the images loaded and processed
  static std::map<uint, Image2D *> sImageLibrary;
};

#endif /* IMAGE2D_H_ */
