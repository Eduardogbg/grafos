#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <queue>
#include "simetrica.h"
#include "grafo.h"

using namespace std;


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
  bool haAresta(int u, int v) {
    return this->adjacencia.get(u, v) != NULL;
  }
  double peso(int u, int v) {
    return this->adjacencia.get(u, v);
  }
  void removerAresta(int u, int v) {
    this->adjacencia.set(u, v, 0);
  }

  int grau(int v) {
    int grau = 0;

    for (int u = 0; u < adjacencia.size(); ++u) {
      if (this->haAresta(u, v)) {
        ++grau;
      }
    }

    return grau;
  };
  int* vizinhos(int v) {
    vector<int> vizinhos;

    for (int u = 0; u < adjacencia.size(); ++u) {
      if (this->haAresta(u, v)) {
        vizinhos.push_back(u);
      }
    }

    return &vizinhos[0];
  }

  void busca(int s);
  void cicloEuleriano();

  Grafo copia() {
    return Grafo(this->labels, this->arestas);
  }

  Grafo(vector<string> labels, vector<aresta> arestas) {
    this->labels = labels;
    this->arestas = arestas;

    Simetrica adjacencia(arestas);
    this->adjacencia = adjacencia;
  };

  Grafo() {};

private:
  vector<string> labels;
  Simetrica adjacencia;
  vector<aresta> arestas;
};

void Grafo::busca(int s) {
  queue<int> fila;

  int linha = 0;
  int v = s;
  do {
    auto vizinhos = this->vizinhos(v);

    cout << linha << ": ";
    for (int i = 0; i < sizeof(vizinhos); ++i) {
      fila.push(i);

      if (i != 0) {
        cout << ', ';
      }
      cout << i;
    }
    cout << endl;

    fila.pop();
    v = fila.front();
  } while (!fila.empty());
}

void Grafo::cicloEuleriano() {
  int grauImpar[2];
  int qtdGrauImpar = 0;

  int ordem = this->qtdVertices();
  for (int i = 0; i < ordem; ++i) {
    if (this->grau(i) % 2 != 0) {
      cout << '0' << endl;
      return;
    }
  }
  cout << '1' << endl;

  vector<int> ciclo;
  auto g = this->copia();
  int v = 0;

  do {
    auto vizinhos = g.vizinhos(v);

    int size = sizeof(vizinhos);
    for (int i = 0; i < size; ++i) {
      if (g.grau(i) || i == size - 1) {
        ciclo.push_back(i);
        g.removerAresta(i, v);
        v = i;
        break;
      }
    }
  } while (g.qtdArestas() > 0);

  for (int i = 0; i < ciclo.size(); ++i) {
    if (i != 0) {
      cout << ',';
    }
    cout << ciclo[i];
  }
  cout << endl;
}
