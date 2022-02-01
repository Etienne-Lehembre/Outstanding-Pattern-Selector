#include "node.hpp"

// --- Constructor  ------------------------------------------------------------
Node::Node()
{
  layouts = vector<Layout>();
  ancestors = set<string>();
  descendants = set<string>();
}

Node::Node(Layout layout) {
  layouts.push_back(layout);
}

// --- Layout Management  ------------------------------------------------------
vector<Layout> Node::getLayouts()
{
  return this->layouts;
}


void Node::insertLayout(Layout layout)
{
  if (layouts.size() + 1 >= layouts.capacity()) {
    layouts.reserve(layouts.size() * MEMORY_ALLOC_GROWTH + 1);
  }
  layouts.push_back(layout);
}

string Node::getId()
{
  return layouts.at(0).intent.id;
}

int Node::compare(Node* other)
{
  return layouts.at(0).compare(&(other->getLayouts().at(0)));
}

map<vector<int>*, bool> Node::getExtent()
{
  return layouts.at(0).extent;
}

// --- Ancestors management ----------------------------------------------------
bool Node::isDescendantOf(Node* other)
{
  return compare(other) == EXTENT_IS_IN;
}
set<string> Node::getAncestors()
{
  return ancestors;
}

void Node::addAncestor(string src_id)
{
    this->ancestors.insert(src_id);
}

// --- Descendant management  --------------------------------------------------
bool Node::isAncestorOf(Node* other)
{
  return compare(other) == EXTENT_INLCUDE;
}

set<string> Node::getDescendants()
{
  return descendants;
}

void Node::addDescendant(string src_id)
{
    descendants.insert(src_id);
}

// --- Parents management ------------------------------------------------------
bool Node::isChildOf(Node *other) {
  if (compare(other) == EXTENT_IS_IN) {
    for (string a1 : ancestors)
      for (string a2 : other->getDescendants())
        if (a1.compare(a2) == 0) return false;

    return true;
  }
  return false;
}

set<string> Node::getParents() {
  return parents;
}

void Node::addParent(string src_id) {
  parents.insert(src_id);
}

// --- Children management  ----------------------------------------------------
bool Node::isParentOf(Node *other) {
  if (compare(other) == EXTENT_INLCUDE) {
    for (string a1 : descendants)
      for (string a2 : other->getAncestors())
        if (a1.compare(a2) == 0) return false;

    return true;
  }
  return false;
}

set<string> Node::getChildren() {
  return children;
}

void Node::addChild(string src_id) {
  children.insert(src_id);
}

// --- Tools  ------------------------------------------------------------------
string Node::relationToString(set<string> relation)
{
  string str = string("["); 
  for(auto const& elem: relation) {
    str.append(elem);
    str.append(", ");
  }
  str.size() < 3 ? str.append("empty]") : str.replace(str.end() - 2,
      str.end(), "]");
  
  return str;
}

// --- Public tools ------------------------------------------------------------


string Node::toString()
{
  string id_str = string("Layout: " + getId());
  
  string embeddings_str = string("Extent: ");
  // string embeddings_str_info = this->embeddings.toString();
  //embeddings_str.append(embeddings_str_info);
  
  string emptynode_str = EmptyNode::toString();
  
  string ancestors_str = string("Ancestors: ");
  string ancestors_str_info = this->relationToString(this->ancestors);
  ancestors_str.append(ancestors_str_info);
  
  string Descendantren_str = string("Descendants: ");
  string Descendantren_str_info = this->relationToString(this->descendants);
  Descendantren_str.append(Descendantren_str_info);
  
  return string("{" + id_str + embeddings_str + "\n" + emptynode_str + ",\n"
      + ancestors_str + ",\n" + Descendantren_str + "}");
}


string Node::toCsv()
{
  string res = string();
  
  string emptynode_csv = EmptyNode::toCsv();

  res.append(layouts.at(0).intent.id);// Label
  res.append(CSV_SEP);
  // Intents
  string intents_str = string();
  for (auto& layout : layouts) {
    if (!intents_str.empty()) intents_str.append(VAL_SEP);
    intents_str.append(layout.intent.toCsv());
  }
  res.append(intents_str);
  res.append(CSV_SEP);
  res.append(layouts.at(0).extToCsv()); // extent and frequency
  res.append(CSV_SEP);
  res.append(emptynode_csv); // Adding empty node informations.
  return res;
}

void Node::insertExtent(vector<int>* vec, bool b)
{
  for (auto& layout : layouts) {
    if (layout.validExtent(vec)) layout.extent[vec] = b;
  }
}
