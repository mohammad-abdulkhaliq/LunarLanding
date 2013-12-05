#include <stdio.h>      // Header file for standard file i/o.
#include <iostream>
#include <stdlib.h>     // Header file for malloc/free.
#include <ctype.h>
#include "pixmap.h"


static unsigned char getnum (FILE *fp)
{
  char buf[4];
  char c = getc(fp);
  int i=0;

  while(!isdigit(c) && !feof(fp)) c=getc(fp);
  while(isdigit(c) && !feof(fp))
  {
    buf[i]=c;
    i++;
    c=getc(fp);
  }

  buf[i]='\0';  
  return ( (i!= 0) ?  (unsigned char) atoi(buf) : 0 );
}


static long getdim (FILE *fp)
{
  int i=0;
  char buf[20];
  char c;

  c=getc(fp);
  while(!isdigit(c) && !feof(fp)) c=getc(fp);
  while(isdigit(c) && !feof(fp)){
    buf[i]=c;
    i++;
    c=getc(fp);
  }

  buf[i]='\0';  
  return ( (i!= 0) ?  (long) atol(buf) : 0 );
}


Pixmap::Pixmap (const string & filename)
{
    FILE *fp = fopen(filename.c_str(), "rb");

    if (fp == NULL) 
    {
        printf("File Not Found : %s\n", filename.c_str());
	exit(0);
    }
    else
    {
        printf("Opened %s\n", filename.c_str());
    }

    char buf[80];
    char c = getc(fp);
    while (!isdigit(c))
    {
        fgets(buf, 80, fp);
        c = getc(fp);
    }
    ungetc(c, fp);

    sizeX = getdim(fp);
    sizeY = getdim(fp);
    getdim(fp);
    data = new unsigned char*[sizeX];
    for (unsigned long i = 0; i < sizeX; i++)
    {
        data[i] = new unsigned char[sizeY];  
    }
  
    for(unsigned long j = 1; j <= sizeY; j++)
    {
        for(unsigned long i = 0; i < sizeX; i++)
	{
	    data[i][sizeY - j] = getnum(fp);
	}
    }
}


short Pixmap::getPixel (unsigned long x, unsigned long y) const
{
    return data[x % sizeX][y % sizeY];
}
