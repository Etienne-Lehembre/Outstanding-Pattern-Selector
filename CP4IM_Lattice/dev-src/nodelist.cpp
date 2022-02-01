#include "nodelist.hpp"
// --- Constructor  ------------------------------------------------------------
NodeList::NodeList()
{
  list = map<string,Node>();
}

size_t NodeList::getSize()
{
  return this->list.size();
}

// --- Node's methods ----------------------------------------------------------
Node* NodeList::getNode(const string& id)
{
  if (list.count(id) != 0) return &list.at(id);
  return nullptr;
}

void NodeList::insertNode(Node node)
{
//  for (auto& elem : list) {
//    if (elem.second.compare(&node) == EXTENT_IS_EQUAL) {
//      for (Layout layout: node.getLayouts())
//        elem.second.insertLayout(layout);
//      return;
//    }
//  }

  list.insert(pair<string, Node>(node.getId(), node));
  linkToAncestors(node.getId());
}

void NodeList::eraseNode(const string& id)
{
  if (list.count(id) != 0) list.erase(id);
}

// --- Tools  ------------------------------------------------------------------
void NodeList::generateConcept() {
  cout << "NodeList::generateConcept: starting." << endl;
  map<string, Node> res = map<string, Node>();
  cout << "Size of list:" << list.size() << endl;
  //init
  res.insert(*list.begin());
  list.erase(list.begin()->first);

  while (!list.empty()) {
    set<string> to_erase = set<string>();
//    cout << res.size() << "|" << list.size();

    for (auto& tpl1 : list) {
      for (auto& tpl2 : res) {
        if (tpl1.second.compare(&tpl2.second) == EXTENT_IS_EQUAL) {
          to_erase.insert(tpl1.first);
          for (Layout layout: tpl1.second.getLayouts())
            tpl2.second.insertLayout(layout);
        }
      }
      if (!to_erase.count(tpl1.first)) res.insert(tpl1);
      to_erase.insert(tpl1.first);
    }

    for (string elem : to_erase) list.erase(elem);
//    cout << "\r";
  }
  cout << "Size of list:" << list.size() << endl;
  cout << "Nb concept: " << res.size() << endl;

  for (auto& tpl : res)
    list.insert(pair<string,Node>(tpl.second.getId(),tpl.second));
  cout << "Size of list:" << list.size() << endl;
}

// Faire d'abord le lien avec tous les ancêtres.
// Faire ensuite la distinction avec les ancêtres directes.

void NodeList::linkAll()
{
  // We have done ancestors in insertNode.
//  cout << "NodeList::linkAll(): linking ancestors." << endl;
//  for (auto & tpl : list) linkToAncestors(tpl.first);
  cout << "NodeList::linkAll(): linking parents." << endl;
  for (auto & tpl : list) linkToParents(tpl.first);
}

void NodeList::linkToAncestors(string id) {
  if (list.count(id) == 0) return;

  for (auto& elem : list) {
    if (get<MAP_VALUE>(elem).isAncestorOf(&list.at(id))) {
      // ajouter elem comme ancêtre de index et id comme descendant de elem
      (&list.at(id))->addAncestor(get<MAP_KEY>(elem));
      get<MAP_VALUE>(elem).addDescendant(id);
    }
    if (get<MAP_VALUE>(elem).isDescendantOf(&list.at(id))) {
      // ajouter elem comme descendant de id et id comme ancêtre de elem
      (&list.at(id))->addDescendant(get<MAP_KEY>(elem));
      get<MAP_VALUE>(elem).addAncestor(id);
    }
  }
}

void NodeList::linkToParents(string id) {
  if (list.count(id) == 0) return;

  // We can narrow the search to the ancestors
  for (auto& elem : list.at(id).getAncestors()) {
    if (list.at(elem).isParentOf(&list.at(id))) {
      // ajouter elem comme ancêtre de index et id comme descendant de elem
      (&list.at(id))->addParent(elem);
      list.at(elem).addChild(id);
    }
  }

  // Not needed because the children are found in the first loop ?
//  for (auto& elem : list.at(id).getDescendants()) {
//    if (list.at(elem).isChildOf(&list.at(id))) {
//      // ajouter elem comme descendant de id et id comme ancêtre de elem
//      (&list.at(id))->addChild(elem);
//      list.at(elem).addParent(id);
//    }
//  }
}

string NodeList::toString()
{
  string str = "<";
  for (auto & n : this->list) {
    str.append(get<MAP_VALUE>(n).toString());
    str.append(",\n\n");
  }
  
  str.size() == 1 ? str.append(">") : str.replace(str.end() - 3, str.end(), ">");
  
  return str;
}

void NodeList::insertExtent(vector<int>* vec, bool b)
{
  for (auto & tpl : list) {
    tpl.second.insertExtent(vec, b);
  }
}

