//
// Created by guillermo on 2/23/17.
//


#ifndef GHCCR_CONTROLADOR_H
#define GHCCR_CONTROLADOR_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unordered_set>
#include <set>
#include <math.h>
#include <limits.h>

#include "Endpoint.h"

using namespace std;

class Controlador {
public:
    vector<int> tam_videos; // tamanio de videos
    vector<vector< pair <int, float> > > prioridades; // r= ncaches c = nvideos
    vector<vector<vector<int> > > interesados; //vector de EP interesados por video
    vector<Endpoint> endpoints;
    int ncaches;
    int tam_cache;
    int nvideos;


    Controlador (){

    }

    void iniciar(){
        prioridades.resize (ncaches);
        interesados.resize(ncaches);

        for (int i= 0; i < ncaches; i++){
            prioridades[i].resize(nvideos);
            interesados[i].resize(nvideos);

            for (int j= 0; j < nvideos; j++){
                prioridades[i][j].first= j ;
                prioridades[i][j].second= 0.0;
            }
        }

    }
    float prior(int ep_id, int ch_id, int v_id);
    void calculaprioridad();
    void seleccionaVideos (ostream & os);

    void imprime(ostream & os){
        calculaprioridad();
        //printConnections(cout);
        seleccionaVideos(os);
    }

    void printConnections(ostream & os){

        /*
         * ENDPOINTS -> VIDEOS
         * */
        cout << "'ENDPOINT'";
        for(unsigned int i=0; i<tam_videos.size(); i++)
            cout << ",'VIDEO " << i << "'";
        cout << endl;
        for(unsigned int i=0; i<endpoints.size(); i++){
            cout << i ;
            for(unsigned int j=0; j<endpoints[i].peticiones_video.size(); j++)
                cout << ","<< endpoints[i].peticiones_video[j];
            cout << endl;
        }

        cout << "###################" << endl;

        /*
         * ENDPOINTS -> CACHES
         * */
        cout << "'ENDPOINT'";
        for(unsigned int i=0; i<prioridades.size(); i++)
            cout << ",'CACHE " << i << "'";
        cout << endl;
        for(unsigned int i=0; i<endpoints.size(); i++){
            cout << i ;
            for(unsigned int j=0; j<endpoints[i].latencias.size(); j++)
                cout << ","<< endpoints[i].latencias[j];
            cout << endl;
        }
    }

    friend istream & operator>> (istream & in, Controlador & c);

};


#endif //GHCCR_CONTROLADOR_H
