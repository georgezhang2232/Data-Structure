#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
    for(auto it:vertexMap)it.second["1"] = "infinite";
    std::queue<V> heap;
    V & start_ = vertexMap.at(start);
    heap.push(start_);
    while(!heap.empty()){
      V & temp = heap.front();
      heap.pop();
      for(auto it:incidentEdges(temp.key())){
        if(it.get().source() == temp){
          V & v = vertexMap.at(it.get().dest().key());
        if(v["1"] == "infinite"){
          v["1"] = "real";
          v["2"] = it.get().source().key();
          heap.push(v);
        }
        }else if(it.get().dest() == temp){
          V & v = vertexMap.at(it.get().source().key());
        if(v["1"] == "infinite"){
          v["1"] = "real";
          v["2"] = it.get().dest().key();
          heap.push(v);
        }
        }
      }
    }
    vertexMap.at(start)["2"] = "null";
    string back = end;
    while(back != "null"){
      path.push_back(back);
      V & v = vertexMap.at(back);
      back = v["2"];
    }
    std::reverse(path.begin(),path.end());
    return path;
}
