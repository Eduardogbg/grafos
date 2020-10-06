#include <iostream>
#include "exer1.h"

using namespace std;


void cicloEuleriano(Grafo grafo) {
  int grauImpar [2];
  int qtdGrauImpar = 0;

  int ordem = grafo.qtdVertices();
  for (int i = 0; i < ordem; ++i) {
    bool impar = grafo.grau(i) % 2 != 0;

    if (impar) {
      grauImpar[qtdGrauImpar++] = i;
    }
  }

  if (qtdGrauImpar > 2 || qtdGrauImpar == 1) {
    cout << '0' << endl;
    return;
  }

  cout << '1' << endl;
  vector<int> ciclo;
  auto g = grafo.copia();
  int v = qtdGrauImpar ? grauImpar[0] : 0;

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
  } while(g.qtdArestas() > 0);

  for (int i = 0; i < ciclo.size(); ++i) {
    if (i != 0) {
      cout << ',';
    }
    cout << ciclo[i];
  }
  cout << endl;
}
