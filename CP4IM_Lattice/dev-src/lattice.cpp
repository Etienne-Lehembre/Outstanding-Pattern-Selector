#include "lattice.hpp"

// --- Constructor  ------------------------------------------------------------
Lattice::Lattice()
{
  layers = NodeList();
//  transactions = map<vector<int>, bool>();
  transactions = vector<pair<vector<int>, bool>>();
}

Lattice::Lattice(const char* seed_intent, const char* seed_extent)
{
  // initialization
  Lattice();

  // generating structure
  generateLayers(seed_intent, seed_extent);

  // Creating Concept Lattice
  // layers.generateConcept(); // No need avec le nouveau insertNode

  // Linking concepts together.
  layers.linkAll();
}

// --- Tools  ------------------------------------------------------------------
void Lattice::generateLayers(const char* seed_intent, const char* seed_extent) {
  string line = "";
//  string working = string("Working");

  // Gestion de l'extent  ------------------------------------------------------
  ifstream fextent(seed_extent);

  if (!fextent) {
    cerr << "Lattice::generateLayers: failed to read file: " << seed_extent << "." << endl;
    exit(EXIT_FAILURE);
  }
  cerr << "Lattice::generateLayers: reading: " << seed_extent << "." << endl;

// skeeping the head of the data
  while (fextent) { // Reading until we reach the end of the file.
//    cout << working << string(10 - working.size(), ' ');
//    if (working.size() == 10) {
//      working = string("Working");
//    } else {
//      working.append(".");
//    }

    line = "";

    // Reading a line.
    getline(fextent, line);
    //cout << line << endl;

    // We have reached the end of the info part.
//    cout << "\r";
    if (line.compare("@data")==0) break;
  }

  getline(fextent, line);

  // we now process the data set
//  cout << "\r";
  while (fextent) { // Reading until we reach the end of the file.
//    cout << working << string(10 - working.size(), ' ');
//    if (working.size() == 10) {
//      working = string("Working");
//    } else {
//      working.append(".");
//    }

    line = "";

    // Reading first line.
    getline(fextent, line);
    // cout << line << endl;
    if (line.empty()) break;

    vector<int> vec = vector<int>();
    bool b;
    // converting string into vec<int> and bool
    char_separator<char> sep(" ");
    tokenizer< char_separator<char> > tokens(line, sep);
    for (const string& t : tokens) {
      if (vec.size() + 1 >= vec.capacity())
        vec.reserve(vec.size() * MEMORY_ALLOC_GROWTH + 1);
      vec.push_back(atoi(t.c_str()));
    }
    b = vec.at(vec.size() - 1);
    vec.pop_back();

    // assigning vec and b to the corresponding layouts
//    transactions[vec] = b;

      if (transactions.size() + 1 >= transactions.capacity())
        transactions.reserve(transactions.size() * MEMORY_ALLOC_GROWTH + 1);
      transactions.push_back(pair<vector<int>,bool>(vec, b));

//    cout << "\r";
  }
  transactions.shrink_to_fit();

  fextent.close();

  // Vérification du jeu
  long int nbPos = 0, nbNeg = 0;
  for (auto & tpl : transactions) {
    tpl.second ? nbPos += 1 : nbNeg += 1;
  }
  cout << "Nombre de transactions: " << transactions.size() << endl;
  cout << "Nombre d'éléments positifs: " << nbPos << endl;
  cout << "Nombre d'éléments négatifs': " << nbNeg << endl;

  // Treatment de l'Intent -----------------------------------------------------
  ifstream fintent(seed_intent);
  
  if (!fintent) {
    cerr << "Lattice::generateLayers: failed to read file: " << seed_intent << "." << endl;
    exit(EXIT_FAILURE);
  }
  cerr << "Lattice::generateLayers: reading: " << seed_intent << "." << endl;

  // we now process the data set
  while(fintent) { // Reading until we reach the end of the file.
//    cout << working << string(10 - working.size(), ' ');
//    if (working.size() == 10) {
//      working = string("Working");
//    } else {
//      working.append(".");
//    }


    // Reading first line.
    getline(fintent, line);
    // We don't want to process the separation line between info and data
    // cout << line << endl;
    if (line.empty()) break;

    vector<int> vec = vector<int>();
    // converting string into vec<int> and bool
    char_separator<char> sep(" ");
    tokenizer <char_separator<char>> tokens(line, sep);
    for (const string &t: tokens) {
      if (vec.size() + 1 >= vec.capacity())
        vec.reserve(vec.size() * MEMORY_ALLOC_GROWTH + 1);
      vec.push_back(atoi(t.c_str()));
    }
    //cout << "Popping: " << vec.at(vec.size() - 1) << endl;
    vec.pop_back(); // popping the thing we cannot convert

    // Creating intent node and inserting it
    Layout layout = Layout();
    layout.intent.code = &vec;
    layout.intent.id = layout.intent.toString();
    //cout << layout.intent.toCsv() << endl;
    Node node = Node(layout);

    // Addind extent to the node
    for (auto& tpl : transactions) {
      node.insertExtent((vector<int>*) &(tpl.first), tpl.second);
    }

    layers.insertNode(node);
//    cout << "\r";
  }

  fintent.close();

  cout << "Lattice::generateLayers: concepts generated: " << layers.getSize() << endl;
}

// --- Nodes management --------------------------------------------------------
void Lattice::discardNode(string id)
{
  Node* node = layers.getNode(id);
  if (node != NULL) node->discard();
}

void Lattice::selectNode(string id)
{
  Node* node = layers.getNode(id);
  if (node != NULL) node->select();
}

// --- Tools  ------------------------------------------------------------------
void Lattice::display(bool short_display)
{
  size_t nb_nodes = 0;
  
  cout << "Number of nodes in the lattice: " << nb_nodes << endl;
}

void Lattice::convertToCSV(const char *vertices_filename,
                           const char *edges_filename) {
  cerr << "Lattice:: computing CSVs." << endl;
  // Lien stringId -> intId
  map<string,size_t> link = map<string,size_t>();
  // Opening vertices file.
  ofstream v_filestream(vertices_filename);
  if (!v_filestream) {
    cerr << "Lattice::toCsv: Impossible d'ouvrir le fichier des sommets en écriture." << endl;
    exit(EXIT_FAILURE);
  }
  
  // Writing vertices.
  v_filestream << CSV_VERTICES_HEADER << endl;
  v_filestream << CSV_VERTICES_ROOT << endl;
  size_t k = 1;
  for (auto& tpl : layers.list) {
    link[tpl.first] = k;
    v_filestream << k << CSV_SEP << tpl.second.toCsv() << endl;
    k += 1;
  }
 // size_t index = 1;
  
  // Closing vertices file.
  v_filestream.close();
  
  // Opening edges file.
  ofstream e_filestream(edges_filename);
  if (!e_filestream) {
    cerr << "Lattice::toCsv: Impossible d'ouvrir le fichier des arêtes en écriture." << endl;
    exit(EXIT_FAILURE);
  }
  
  // Writing edges.
  e_filestream << CSV_EDGES_HEADER << endl;
  // Linking to root
  for (auto& tpl : layers.list) {
    if (tpl.second.getAncestors().empty())
      e_filestream << 0 << "," << link.at(tpl.first) << endl;
  }

  // Linking the nodes
  for (auto& tpl : layers.list) {
    for (string child : tpl.second.getChildren())
      e_filestream << link.at(tpl.first) << "," << link.at(child) << endl;
  }
  //index = 1;

  // Closing edges file.
  e_filestream.close();
}


// --- Algorithms --------------------------------------------------------------
void Lattice::frequenceManagement(size_t min_threshold)
{
  cerr << "Lattice:: managing frequence with: " << min_threshold << "." << endl;
  for (auto & tpl : layers.list) {
    Node* n = &get<MAP_VALUE>(tpl);
    if (n != nullptr && n->isSelected()) {
      if (n->getLayouts().at(0).getSupport() < (int) min_threshold) {
        discardNode(get<MAP_KEY>(tpl));
      }
    }
  }
}


void Lattice::calculateGrowthRate(Node* n,
    int nbPosDataset, int nbNegDataset, double*gr_up, double* gr_down)
{
  int nbPos = 0;
  map<vector<int>*, bool> extent = n->getLayouts().at(0).extent;
  for (auto & elem : extent) {
    if (get<MAP_VALUE>(elem)) nbPos += 1;
  }
  int nbNeg = extent.size() - nbPos;
  
  *gr_up = double(nbPos)/double(nbPosDataset); 
  *gr_down = double(nbNeg)/double(nbNegDataset);
}


void Lattice::computeGrowthRate()
{
  cerr << "Lattice:: computing Growth Rate." << endl;
  int nbPosDataset = 0;
  int nbNegDataset = 0;
  for (auto& tpl : transactions)
    tpl.second == 1 ? nbPosDataset += 1 : nbNegDataset += 1;

  // Computing GR on the layers.
  for (auto & elem : layers.list) {
    Node* n = &get<MAP_VALUE>(elem);
    // Is it wise to not compute GR for the desactivated nodes ?  && n->isActive()
    if (n != nullptr) {
      double gr_up = 0.0;
      double gr_down = 0.0;
      calculateGrowthRate(n, nbPosDataset, nbNegDataset,
          &gr_up, &gr_down);
      if (gr_down == 0.0) {
        gr_up == 0.0 ? n->setQuality(0.0) : n->setQuality(1.0);
      } else {
        double growthRate = (double) (gr_up / gr_down);
        n->setQuality(growthRate / (growthRate + 1.0));
      }
    }
  }
}

void Lattice::computeConfidence() {
  cerr << "Lattice:: computing Confidence." << endl;

  // Computing Confidence on the layers.
  for (auto & elem : layers.list) {
    Node* n = &get<MAP_VALUE>(elem);
    // Is it wise to not compute GR for the desactivated nodes ?  && n->isActive()
    if (n != nullptr) {
      double nodeExtSize = n->getExtent().size();
      long int nbPosExt = 0;
      for (auto& tpl : n->getExtent())
        if (tpl.second) nbPosExt += 1;
      // confidence = NbPosElem / support
      n->setQuality((double) (nbPosExt / nodeExtSize));
    }
  }
}

void Lattice::computeWRAcc()
{
  cerr << "Lattice:: computing WRAcc." << endl;
  // Counting number of positive elements in the dataset
  double dataSize = transactions.size();
  long int nbPosDataset = 0;
  for (auto& tpl : transactions)
    if (tpl.second)  nbPosDataset += 1;

  // Computing WRAcc on the layers.
  for (auto & elem : layers.list) {
    Node* n = &get<MAP_VALUE>(elem);
    if (n != nullptr) {
      double nodeExtSize = n->getExtent().size();
      // Counting number of positive elements in the Extent
      long int nbPosExt = 0;
      for (auto& tpl : n->getExtent())
        if (tpl.second) nbPosExt += 1;
      double fst = (double) (nodeExtSize / dataSize);
      double snd = (double) (nbPosExt / nodeExtSize);
      snd -= (double) (nbPosDataset / dataSize);
      n->setQuality(fst * snd);
    }
  }
}

void Lattice::computeChiSquare()
{
  cerr << "Lattice:: computing Chi Square." << endl;
  // Computing WRAcc on the layers.
  double dataSize = transactions.size();
  long int nbPosDataset = 0, nbNegDataSet = 0;
  for (auto& tpl : transactions)
    tpl.second ?  nbPosDataset += 1 : nbNegDataSet += 1;
  for (auto & elem : layers.list) {
    Node* n = &get<MAP_VALUE>(elem);
    if (n != nullptr) {
      double nodeExtSize = n->getExtent().size();
      // Counting number of positive elements in the Extent
      long int nbPosExt = 0, nbNegExt = 0;
      for (auto& tpl : n->getExtent())
        tpl.second ? nbPosExt += 1 : nbNegExt += 1;
      double expectedPos = (double) ((nbPosDataset * nodeExtSize) / dataSize);
      double expectedNeg = (double) ((nbNegDataSet * nodeExtSize) / dataSize);
      double compPos = (double) (nbPosDataset * (dataSize - nodeExtSize)
        / dataSize);
      double compNeg = (double) (nbNegDataSet * (dataSize - nodeExtSize)
        / dataSize);

      double Cell1 = pow(nbPosExt - expectedPos, 2.0) / expectedPos;
      double Cell2 = pow(nbNegExt - expectedNeg, 2.0) / expectedNeg;
      double Cell3 = pow((nbPosDataset - nbPosExt) - compPos, 2.0) / compPos;
      double Cell4 = pow((nbNegDataSet - nbNegExt) - compNeg, 2.0) / compNeg;

      n->setQuality(Cell1 + Cell2 + Cell3 + Cell4);
      if (isnan(n->getQuality())) n->setQuality(MAXFLOAT);
    }
  }
}




// --- RPS  --------------------------------------------------------------------

double std_deviation(double mean, vector<Node*> clusters)
{
  double res = 0.0;

  for (size_t k = 0; k < clusters.size(); ++k) {
    double tmp = res + (pow((clusters.at(k)->getQuality() - mean),2.0) / (double) clusters.size());
    (tmp >= res && tmp < MAXFLOAT) ? res = tmp : res = MAXFLOAT;
  }

  res = sqrt(res);

  return res;
}

vector<Node*> Lattice::getParentsOf(Node *node) {
  vector<Node*> res = vector<Node*>();
  res.push_back(node);

  set<Node*> buffer = set<Node*>();

  for (size_t k = 0; k < res.size(); ++k) {
    for (string elem: res[k]->getParents()) {
      buffer.insert(layers.getNode(elem));
    }
  }


  res.clear();
  res.reserve(buffer.size());
  for (Node* elem : buffer) {
    res.push_back(elem);
  }

  return res;
}

// We want to keep every cluster which has an order range containing 'order'.
vector<Node*> Lattice::getChildrenOf(vector<Node *> nodes) {
  vector<Node*> res = vector<Node*>();
  vector<Node*> tmp = nodes;


  if (!tmp.empty()) {
    set<Node *> buffer = set<Node *>();

    // Getting from children from temp.
    for (size_t k = 0; k < tmp.size(); ++k) {
      for (string elem: tmp[k]->getChildren()) {
        buffer.insert(layers.getNode(elem));
      }
    }

    tmp.clear();
    tmp.reserve(buffer.size());
    for (Node *elem: buffer) {
      res.push_back(elem);
    }
  }
  return res;
}

void Lattice::RPSAux(string id)
{
  Node* node = layers.getNode(id);
  vector<Node*> buffer = getParentsOf(node);
  buffer = getChildrenOf(buffer);

  if (buffer.empty()) {
    node->setPertinence(node->getQuality());
    node->discard();
    return;
  }

  double mean = 0.0;
  for (size_t k = 0; k < buffer.size(); ++k) {
    double tmp = mean + (buffer.at(k)->getQuality() / (double) buffer.size());
    (tmp < MAXFLOAT) ? mean = tmp : mean = MAXFLOAT;
  }

  node->mean = mean;

  double buffer_dev = std_deviation(mean, buffer);
  double node_dev = sqrt(pow((node->getQuality() - mean), 2.0));
  node->setPertinence((node->getQuality() - mean) / buffer_dev);
  if (isnan(node->getPertinence())) node->setPertinence((node->getQuality() - mean));

  (node_dev >= CONTRAST_COEF * buffer_dev && !(node_dev==0.0 && buffer_dev==0.0)) ? node->select() : node->discard();
}

void Lattice::remarkablePatternSelector()
{
  cout << "ClusterLattice: computing pharmacophore activity delta." << endl;
  for (auto & tpl : layers.list) {
    RPSAux(get<MAP_KEY>(tpl));
  }
}
