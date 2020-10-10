#include <map>
#include <cmath>
#include "simetrica.h"

using namespace std;


class Simetrica {
public:
  double get(int i, int j) {
    return this->esparsa[{ min(i,j), max(i,j) }];
  }

  void set(int i, int j, double w) {
    this->esparsa[{ min(i,j), max(i,j) }] = w;
  }

  int size() {
    return this->ordem;
  }

  Simetrica(vector<aresta> arestas) {
    for (auto a: arestas) {
      int i, j;
      double w;
      tie (i, j, w) = a;

      int maiorIndice = max(i, j);
      if (maiorIndice > this->ordem) {
        this->ordem = maiorIndice;
      }
      
      this->esparsa[{ min(i,j), maiorIndice }] = w;
    }
  };

  Simetrica() {};

private:
  map<tuple<int, int>, double> esparsa;
  int ordem;
};
