#ifndef _PIXMAP_H_
#define _PIXMAP_H_

#include <string>
using namespace std;


//////////////////////////////////////////////////////////////
// Pixmap type - contains height, width, and grey scale data
//
struct Pixmap
{
  unsigned long sizeX;
  unsigned long sizeY;
  unsigned char **data;

  Pixmap (const string& filename);

  short getPixel (unsigned long x, unsigned long y) const;

};


#endif
