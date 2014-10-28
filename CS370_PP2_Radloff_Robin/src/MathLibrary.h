/*
 * Image2D.h
 *
 *  Created on:
 *      Author: wylder
 */

#ifndef MATHLIBRARY__H
#define MATHLIBRARY__H

#include <complex>


//The real way foreach should be defined... if it would work lol
//#define forEach(it,container) \
//  for (container::iterator it = container.begin(); it != container.end(); ++it)

namespace Math
{

//Complex values
typedef double real;

//Mmm Pi....
static const real cPi = 3.141592653;

//Rollin rollin rollin..
static const real cE = 2.71828183;

//Generic linear interpolation method
template <typename DT, typename RT>
DT lerp(const DT& start, const DT& end, const RT& value)
{
  return (RT(1.0) - value) * start + value * end;
}


////DFT
//class DFTBase
//{
//public:
//  DFTBase()
//  {
//    mTransform = NULL;
//  }
//  template <typename dType>
//  std::complex<real> * operator()(dType *input, int width, int height)
//  {
//    //stuff...
//    delete [] mTransform;
//    mTransform = new std::complex<real>[width * height];
//
//    for (int n = 0; n < height; ++n)
//    {
//      for (int m = 0; m < width; ++m)
//      {
//        for (int y = 0; y < height; ++y)
//        {
//          for (int x = 0; x < width; ++x)
//          {
//            //do stuff
//            input[x + y*width]
//          }
//        }
//      }
//    }
//  }
//private:
//  std::complex<real> *mTransform;
//};

//IDFT

//FFT

//IFFT

}//namespace Math

#endif
