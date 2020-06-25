/* Your code here! */
#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num){
  for(int i = 0; i < num; i++)
	{
		sets.push_back(-1);
	}
}


int DisjointSets::find(int elem){
  if(sets[elem] < 0) return elem;
	return find(sets[elem]);
}


void DisjointSets::setunion(int a, int b){
  int root1 = find(a);
	int root2 = find(b);
	if(root1 == root2) return;
	int newSize = sets[root1] + sets[root2];
	if(sets[root1] <= sets[root2])//meaning root1 is more negative, root1 is bigger
	{
		sets[root2] = root1;
		sets[root1] = newSize;
	}
	else
	{
		sets[root1] = root2;
		sets[root2] = newSize;
	}
}


int DisjointSets::size(int elem){
  if (elem < (int)sets.size()) return abs(sets[find(elem)]);
  return -1;
}
