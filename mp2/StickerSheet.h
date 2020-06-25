/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once
 #include "Image.h"
 #include <iostream>
 using namespace cs225;
 using namespace std;

class StickerSheet {
public:
  StickerSheet (const Image &picture, unsigned max);
  ~StickerSheet ();
  StickerSheet (const StickerSheet &other);
  const StickerSheet & 	operator= (const StickerSheet &other);
  void changeMaxStickers (unsigned max);
  int addSticker (Image &sticker, unsigned x, unsigned y);
  bool translate (unsigned index, unsigned x, unsigned y);
  void removeSticker (unsigned index);
  Image * getSticker (unsigned index) const;
  Image render () const;
  void _destory();
  void _copy(const StickerSheet &other);
private:
  unsigned int maxStickers;
  Image base;
  int *Xcoordinate;
  int *Ycoordinate;
  Image ** StickerList;
};
