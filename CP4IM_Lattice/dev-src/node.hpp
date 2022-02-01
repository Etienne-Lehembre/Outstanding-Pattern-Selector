#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <set>

#include "emptynode.hpp"
#include "layout.hpp"

// serialization includes
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/vector.hpp>
//#include <boost/serialization/set.hpp>

using namespace std;
//using namespace boost;


// Node: this class allows us to represent a node of our lattice.
class Node : public EmptyNode
{
private:
// --- Serialization  ----------------------------------------------------------
//friend class boost::serialization::access;
//    template<class Archieve>
//void serialize(Archieve & ar, const unsigned int version)
//{
//  ar& selected;
//  ar& quality;
//  ar& pertinence;
//  ar& layouts;
//  ar& ancestors;
//  ar& descendants;
//  ar& parents;
//  ar& children;
//}

// --- Attributes  -------------------------------------------------------------
  vector<Layout> layouts;

  set<string> ancestors;
  set<string> descendants;

  set<string> parents;
  set<string> children;


// --- Tools  ------------------------------------------------------------------

  // relationToString: create a string from the list of the signet (keys) of
  //    relation.
  string relationToString(set<string> relation);
  
public:
// --- Constructors ------------------------------------------------------------
  
  // Node: create a disconnected node.
  //    (1): without a layout.
  Node();
  Node(Layout layout);

// --- Layout management  ------------------------------------------------------
  string getId();
  vector<Layout> getLayouts();
  void insertLayout(Layout layout);
  int compare(Node* other);
  map<vector<int>*, bool> getExtent();

// --- Ancestors management ----------------------------------------------------
  // isDescendantOf: returns true other is the ancestor of this Node.
  bool isDescendantOf(Node* other);

  // getParents: returns the map of ancestors of the node.
  set<string> getAncestors();

  // addAncestor: adds the node of Id src_id in precedent layer at index src_ref
  //    as an ancestor of this node.
  void addAncestor(string src_id);

// --- Descendant management  --------------------------------------------------
  // isAncestorOf:  returns true if other is the descendant of this node.
  bool isAncestorOf(Node* other);

  // getDescendants: returns the map of descendants of the node.
  set<string> getDescendants();

  // addDescendant: adds the node of Id src_id in the following layer at index src_ref
  //    as a descendant of this node.
  void addDescendant(string src_id);

// --- Parents management ------------------------------------------------------
// isDescendantOf: returns true other is the ancestor of this Node.
bool isChildOf(Node* other);

// getParents: returns the map of ancestors of the node.
set<string> getParents();

// addAncestor: adds the node of Id src_id in precedent layer at index src_ref
//    as an ancestor of this node.
void addParent(string src_id);

// --- Children management  ----------------------------------------------------
// isAncestorOf:  returns true if other is the descendant of this node.
bool isParentOf(Node* other);

// getDescendants: returns the map of descendants of the node.
set<string> getChildren();

// addDescendant: adds the node of Id src_id in the following layer at index src_ref
//    as a descendant of this node.
void addChild(string src_id);


// --- Tools  ------------------------------------------------------------------

  // toString: renvoie une chaîne de caractères décrivant le noeud.
  string toString();
  string toCsv();

  void insertExtent(vector<int>* vec, bool b);
};
#endif


