#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image base;
  Image sticker;
  base.readFromFile("alma.png");
  sticker.readFromFile("i.png");

  StickerSheet sheet(base,3);
  sheet.addSticker(sticker, 10, 10);
  sheet.addSticker(sticker, 500, 10);
  sheet.addSticker(sticker, 10, 500);
  Image finalimage = sheet.render();
  finalimage.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
