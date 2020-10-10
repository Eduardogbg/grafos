#include <map>
#include <vector>
#include <cmath>
#include "aresta.h"

#include <iostream>
using namespace std;


class Simetrica {
public:
  double get(int i, int j) {
    return this->esparsa[{ min(i,j), max(i,j) }];
  }

  void set(int i, int j, double w) {
    this->esparsa[{ min(i,j), max(i,j) }] = w;
    this->ordem = max(i, j) + 1;
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
        this->ordem = maiorIndice + 1;
      }
      
      this->esparsa[{ min(i,j), maiorIndice }] = w;
    }
  };

  Simetrica() {
    map<tuple<int, int>, double> esparsa;
    this->esparsa = esparsa;
    this->ordem = 0;
  };

private:
  map<tuple<int, int>, double> esparsa;
  int ordem;
};


int main() {
  vector<aresta> a;
  a.push_back({ 0, 1, 2 });
  a.push_back({ 1, 2, 3 });

  Simetrica s(a);

  cout << "Tamanho: " << s.size() << endl;
  cout << "Distância de 2 pra 1: " << s.get(2, 1) << endl;  

  return 0;
}
