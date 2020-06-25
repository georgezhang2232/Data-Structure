#include "Image.h"

namespace cs225{

void Image::lighten(){

  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).l += 0.1;
      if(this->getPixel(x,y).l > 1){
        this->getPixel(x,y).l = 1;
      }
    }
  }
}

void Image::lighten (double amount){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).l -= amount;
      if(this->getPixel(x,y).l > 1){
        this->getPixel(x,y).l = 1;
      }
    }
  }
}

void Image::darken (){
for(unsigned int x = 0; x < width(); x++ ){
  for(unsigned int y = 0; y< height(); y++){
    this->getPixel(x,y).l -= 0.1;
    if(this->getPixel(x,y).l < 0){
      this->getPixel(x,y).l = 0;
    }
  }
}
}

void Image::darken (double amount){
for(unsigned int x = 0; x < width(); x++ ){
  for(unsigned int y = 0; y< height(); y++){
    this->getPixel(x,y).l -= amount;
    if(this->getPixel(x,y).l < 0){
      this->getPixel(x,y).l = 0;
    }
  }
}
}

void Image::saturate (){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).s += 0.1;
      if(this->getPixel(x,y).s > 1){
        this->getPixel(x,y).s = 1;
      }
    }
  }
}

void Image::saturate (double amount){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).s += amount;
      if(this->getPixel(x,y).s > 1){
        this->getPixel(x,y).s = 1;
      }
    }
  }
}

void Image::desaturate (){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).s -= 0.1;
      if(this->getPixel(x,y).s < 0){
        this->getPixel(x,y).s = 0;
      }
    }
  }
}

void Image::desaturate (double amount){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).s -= amount;
      if(this->getPixel(x,y).s < 0){
        this->getPixel(x,y).s = 0;
      }
    }
  }
}

void Image::grayscale (){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).s = 0;
    }
  }
}

void Image::rotateColor (double degrees){
  for(unsigned int x = 0; x < width(); x++ ){
    for(unsigned int y = 0; y< height(); y++){
      this->getPixel(x,y).h += degrees;
      while (this->getPixel(x,y).h > 360){
        this->getPixel(x,y).h -= 360;
      }
      while (this->getPixel(x,y).h < 0){
        this->getPixel(x,y).h += 360;
      }
      }
    }
  }



void Image::illinify (){
  for(unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if (pixel.h >= 113.5 && pixel.h <= 293.5){
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }
    }
  }
}
void Image::scale (double factor){
  PNG *copyimage = new PNG(*this);
  unsigned int newWidth = this->width()*factor;
  unsigned int newHeight = this->height()*factor;
  this->resize(newWidth, newHeight);
  for(unsigned x = 0; x < newWidth; x++){
    for(unsigned y = 0; y < newHeight; y++){
      this->getPixel(x,y) = copyimage->getPixel((x/factor),(y/factor));
    }
  }
}
void Image::scale (unsigned w, unsigned h){
    PNG *copyimage = new PNG(*this);
  double widthfactor = w / width();
  double heightfactor = h / height();
  this->resize(w,h);
  for(unsigned x = 0; x < w; x++){
    for(unsigned y = 0; y < h; y++){
      this->getPixel(x,y) = copyimage->getPixel((x/widthfactor),(y/heightfactor));
    }
  }
}
}
