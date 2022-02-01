//
// Created by lehembr211 on 05/10/2021.
//

#ifndef CP4IM_LATTICE_INTENT_H
#define CP4IM_LATTICE_INTENT_H

#include <iostream>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/string.hpp>

#define INT_SEP     "|"


class Intent {
private:
// --- Serialization  ----------------------------------------------------------
//    friend class boost::serialization::access;
//    template<class Archieve>
//    void serialize(Archieve & ar, const unsigned int version)
//    {
//      ar& code;
//      ar& id;
//    }

public:
    vector<int>* code;
    string id;

    string toCsv() {
      return id;
    }

    string toString() {
      string res = string();
      for (auto & elem : *code) {
        res.append(INT_SEP);
        res.append(std::to_string(elem));
      }
      res.append(INT_SEP);
      return res;
    }
};

#endif //CP4IM_LATTICE_INTENT_H
