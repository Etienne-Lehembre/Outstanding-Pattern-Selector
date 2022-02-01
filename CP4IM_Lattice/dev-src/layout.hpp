//
// Created by lehembr211 on 05/10/2021.
//

#ifndef CP4IM_LATTICE_LAYOUT_H
#define CP4IM_LATTICE_LAYOUT_H

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/map.hpp>

#include "intent.hpp"

#define MAP_KEY             0
#define MAP_VALUE           1
#define CLASS_INACTIVE      0
#define CLASS_ACTIVE        1

#define EXTENT_INLCUDE      1
#define EXTENT_IS_EQUAL     0
#define EXTENT_IS_IN        -1
#define EXTENT_NOT_RELATED  -2
#define NUMBER_OF_CLASSES   2
#define VAL_SEP             "|"
#define EXT_SEP             "-"
#define CSV_SEP             ","


class Layout {
private:
// --- Serialization  ----------------------------------------------------------
//    friend class boost::serialization::access;
//    template<class Archieve>
//    void serialize(Archieve & ar, const unsigned int version)
//    {
//      ar& intent;
//      ar& extent;
//    }

public:
    Intent intent;
    map<vector<int>*, bool> extent;

    int vecIntCompare(vector<int>* v1, vector<int>* v2)
    {
      size_t k = 0;
      while (k < v1->size() && k < v2->size()) {
        int diff = v1->at(k) - v2->at(k);
        if (diff != 0) return diff;
        k += 1;
      }
      return v1->size() - v2->size();
    }

    // retravailler pour retourner:
    // +1 si this->exent contient other->extent
    // 0 si this->extent == other->extent
    // -1 si this extent est inclus dans other->extent
    // -2 si il n'y pas de lien entre this->extent et other->extent
    int compare(Layout* other) {
      map<vector<int>*, bool>* bigExt;
      map<vector<int>*, bool>* smallExt;
      if (extent.size() > other->extent.size()) {
        bigExt = &extent;
        smallExt = &(other->extent);
      } else {
        bigExt = &(other->extent);
        smallExt = &extent;
      }

      for (auto & e : *smallExt) {
        bool b = false;
        for (auto & o : *bigExt) {
          //if (vecIntCompare(e.first, o.first) == 0) {
          if (e.first == o.first) {
            b = true;
            break;
          }
        }
        if (!b) return EXTENT_NOT_RELATED;
      }

      int size_diff = extent.size() - other->extent.size();
      if (size_diff == 0) {
        return EXTENT_IS_EQUAL;
      } else if (size_diff > 0) {
        return EXTENT_INLCUDE;
      } else {
        return EXTENT_IS_IN;
      }
    }

    int getSupport() {
      return extent.size();
    }

    // return intent,extent,frequency
    string extToCsv() {
      string res = string();
      string ext_str = string();
      long int nbPos = 0;
      long int nbNeg = 0;
      for (auto& ext: extent) {
        if (!ext_str.empty()) ext_str.append(EXT_SEP);
        for (auto& val : *(ext.first)) {
          ext_str.append(VAL_SEP);
          ext_str.append(to_string(val));
        }
        ext_str.append(VAL_SEP);
        ext.second ? nbPos += 1 : nbNeg += 1;
      }
      res.append(ext_str);
      res.append(CSV_SEP);
      res.append(to_string(extent.size()));
      res.append(CSV_SEP);
      res.append(to_string(nbPos));
      res.append(CSV_SEP);
      res.append(to_string(nbNeg));

      return res;
    }

    bool validExtent(vector<int>* candidate) {
      for (auto& elem1 : *(intent.code)) {
        bool b = false;
        for (auto& elem2 : *candidate) {
          if (elem1 == elem2) {
            b = true;
            break;
          }
        }
        if (!b) return false;
      }
      return true;
    }

/*
    vector<long int> enumerateClasses() {
      vector<long int> res = vector<long int>();
      res.reserve(NUMBER_OF_CLASSES);
      for (size_t k = 0; k < NUMBER_OF_CLASSES; ++k) res[k] = 0;
      for (auto& tpl : extent) res[tpl.second] += 1;
      return res;
    }
//*/
};


#endif //CP4IM_LATTICE_LAYOUT_H
