/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

       map<Point<3>, int> tileMap;
       vector<Point<3>> tileColor;
       tileColor.resize(theTiles.size());

       for (unsigned i = 0; i < theTiles.size(); i++) {
         LUVAPixel tilePixel = theTiles[i].getAverageColor();
         Point<3> LUVcolor = convertToXYZ(tilePixel);
         tileColor.push_back(LUVcolor);
         tileMap[LUVcolor] = i;
       }

       KDTree<3> tree(tileColor);
       MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

       for (int i = 0; i < theSource.getRows(); i++) {
         for (int j = 0; j < theSource.getColumns(); j++) {
           LUVAPixel sourcePixel = theSource.getRegionColor(i, j);
           Point<3> query(sourcePixel.l, sourcePixel.u, sourcePixel.v);
           canvas->setTile(i, j, & theTiles[tileMap[tree.findNearestNeighbor(query)]]);
         }
       }
       return canvas;
}
