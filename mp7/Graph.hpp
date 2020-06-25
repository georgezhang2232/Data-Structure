#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include <list>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  string key = v.key();
  return adjList.at(key).size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
    V & v = *(new V(key));
    std::list<edgeListIter> insertlist;
    vertexMap.insert({key, v});
    adjList.insert({key, insertlist});
    return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  // for(unsigned i = 0; i < adjList.at(key).size(); i++){
  //   adjList[key].erase(adjList.at(key).begin());
  // }
  std::list<edgeListIter> adjEdge = adjList.at(key);
  for(auto it = adjEdge.begin(); it != adjEdge.end(); ++it){
    removeEdge(*it);
  }
  vertexMap.erase(key);

}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  string key1 = v1.key();
  string key2 = v2.key();
  adjList.at(key1).push_back(edgeList.begin());
  adjList.at(key2).push_back(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
 //  for(auto it : adjList.at(key1)){
 //    if(it->get().dest().key() == key2){
 //      adjList.at(key1).erase(it);
 //      break;
 //    }
 //  }
 //
 //  for(auto it : adjList.at(key2)){
 //    if(it->get().source().key() == key1){
 //      adjList.at(key2).erase(it);
 //      break;
 //        }
 //     }
 //
 // for(auto it : edgeList){
 //   if(it->get().source().key() == key1 && it->get().dest().key() == key2){
 //     edgeList.erase(it);
 //      }
 //  }
 for(auto it = adjList.at(key1).begin(); it!=adjList.at(key1).end(); ++it){
   if((it)->get().dest().key() == key2){
     adjList.at(key1).erase(it);
     break;
   }
 }
for(auto it = adjList.at(key2).begin(); it!=adjList.at(key2).end(); ++it){
             if((*it)->get().source().key() == key1){
               adjList.at(key2).erase(it);
               break;
             }
       }
 for(auto it = edgeList.begin(); it!=edgeList.end(); ++it){
       if(it->get().source().key() == key1 && (*it).get().dest().key() == key2){
         edgeList.erase(it);
       }
     }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  string sourcekey = it->get().source().key();
  string destkey = it->get().dest().key();
  removeEdge(sourcekey, destkey);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<edgeListIter> itList = adjList.at(key);
  std::list<std::reference_wrapper<E>> edges;
    for(auto it : itList){
      edges.push_back(*it);
    }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  if(adjList.at(key1).size() == 0) return false;
  if(adjList.at(key2).size() == 0) return false;

  if(adjList.at(key1).size() < adjList.at(key2).size()){
    for(auto it1 : adjList.at(key1)){
          if(it1->get().source().key() == key1 && it1->get().dest().key() == key2){
            return true;
          }
        }
  }

  if(adjList.at(key1).size() >= adjList.at(key2).size()){
    for(auto it2 : adjList.at(key2)){
      if(it2->get().source().key() == key1 && it2->get().dest().key() == key2){
        return true;
      }
  }
}
  return false;
}
