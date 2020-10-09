#include <iostream>
#include <queue>
#include "exer1.h"

using namespace std;


void busca(Grafo grafo, int s) {
  queue<int> fila;

  int linha = 0;
  int v = s;
  do {
    auto vizinhos = grafo.vizinhos(v);

    cout << linha << ": ";
    for (int i = 0; i < sizeof(vizinhos); ++i) {
      if (i != 0) {
        cout << ', ';
      }

      fila.push(i);
      
      cout << i;
    }
    cout << endl;

    fila.pop();
    v = fila.front();
  } while (!fila.empty());
}
