#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG inputPNG;
  if(inputPNG.readFromFile(inputFile)){
  // PNG *outputPNG = new PNG(inputPNG.width(),inputPNG.height());
  PNG outputPNG(inputPNG.width(),inputPNG.height());
    for(unsigned int x = 0; x < inputPNG.width(); x++){
      for(unsigned int y = 0; y < inputPNG.height(); y++){
        outputPNG.getPixel(x,y) = inputPNG.getPixel(inputPNG.width()-1-x,inputPNG.height()-1-y);
      }
    }
    outputPNG.writeToFile(outputFile);
  }
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      HSLAPixel &pixel = png.getPixel(x,y);
      pixel.h = (100 * y / height);
      pixel.s = 1;
      pixel.l = 0.5;
      pixel.a = 1;
    }
  }
  return png;
}
