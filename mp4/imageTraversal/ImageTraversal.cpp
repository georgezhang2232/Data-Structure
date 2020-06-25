#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(PNG image, Point start, double tolerance, ImageTraversal *ittraversal){
  traversal = ittraversal;
  itimage = image;
  itstart = start;
  realstart = itstart;
  ittorlenrance = tolerance;

  for (unsigned i = 0; i < itimage.width() * itimage.height(); i++) {
   visited_.push_back(false);
 }

 if (canVisit(itstart)) {
    visited_[itstart.x + itstart.y * itimage.width()] = true;
  } else {
    isend = true;
  }
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point right = Point(itstart.x + 1, itstart.y);
  Point below = Point(itstart.x, itstart.y + 1);
  Point left = Point(itstart.x-1, itstart.y);
  Point above = Point(itstart.x, itstart.y - 1);

  if (canVisit(right)) traversal->add(right);
  if (canVisit(below)) traversal->add(below);
  if (canVisit(left)) traversal->add(left);
  if (canVisit(above)) traversal->add(above);


    Point next = traversal->peek();
    while (visited_[next.x + next.y * itimage.width()]) {
    if (traversal->empty()) {
      isend = true;
      return *this;
    }
    next = traversal->pop();
  }
  itstart = next;
  visited_[itstart.x + itstart.y * itimage.width()] = true;
  return *this;

}

bool ImageTraversal::Iterator::canVisit(Point point) {
  //out of bound
  if (point.x >= itimage.width() || point.y >= itimage.height())
  return false;
  //out of tolerance
  HSLAPixel start = itimage.getPixel(realstart.x, realstart.y);
  HSLAPixel temp = itimage.getPixel(point.x, point.y);
  if (calculateDelta(start, temp) >= ittorlenrance)
  return false;
  // everything is ok :)
  return true;
}
/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return itstart;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return isend != other.isend;
}
