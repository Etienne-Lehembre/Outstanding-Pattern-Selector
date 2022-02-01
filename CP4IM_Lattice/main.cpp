#include <iostream>
#include "dev-src/lattice.hpp"

#define NB_ARG            3
#define SEED_INTENT       2  // -class.closed
#define SEED_EXTENT       1  // .txt
#define FILE_FORMAT_LEN   4  // len(.txt)

int main(int argc, char* argv[]) {
  if (argc != NB_ARG) return EXIT_FAILURE;
  Lattice lattice = Lattice((const char *) argv[SEED_INTENT], (const char *) argv[SEED_EXTENT]);

// --- GR ----------------------------------------------------------------------
  lattice.computeGrowthRate();
  lattice.remarkablePatternSelector();

  string vertices_str = string(argv[SEED_EXTENT]);
  vertices_str.replace(vertices_str.end() - FILE_FORMAT_LEN,
                       vertices_str.end(), string("_GRVerti.csv"));

  string edges_str = string(argv[SEED_EXTENT]);
  edges_str.replace(edges_str.end() - FILE_FORMAT_LEN,
                    edges_str.end(), string("_GREdges.csv"));

  lattice.convertToCSV(vertices_str.c_str(), edges_str.c_str());

// --- Confidence --------------------------------------------------------------
  lattice.computeConfidence();
  lattice.remarkablePatternSelector();

  vertices_str = string(argv[SEED_EXTENT]);
  vertices_str.replace(vertices_str.end() - FILE_FORMAT_LEN,
                       vertices_str.end(), string("_ConfidenceVerti.csv"));

  edges_str = string(argv[SEED_EXTENT]);
  edges_str.replace(edges_str.end() - FILE_FORMAT_LEN,
                    edges_str.end(), string("_ConfidenceEdges.csv"));

  lattice.convertToCSV(vertices_str.c_str(), edges_str.c_str());

// --- WRAcc  ------------------------------------------------------------------
  lattice.computeWRAcc();
  lattice.remarkablePatternSelector();

  vertices_str = string(argv[SEED_EXTENT]);
  vertices_str.replace(vertices_str.end() - FILE_FORMAT_LEN,
                       vertices_str.end(), string("_WRAccVerti.csv"));

  edges_str = string(argv[SEED_EXTENT]);
  edges_str.replace(edges_str.end() - FILE_FORMAT_LEN,
                    edges_str.end(), string("_WRAccEdges.csv"));

  lattice.convertToCSV(vertices_str.c_str(), edges_str.c_str());

// --- Chi Square --------------------------------------------------------------
  lattice.computeChiSquare();
  lattice.remarkablePatternSelector();

  vertices_str = string(argv[SEED_EXTENT]);
  vertices_str.replace(vertices_str.end() - FILE_FORMAT_LEN,
                       vertices_str.end(), string("_ChiSquareVerti.csv"));

  edges_str = string(argv[SEED_EXTENT]);
  edges_str.replace(edges_str.end() - FILE_FORMAT_LEN,
                    edges_str.end(), string("_ChiSquareEdges.csv"));

  lattice.convertToCSV(vertices_str.c_str(), edges_str.c_str());


  return EXIT_SUCCESS;
}
