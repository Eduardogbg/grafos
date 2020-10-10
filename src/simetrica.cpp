#include <map>
#include <vector>
#include <algorithm>
#include "aresta.h"
#include "simetrica.h"

using namespace std;


double Simetrica::get(int i, int j) {
  return this->esparsa[{min(i, j), max(i, j)}];
}

void Simetrica::set(int i, int j, double w) {
  this->esparsa[{min(i, j), max(i, j)}] = w;
  this->ordem = max(i, j) + 1;
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
