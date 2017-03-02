//
// Created by guillermo on 2/23/17.
//

#include <iostream>

#include <fstream>

#include <string.h>
#include <stdlib.h>

#include <vector>
#include <set>

#include "Controlador.h"

using namespace std;

int main(int argc, char * argv[]){
    Controlador controlador;
    srand(time(NULL));

    if(argc != 2){
        cout << "Archivo modafaca" << endl;
        return 1;
    }
    string entrada = argv[1];
    string salida = entrada + ".out";


    ifstream in (entrada.c_str());

    if (!in){
        cout << "Error abriendo " << entrada << endl;
        return 1;
    }
    ofstream out (salida.c_str());

    if (!out){
        cout << "Error abriendo " << salida << endl;
        return 1;
    }


    in >> controlador;

    // Mostrar Salida
    controlador.imprime(out);
    in.close();
    out.close();
}
