
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;
  png.readFromFile("tests/pacman.png");
  FloodFilledImage image(png);

  DFS dfs(png, Point(0, 0), 0.03);
  RainbowColorPicker rainbow(0.5);
  image.addFloodFill( dfs, rainbow );

  DFS dfs2(png, Point(150, 0), 0.03);
  RainbowColorPicker rainbow2(0.5);
  image.addFloodFill( dfs2, rainbow2 );


  BFS bfs(png, Point(10, 150), 0.03);
  MyColorPicker myColor;
  image.addFloodFill( dfs, myColor );

  BFS bfs2(png, Point(150, 20), 0.03);
  MyColorPicker myColor2;
  image.addFloodFill( dfs, myColor2 );

  Animation animation = image.animate(20000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
