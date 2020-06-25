/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim] < second[curDim])
     return true;
     if(first[curDim] > second[curDim])
     return false;
     return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currdistance = 0;
     double possdistance = 0;
     for(int i = 0; i < Dim; i++){
       currdistance += pow(target[i] - currentBest[i], 2);
       possdistance += pow(target[i] - potential[i], 2);
     }
     if(currdistance > possdistance) return true;
     if(currdistance < possdistance) return false;
     return potential < currentBest;
}


template <int Dim>
void KDTree<Dim>::quickSort(vector<Point<Dim>>& newPoints, int start, int end, int Dimcount) {
  if(Dimcount > Dim) Dimcount = Dimcount % Dim;
  if(Dimcount == Dim) Dimcount = 0;
  if (start >= end) return;

  int median = partition(newPoints, start, end, Dimcount);
  quickSort(newPoints, start, median - 1, Dimcount );
  quickSort(newPoints, median + 1, end, Dimcount );
}


template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int start, int end, int Dimcount) {
  int median = (start + end)/2;
  if(start > end) return start;
  Point<Dim> midValue = newPoints[median];
  swap(newPoints[median], newPoints[end]);

  int curr = start;
  for(int i = start; i < end; i++){
    if(smallerDimVal(newPoints[i], midValue, Dimcount)){
      swap(newPoints[curr], newPoints[i]);
      curr++;
    }
  }
  swap(newPoints[end], newPoints[curr]);
  return curr;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<Dim>> copyPoints = newPoints;
     size = newPoints.size();
     root = KDTreehelper(copyPoints, 0, copyPoints.size() - 1, 0);

}
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTreehelper(vector<Point<Dim>>& newPoints, int start, int end, int Dimcount){
  if(Dimcount > Dim) Dimcount = Dimcount % Dim;
  if(Dimcount == Dim) Dimcount = 0;
  if (start > end) return NULL;
  if (start == end) return new KDTreeNode(newPoints[start]);
  quickSort(newPoints, start, end, Dimcount);
  int median = (start + end)/2;
  KDTreeNode* subRoot = new KDTreeNode(newPoints[median]);
  subRoot->left = KDTreehelper(newPoints, start, median - 1, Dimcount + 1);
  subRoot->right = KDTreehelper(newPoints, median + 1, end, Dimcount + 1);
  return subRoot;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(other.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* subRoot) {
  if (!subRoot) return NULL;
  return new KDTreeNode(subRoot->point);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
     destory(root);
     copy(rhs.root);
  }
  return *this;
}

template <int Dim>
void KDTree<Dim>::destory(KDTreeNode* subroot) {
  if (subroot == NULL) return;
  destory(subroot->left);
  destory(subroot->right);
  delete subroot;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destory(root);
   root = NULL;
   size = 0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* subRoot, int Dimcount) const {
  if (Dimcount >= Dim) Dimcount -= Dim;
  Point<Dim> currBest = subRoot->point;
  double radius = 0;

  if (smallerDimVal(query, subRoot->point, Dimcount)) {
    if (subRoot->left) currBest = findNearestNeighbor(query, subRoot->left, Dimcount + 1);
    else return subRoot->point;

    if (shouldReplace(query, currBest, subRoot->point))
    currBest = subRoot->point;

    for (int i = 0; i < Dim; i++) {
      radius += pow(query[i] - currBest[i], 2);
    }

    radius = sqrt(radius);
    if (radius >= abs(query[Dimcount] - subRoot->point[Dimcount])) {
      if (subRoot->right) {
        Point<Dim> newcurrBest = findNearestNeighbor(query, subRoot->right, Dimcount + 1);
       if (shouldReplace(query, currBest, newcurrBest))
       currBest = newcurrBest;
    }
  }
}

  if (!smallerDimVal(query, subRoot->point, Dimcount)){
  if (subRoot->right) currBest = findNearestNeighbor(query, subRoot->right, Dimcount + 1);
    else return subRoot->point;

    if (shouldReplace(query, currBest, subRoot->point))
    currBest = subRoot->point;

    for (int i = 0; i < Dim; i++) {
      radius += pow(query[i] - currBest[i], 2);
    }

    radius = sqrt(radius);
    if (radius >= abs(query[Dimcount] - subRoot->point[Dimcount])) {
      if (subRoot->left) {
        Point<Dim> newcurrBest = findNearestNeighbor(query, subRoot->left, Dimcount + 1);
      if (shouldReplace(query, currBest, newcurrBest))
      currBest = newcurrBest;
    }
  }
}
return currBest;
}
