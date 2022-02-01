#ifndef LATTICE_HPP
#define LATTICE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// serialization includes
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/vector.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/tokenizer.hpp>

#include "nodelist.hpp"

using namespace std;
using namespace boost;

#define DEFAULT_FIRST_LAYER     0
#define DEFAULT_LAST_LAYER      0
#define DEFAULT_MAX_LAYERS      15

#define CSV_VERTICES_HEADER     "Id,Label,Intent,Extent,Frequency,Positive,Negative,Quality,Pertinence,Mean,Selected"
#define CSV_EDGES_HEADER        "Source,Target"
#define CSV_VERTICES_ROOT       "0,-,-,-,0,0,0,0,0,0,0"


#define DEFAULT_ARCHIVE_NAME    "lattice_archive.lat"
#define DEFAULT_MIN_FREQ        10
#define DEFAULT_MAX_GR          3
#define CONTRAST_COEF           2

class Lattice
{
private:
//friend class boost::serialization::access;
//    template<class Archieve>
//  void serialize(Archieve & ar, const unsigned int version)
//  {
//      ar& layers;
//      ar& transactions;
//  }

// ---  Attributes  ------------------------------------------------------------
  NodeList layers;
//  map<vector<int>,bool> transactions;
  vector<pair<vector<int>, bool>> transactions;
//  vector<string> labels; // Permet de faire le lien entre les entier et leur traduction.

  void calculateGrowthRate(Node* n, int nbPosDataset, int nbNegDataset,
                         double*gr_up, double* gr_down);
  void discardDescendant(Node* n, size_t layer);
  
public:
// --- Constructor  ------------------------------------------------------------
  // Lattice:
  //    (1): Returns an empty lattice.
  //    (2): Returns a lattice with filename as seed.
  Lattice();
  Lattice(const char* seed_intent, const char* seed_extent);
  
// --- Layers management  ------------------------------------------------------
  // addLayer: add a layer generated from the file to the lattice.
  void generateLayers(const char* seed_intent, const char* seed_extent);
  
  // getLayer: returns the layer at index 'index'.
  NodeList* getLayer();
  
// --- Nodes management --------------------------------------------------------
  void discardNode(string id);
  // nodeActivate: activate a node in layer layer_index at index
  //    node_index.
  void selectNode(string id);
  
// --- Tools  ------------------------------------------------------------------
  // display: if short_display=true, display the number of layers as well as
  //    their size, their number of selected and discarded nodes,
  //    and the total number of nodes in the lattice. Else, display in addition
  //     each layer as well as the nodes it contains.
  void display(bool short_display=true);
  
  // toCsv: convert the lattice in two CSV files. The first one for the vertices
  //    (vertices_filename) and the second for the edges (edges_filename).
  void convertToCSV(const char* vertices_filename, const char* edges_filename);
  
//  // save: save the lattice in a file named filename.
//  void save(const char* filename=DEFAULT_ARCHIVE_NAME)
//  {
//    // create and open a character archive for output
//    std::ofstream ofs(filename);
//    boost::archive::text_oarchive oa(ofs);
//    // write class instance to archive
//    oa << *(this);
//    // archive and stream closed when destructors are called
//    ofs.close();
//  }
//
//  // load: load a lattice from the file filename.
//  void load(const char* filename=DEFAULT_ARCHIVE_NAME)
//  {
//    std::ifstream file{filename};
//    boost::archive::text_iarchive ia{file};
//    ia >> *(this);
//    file.close();
//  }
  
// --- Algorithms --------------------------------------------------------------
  // frequenceManagement: desactivate every node in the lattice which hase a
  //    support less than min_threshold.
  void frequenceManagement(size_t min_threshold=DEFAULT_MIN_FREQ);
  
  // computeGrowthRate: desactivate the children of the nodes wich have
  //    a growth rate greater or equal to max_gr.
  void computeGrowthRate();
  void computeConfidence();
  void computeWRAcc();
  void computeChiSquare();

  vector<Node*> getParentsOf(Node* node);
  vector<Node*> getChildrenOf(vector<Node*> nodes);
  void RPSAux(string id);
  void remarkablePatternSelector();
};
#endif
