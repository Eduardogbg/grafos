#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include "exer1.h"
using namespace std;


typedef tuple<int, int, double> Aresta;

class Simetrica {
public:
  double get(int i, int j) {
    return this->esparsa[min(i,j), max(i,j)];
  }

  void set(int i, int j, double w) {
    this->esparsa[min(i,j), max(i,j)] = w;
  }

  int size() {
    return this->ordem;
  }

  Simetrica(vector<Aresta> arestas) {
    for (int k = 0; k <= arestas.size(); k++) {
      Aresta aresta = arestas[k];

      int i, j;
      double w;
      tie (i, j, w) = aresta;

      int maiorIndice = max(i, j);
      if (maiorIndice > this->ordem) {
        this->ordem = maiorIndice;
      }
      
      this->esparsa[min(i,j), maiorIndice] = w;
    }
  };

  Simetrica() {};

private:
  map<int, int, double> esparsa;
  int ordem;
};

class Grafo {
public:
  int qtdVertices() {
    return this->labels.size();
  }

  int qtdArestas() {
    return this->arestas.size();
  }

  string rotulo(int v) {
    return this->labels[v];
  }

  int grau(int v) {
    int grau = 0;

    for (int u = 0; u < adjacencia.size(); ++u) {
      if (this->adjacencia.get(u, v) != 0) {
        ++grau;
      }
    }

    return grau;
  };

  int* vizinhos(int v) {
    vector<int> vizinhos;

    for (int u = 0; u < adjacencia.size(); ++u) {
      if (this->adjacencia.get(u, v) != 0) {
        vizinhos.push_back(u);
      }
    }

    vizinhos.data();

    return &vizinhos[0];
  }

  bool haAresta(int u, int v) {
    return this->adjacencia.get(u, v) != NULL;
  }

  double peso(int u, int v) {
    return this->adjacencia.get(u, v);
  }

  Grafo(vector<string> labels, vector<Aresta> arestas) {
    this->labels = labels;
    this->arestas = arestas;
    
    Simetrica adjacencia(arestas);
    this->adjacencia = adjacencia;
  };

  Grafo() {};

private:
  vector<string> labels;
  vector<Aresta> arestas;
  Simetrica adjacencia;
};
