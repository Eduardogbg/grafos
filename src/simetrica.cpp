#include <map>
#include <vector>
#include <algorithm>
#include "aresta.h"
#include "simetrica.h"

using namespace std;


double Simetrica::get(int i, int j) {
  auto coords = make_tuple(min(i, j), max(i, j));

  return this->esparsa.find(coords) == this->esparsa.end()
    ? 0
    : this->esparsa[coords];
}

void Simetrica::set(int i, int j, double w) {
  auto coords = make_tuple(min(i, j), max(i, j));

  if (w == 0) {
    this->esparsa.erase(coords);
  } else {
    this->esparsa[coords] = w;
    this->ordem = max(max(i, j) + 1, this->ordem);
  }
}

int Simetrica::size() {
  return this->ordem;
}

Simetrica::Simetrica(vector<aresta> arestas) {
  for (auto a : arestas) {
    int i, j;
    double w;
    tie(i, j, w) = a;

    int maiorIndice = max(i, j);
    if (maiorIndice > this->ordem) {
      this->ordem = maiorIndice + 1;
    }

    this->esparsa[{min(i, j), maiorIndice}] = w;
  }
};

Simetrica::Simetrica() {
  map<tuple<int, int>, double> esparsa;
  this->esparsa = esparsa;
  this->ordem = 0;
};
