#pragma once

#include <vector>
#include <map>
#include <tuple>
#include "aresta.h"

using namespace std;


class Simetrica {
public:
  double get(int i, int j);
  void set(int i, int j, double w);
  int size();

  Simetrica(vector<aresta> arestas);
  Simetrica();

private:
  map<tuple<int, int>, double> esparsa;
  int ordem;
};
