#include <iostream>
#include <queue>
#include "exer1.h"

using namespace std;


void busca(Grafo grafo, int s) {
  queue<int> pilha;

  int linha = 0;
  int v = s;
  do {
    auto vizinhos = grafo.vizinhos(s);

    cout << linha << ": ";
    for (int i = 0; i < sizeof(vizinhos); ++i) {
      if (i != 0) {
        cout << ', ';
      }

      pilha.push(i);
      
      cout << i;
    }
    cout << endl;

    pilha.pop();
    v = pilha.front();
  } while (!pilha.empty());
}
