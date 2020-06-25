#include "StickerSheet.h"
#include "Image.h"
#include <cmath>
using namespace cs225;
using namespace std;

//Initializes this StickerSheet with a base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. More...
StickerSheet::StickerSheet (const Image &picture, unsigned max){
  maxStickers = max;
  base = picture;
  StickerList = new Image *[max];
  Ycoordinate = new int [max];
  Xcoordinate = new int [max];
  for(unsigned i = 0; i < max; i++){
    StickerList[i] = NULL;
  }
}

//Frees all space that was dynamically allocated by this StickerSheet. More...
StickerSheet::~StickerSheet (){
  _destory();
}

//The copy constructor makes this StickerSheet an independent copy of the source. More...
StickerSheet::StickerSheet (const StickerSheet &other){
  _copy(other);
}

//The assignment operator for the StickerSheet class. More...
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
  if(this!= &other){
    _destory();
    _copy(other);
  }
  return *this;
}

//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. More...
void 	StickerSheet::changeMaxStickers (unsigned max){
  Image** copylist = new Image*[maxStickers];
  int* copyx =  new int[maxStickers];
  int* copyy =  new int[maxStickers];
    for(unsigned x = 0; x < maxStickers; x++){
        copylist[x] = StickerList[x];
        copyx[x] = Xcoordinate[x];
        copyy[x] = Ycoordinate[x];
      }
  _destory();
  StickerList = new Image* [max];
  for(unsigned i = 0; i < max; i++){
    StickerList[i] = NULL;
  }
  Ycoordinate = new int[max];
  Xcoordinate = new int[max];
    for(unsigned int x = 0; x < min(maxStickers,max); x++){
        StickerList[x] = copylist[x];
        Xcoordinate[x] = copyx[x];
        Ycoordinate[x] = copyy[x];
      }
  delete []copylist;
  delete []copyx;
  delete []copyy;
  maxStickers = max;
}

//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. More...
int 	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  for(unsigned i = 0; i < maxStickers; i++){
    if (StickerList[i] == NULL){
      StickerList[i] = &sticker;
      Xcoordinate[i] = x;
      Ycoordinate[i] = y;
      return i;
    }
  }
  return -1;
}

//Changes the x and y coordinates of the Image in the specified layer. More...
bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if(index < maxStickers && StickerList[index] != NULL){
    Xcoordinate[index] = x;
    Ycoordinate[index] = y;
    return true;
  }
  return false;
}

//Removes the sticker at the given zero-based layer index. More...
void 	StickerSheet::removeSticker (unsigned index){
    StickerList[index] = NULL;
    Xcoordinate[index] = 0;
    Ycoordinate[index] = 0;

}

//Returns a pointer to the sticker at the specified index, not a copy of it. More...
Image * StickerSheet::getSticker (unsigned index) const{
  if(index >= maxStickers){
    return NULL;
  }
  return StickerList[index];
}

//Renders the whole StickerSheet on one Image and returns that Image. More...
Image StickerSheet::render () const{
  Image finalpic = Image(base);
  unsigned finalwidth = base.width();
  unsigned finalheight = base.height();
  for(unsigned i = 0; i < maxStickers; i++){
    if(StickerList[i] != NULL){
    if(Xcoordinate[i]+StickerList[i]->width() > finalwidth){
      finalwidth  = Xcoordinate[i]+StickerList[i]->width();
    }
    if(Ycoordinate[i]+StickerList[i]->height() > finalheight){
      finalheight = Ycoordinate[i]+StickerList[i]->height();
    }
  }
  }
  finalpic.resize(finalwidth,finalheight);
  for(unsigned i = 0; i < maxStickers; i++){
    if(StickerList[i] != NULL){
    for(unsigned j = Xcoordinate[i]; j < Xcoordinate[i]+StickerList[i]->width(); j++){
      for(unsigned k = Ycoordinate[i]; k < Ycoordinate[i]+StickerList[i]->height(); k++){
        if(StickerList[i]->getPixel(j-Xcoordinate[i], k-Ycoordinate[i]).a != 0){
          finalpic.getPixel(j,k) = StickerList[i]->getPixel(j-Xcoordinate[i],k-Ycoordinate[i]);
        }
      }
    }
  }
}
  return finalpic;
}

void StickerSheet::_destory(){
  delete []StickerList;
  delete []Ycoordinate;
  delete []Xcoordinate;
}

void StickerSheet::_copy(const StickerSheet &other){
  base = other.base;
  maxStickers = other.maxStickers;
  StickerList = new Image* [maxStickers];
  Ycoordinate = new int [maxStickers];
  Xcoordinate = new int [maxStickers];
  for(unsigned x = 0; x < maxStickers; x++){
    StickerList[x] = other.StickerList[x];
  }
  for(unsigned x = 0; x < maxStickers; x++){
    Xcoordinate[x] = other.Xcoordinate[x];
  }
  for(unsigned x = 0; x < maxStickers; x++){
    Ycoordinate[x] = other.Ycoordinate[x];
  }
}
