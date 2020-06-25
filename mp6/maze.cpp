/* Your code here! */

#include "maze.h"
#include<math.h>

using namespace std;

void SquareMaze::makeMaze(int width, int height) {
    this->width = width;
    this->height = height;
    int i = 0;
    while (i<width*height) {
      downWalls.push_back(true);
      rightWalls.push_back(true);
      i++;
    }
    DisjointSets dis;
    dis.addelements(height * width);
    int bd = 0;
    while (bd < width * height - 1) {
      int x = rand() % width;
      int y = rand() % height;
      bool r = rand() % 2;
      if (r) {
        if (x < width - 1){
          if(rightWalls[x + y * width]){
            if(dis.find(x + y * width) != dis.find(x + 1 + y * width)) {
              rightWalls[x + y* width] = false;
              dis.setunion(dis.find(x + y * width), dis.find(x + 1 + y * width));
              bd++;
          }
        }
      }
        } else {
          if (y < height - 1){
            if(downWalls[x + y * width]){
               if(dis.find(x + y * width) != dis.find(x + (y+ 1) * width)) {
                 downWalls[x + y * width] = false;
                 dis.setunion(dis.find(x+ y * width), dis.find(x + (1 + y) * width));
                 bd++;
               }
             }
           }
          }
        }
      }


    bool SquareMaze::canTravel(int x, int y, int dir) const {
          if (dir == 0){
            return !(rightWalls[x + y * width]);
          }
          if (dir == 1){
            return !(downWalls[x + y * width]);
          }
          if (dir == 2) {
            if (x != 0) {
              return !(rightWalls[x - 1 + y * width]);
            }
          }
          if (dir == 3) {
            if (y != 0) {
              return !(downWalls[x + (y - 1) * width]);
            }
          }
          return false;
        }

        void SquareMaze::setWall(int x, int y, int dir, bool exists) {

              if (dir == 0) {
                rightWalls[x + y * width] = exists;
              }else{
                downWalls[x + y * width] = exists;
              }
            }

        vector<int> SquareMaze::solveMaze() {
          vector<int> theLast;
          map<int, int> road;
          vector<bool> hasVis;
          int i = 0;
          while(i < width*height) {
            hasVis.push_back(false);
            i++;
          }
          queue<int> f;
          f.push(0);
          hasVis[0] = true;
          while(!f.empty()) {
            int value = f.front();
            f.pop();
            int x = value % width;
            int y = value / width;
            if (y == height - 1) {
              theLast.push_back(value);
            }
            if (canTravel(x, y, 0)){
              if(!hasVis[value + 1]) {
              road.insert(pair<int, int> (value + 1, value));
              hasVis[value + 1] = true;
              f.push(value + 1);
            }
          }
            if (canTravel(x, y, 1)){
              if(!hasVis[value + width]) {
              road.insert(pair<int, int> (value + width, value));
              hasVis[value + width] = true;
              f.push(value + width);
            }
          }
            if (canTravel(x, y, 2)){
              if(!hasVis[value - 1]) {
              road.insert(pair<int, int> (value - 1, value));
              hasVis[value - 1] = true;
              f.push(value - 1);
            }
          }
            if (canTravel(x, y, 3)){
              if(!hasVis[value - width]) {
              road.insert(pair<int, int> (value - width, value));
              hasVis[value - width] = true;
              f.push(value - width);
            }
          }
          }
          vector<int> output;
          int theL = width - 1;
          while(theLast[width - 1] == theLast[theL - 1]){
            theL = theL - 1;
          }
          int start = theLast[theL];
          int a = road[start];
          while (start != 0) {
            if (start == a + 1) output.push_back(0);
            if (start == a + width) output.push_back(1);
            if (start == a - 1) output.push_back(2);
            if (start == a - width) output.push_back(3);
            start = a;
            a = road[start];
          }
          reverse(output.begin(),output.end());
          return output;
        }


    PNG * SquareMaze::drawMaze() const {
        int Iwidth = width * 10 + 1;
        int Iheight = height * 10 + 1;
        PNG * out = new PNG(Iwidth, Iheight);
        HSLAPixel origin = HSLAPixel(0, 0, 0);
        for (int i = 10; i < Iwidth; i++) {
            out->getPixel(i, 0) = origin;
        }
        for (int i = 0; i < Iheight; i++) {
            out->getPixel(0, i) = origin;
        }
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                //Draw right wall if exists.
                if (rightWalls[x + y * width]) {
                    for (int i = 0; i < 11; i++) {
                        out->getPixel(10 * (x + 1), 10 * y + i) = origin;
                    }
                }
                //Draw down wall if exists.
                if (downWalls[x + y * width]) {
                    for (int i = 0; i < 11; i++) {
                        out->getPixel(10 * x + i, 10 * (y + 1)) = origin;
                    }
                }
            }
        }
        return out;
      }

        PNG * SquareMaze::drawMazeWithSolution() {
            PNG* out= drawMaze();
            vector<int> dirs = solveMaze();
            int x = 5;
            int y = 5;
            unsigned i = 0;
            HSLAPixel color = HSLAPixel(0, 1, 0.5);
            while(i < dirs.size()){
              if (dirs[i] == 0) {
                for (int i = 0; i < 10; i++) {
                  out->getPixel(x,y) = color;
                  x++;
                }
              }
              if (dirs[i] == 1) {
                for (int i = 0; i < 10; i++) {
                  out->getPixel(x,y) = color;
                  y++;
                }
              }
              if (dirs[i] == 2) {
                for (int i = 0; i < 10; i++) {
                  out->getPixel(x,y) = color;
                  x--;
                }
              }
               if (dirs[i] == 3) {
                for (int i = 0; i < 10; i++) {
                  out->getPixel(x,y) = color;
                  y--;
                }
              }
              i++;
            }
            HSLAPixel* pixel = new HSLAPixel();
            out->getPixel(x,y) = color;

            x -= 4;
            y += 5;
            for (int i = 0; i < 9; i++) {
              out->getPixel(x, y) = HSLAPixel();
              x++;
          }
            return out;
          }

    PNG* SquareMaze::drawCreativeMaze() {

      PNG* mymaze = drawMazeWithSolution();
      double xcoor = width * 5;
      double ycoor = height * 5;
      double radius;
      if(xcoor < ycoor){
        radius = pow(xcoor, 2);
      }else{
        radius = pow(ycoor, 2);
      }
      for (unsigned x = 0; x < mymaze->width(); x++) {
        for (unsigned y = 0; y < mymaze->height(); y++) {
          double dis = pow(x - xcoor, 2) + pow(y - ycoor, 2);
          HSLAPixel& pixel = mymaze->getPixel(x, y);
          if (dis > radius) {
            pixel = HSLAPixel(0, 0.8, 0.5);
          }else if (dis > 0.9* radius && dis < radius){
            pixel = HSLAPixel(100, 0.7, 0.5);
          }else if (dis > 0.8* radius && dis < 0.9*radius){
            pixel = HSLAPixel(200, 0.5, 0.5);
          }
        }
      }

      return mymaze;
    }
