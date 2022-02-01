#ifndef NODELIST_HPP
#define NODELIST_HPP

#include "node.hpp"

// serialization includes
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/vector.hpp>
//#include <boost/serialization/map.hpp>

#define EXCEPTION_LENGTH        80
#define MEMORY_ALLOC_GROWTH     1.5

// NodeList: this class allow us to use a list of nodes wich have the same
//    order. It is used to manage the layers of our lattices. The nodes are
//    are sorted by their Ids (signets).
class NodeList
{
private:
//friend class boost::serialization::access;
//    template<class Archieve>
//void serialize(Archieve & ar, const unsigned int version)
//{
//  ar& list;
//}

public:
// --- Attributes --------------------------------------------------------------
  map<string, Node> list;

// --- Constructor  ------------------------------------------------------------
  NodeList();
  size_t getSize();

// --- List management  --------------------------------------------------------
  // insertNode: inserts the node in the list.
  void insertNode(Node node);
  // getNode: if there is a node corresponding to Id, returns it.
  //    Else, returns NULL.
  Node* getNode(const string& id);
  // eraseNode: erases the node at index k.
  void eraseNode(const string& id);


// --- Tools -------------------------------------------------------------------
  void generateConcept();
  void linkAll();
  void linkToAncestors(string id);
  void linkToParents(string id);
  void insertExtent(vector<int>* vec, bool b);
  string toString();

};
#endif

