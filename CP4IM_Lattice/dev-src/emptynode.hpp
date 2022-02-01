#ifndef EMPTYNODE_HPP
#define EMPTYNODE_HPP

#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <iostream>

using namespace std;

#define DEFAULT_QUALITY       0
#define DEFAULT_PERTINENCE    0
#define MIN_GRADE             0
#define MAX_GRADE             10
#define IDENTIFIANT           0
#define VALUE                 1
#define NB_MOTIFS             7
#define F_ID                  100
#define F_INDEX               6
#define SELECTED              "1"
#define DISCARDED             "0"
#define FLOAT_INFINITY        -1.0
#define MEMORY_ALLOC_GROWTH   1.5
#define CSV_SEP               ","


// EmptyNode: EmptyNode contains the core informations wich are shared by Nodes
//    and ClusterNodes.
class EmptyNode
{
protected:
// --- Attributes --------------------------------------------------------------
  // active: indicate if the node is active/selected or not.
  bool selected;
  // quality: indicate the quality of the pharmacophore(s) contained in the node
  //    wich has been asigned by an algorithm (as Growth Rate).
  double quality;
  // pertinence: indicate the pertinence of the quality of the node, wich has
  //    been assigned by an algorithm (as Pharmacophores Activity Delta).
  double pertinence;
  
public:
    double mean;
// --- Constructor  ------------------------------------------------------------
  // EmptyNode: create an activated empty node with a quality, pertinence and
  //    grade of '0.0'.
  EmptyNode();
  
// --- Active management  ------------------------------------------------------
  
  // isActive: return true if the node is activated, return false if not.
  bool isSelected();

  // activate: activate the node.
  void select();

  // discard: discard the node.
  void discard();

// --- Quality management ------------------------------------------------------

  // getQuality: return the quality of the node.
  double getQuality();
  
  // setQuality: set a quality to the node.
  void setQuality(double quality);
  
// --- Pertinence management  --------------------------------------------------

  // getPertinence: return the pertinence of the node.
  double getPertinence();
  
  // setPertinence: set a pertinence to the node.
  void setPertinence(double pertinence);

// --- Public tools ------------------------------------------------------------

  // toString: return a string describing an empty node.
  string toString();
  string toCsv();
};
#endif


