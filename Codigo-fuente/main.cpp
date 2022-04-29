#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>

using namespace std;

#include "headers/SDDS.h"

template <typename T>
Data SDDS<T>::ref = Data();

int main(void) {
    int n, m;
    bool b;
    Data dim;
    DS<int> *SL,*G;
    DS<int> *SL2,*G2;

    srand(time(NULL));

    SDDS<int>::create(&G, GRAPH);
    SDDS<int>::create(&SL,SINGLE_LINKED_LIST);

    for (int i = 0; i < 5; i++) {

        SDDS<int>::insert(SL,i);
        SDDS<int>::insert(G, i, i);
    }
    DS<int>* list;
    for(int g = 0; g < 10; g++){
        SDDS<int>::create(&list,SINGLE_LINKED_LIST);

        m = rand()%9+1;
        for(int c = 0; c < m; c++){
            n = rand()%10;
            SDDS<int>::search(list,n,&b);
            if(n!=g && !b) SDDS<int>::insert(list,n);
        }
        SDDS<int>::define_connections(G,g,list);

        SDDS<int>::destroy(list);
    }
    delete list;

    SDDS<int>::show(SL,false);
    SDDS<int>::show(SL,true);
    SDDS<int>::show(G, false);
    SDDS<int>::show(G, true);

    SDDS<int>::extension(SL,&n);
    cout << "La longitud de la lista enlazada simple es: " << n << "\n";
    SDDS<int>::extension(G, &n);
    cout << "La cantidad de nodos en el grafo es: " << n << "\n";

    SDDS<int>::extract(SL,3,&n);
    cout << "El dato extraído de la lista enlazada simple es: " << n << "\n";
    SDDS<int>::extract(G, 3, &n);
    cout << "El dato extraído del grafo es: " << n << "\n";

    SDDS<int>::search(SL,3,&b);
    cout << "El resultado de búsqueda en la lista enlazada simple resultó: " << ((b)?"TRUE\n":"FALSE\n");
    SDDS<int>::search(G, 6, &b);
    cout << "El resultado de búsqueda en el grafo resultó: " << ((b) ? "TRUE\n" : "FALSE\n");

    SDDS<int>::count(SL,3,&n);
    cout << "El resultado del conteo en la lista enlazada simple resultó: " << n << "\n";
    SDDS<int>::count(G, 6, &n);
    cout << "El resultado del conteo en el grafo resultó: " << n << "\n";

    SDDS<int>::create_copy(SL,&SL2);
    cout << "Se muestra la copia de la lista enlazada simple:\n";
    SDDS<int>::create_copy(G,&G2);
    cout << "Se muestra la copia del grafo:\n";
    SDDS<int>::show(G2,false);

    SDDS<int>::reverse(SL2);
    cout << "Se muestra la copia de la lista enlazada simple invertida:\n";
    SDDS<int>::show(SL2,false);

    SDDS<int>::destroy(SL);     SDDS<int>::destroy(SL2);
    SDDS<int>::destroy(G);      SDDS<int>::destroy(G2);

    delete SL;      delete SL2;
    delete G;       delete G2;

    return 0;
}