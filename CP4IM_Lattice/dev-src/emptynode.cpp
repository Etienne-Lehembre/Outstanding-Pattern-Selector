#include "emptynode.hpp"

// --- Tools  ------------------------------------------------------------------


// --- Constructeur ------------------------------------------------------------
EmptyNode::EmptyNode()
{
  selected = false;
  quality = DEFAULT_QUALITY;
  pertinence= DEFAULT_PERTINENCE;
  mean = 0.0;
}

// --- Active management  ------------------------------------------------------
bool EmptyNode::isSelected()
{
  return this -> selected;
}

void EmptyNode::select() {
  this->selected = true;
}

void EmptyNode::discard() {
  this->selected = false;
}


// --- Méthodes pour quality  --------------------------------------------------

double EmptyNode::getQuality()
{
  return this->quality;
}

void EmptyNode::setQuality(double quality)
{
  this->quality = quality;
}


// --- Méthodes pour pertinence ------------------------------------------------

double EmptyNode::getPertinence()
{
  return this->pertinence;
}

void EmptyNode::setPertinence(double pertinence)
{
  this->pertinence = pertinence;
}

// --- Public tools ------------------------------------------------------------
string EmptyNode::toString()
{
  string active_str = string("Selected: ");
  string active_info_str = this->selected ? "true":"false";
  active_str.append(active_info_str);
  
  string quality_str = string("Quality: " + std::to_string(this->quality));
  
  string pertinence_str = string("Pertinence: " + std::to_string(this->pertinence));
  
  return string(active_str + ",\n" + quality_str + ",\n" + pertinence_str);
}


string EmptyNode::toCsv()
{
  string res = string();
  res.append(std::to_string(quality) + CSV_SEP);
  res.append(std::to_string(pertinence) + CSV_SEP);
  res.append(std::to_string(mean) + CSV_SEP);
  res += selected ? SELECTED:DISCARDED;
  return res;
}
