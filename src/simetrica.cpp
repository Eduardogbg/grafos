#include <map>
#include <vector>
#include <algorithm>
#include "aresta.h"
#include "simetrica.h"

using namespace std;


double Simetrica::get(int i, int j) {
  auto coords = make_tuple(min(i, j), max(i, j));

  return this->esparsa.find(coords) == this->esparsa.end()
    ? this->standard
    : this->esparsa[coords];
}

void Simetrica::set(int i, int j, double w) {
  auto coords = make_tuple(min(i, j), max(i, j));

  if (w == this->standard) {
    this->esparsa.erase(coords);
  } else {
    this->esparsa[coords] = w;
    this->ordem = max(max(i, j) + 1, this->ordem);
  }
}

int Simetrica::size() {
  return this->ordem;
}

Simetrica::Simetrica(vector<aresta> arestas, double standard) {
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
  this->standard = standard;
};

Simetrica::Simetrica() {
  map<tuple<int, int>, double> esparsa;
  this->esparsa = esparsa;
  this->ordem = 0;
  this->standard = 0;
};
