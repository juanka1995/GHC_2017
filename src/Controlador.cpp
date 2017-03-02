//
// Created by guillermo on 2/23/17.
//

#include "Controlador.h"
#include <algorithm>
#include <iostream>

istream & operator>> (istream & in, Controlador & c){
    int nvideos, nendpoints, ndescriptions, ncaches, ntamanio_cache;
    vector<int> videos;
    vector<Endpoint> endpoints;

    in >> nvideos >> nendpoints >> ndescriptions >> ncaches >> ntamanio_cache;

    c.ncaches= ncaches;
    c.nvideos= nvideos;

    c.tam_cache= ntamanio_cache;

    c.iniciar();

    // tamanios videos
    for (int i= 0; i < nvideos; i++){
        int tamanio_v;

        in >> tamanio_v;

        videos.push_back (tamanio_v);
    }

    c.tam_videos= videos;

    // endpoints
    for (int i= 0; i < nendpoints; i++){
        int latencia_cen, ncaches_e;

        in >> latencia_cen >> ncaches_e;

        vector<int> latencias_cache;
        latencias_cache.resize (ncaches);

        for (int j= 0; j < ncaches; j++){
            latencias_cache[j]= -1;

        }
        for (int j= 0; j < ncaches_e; j++){
            int id, lat;

            in >> id >> lat;
            latencias_cache[id]= lat;

        }

        Endpoint e (i, latencia_cen, latencias_cache, nvideos, ncaches_e);
        endpoints.push_back (e);
    }

    // Peticiones

    for (int i= 0; i < ndescriptions; i++){
        int npeticiones, nvideo, nendpoint;
        vector<int> peticiones_video;
        peticiones_video.resize (nvideos);

        for  (int j= 0; j < nvideos; j++){
            peticiones_video[j]= 0;
        }


        in >> nvideo;
        in >> nendpoint;
        in >> npeticiones;

        endpoints[nendpoint].aniadirPeticionVideo (nvideo, npeticiones);
    }

    c.endpoints= endpoints;


    return in;
}


//
// Created by anibal on 23/02/17.
//

bool order(const pair<int,float> & p1, const pair<int,float> & p2){
    return p1.second < p2.second;
}

int getMax(const vector<int> & v){
    int max = INT_MAX;
    int pos = 0;
    for(unsigned int i=0; i<v.size(); i++){
        if(v[i] < max){
            max = v[i];
            pos = i;
        }
    }
    return pos;
}

void Controlador::seleccionaVideos(ostream & os) {
    os << ncaches << endl;
    vector<int> suma_total(ncaches, 0);
    for(int i=0; i<ncaches; i++){
        for(unsigned int j=0; j<prioridades[i].size(); j++)
            suma_total[i] += prioridades[i][j].second;
    }
    for(int i=0; i<ncaches; i++){
        //Selecciono la más prioritaria
        unsigned int cache_id = getMax(suma_total);
        suma_total[cache_id] = INT_MAX;

        //Seleccionada
        cout << 100.0*i/ncaches << '%' << endl;
        for(unsigned int j=0; j < tam_videos.size(); j++){
            prioridades[cache_id][j].second /= pow(tam_videos[j],0.5);
        }
        sort(prioridades[cache_id].begin(), prioridades[cache_id].end(), order);
        vector<int> videos;
        int max = tam_cache;
        for(int j=prioridades[cache_id].size()-1; j>=0 ; j--){ //Por cada uno de los videos
            if(max - tam_videos[prioridades[cache_id][j].first] >= 0){
                videos.push_back(prioridades[cache_id][j].first);
                max -= tam_videos[prioridades[cache_id][j].first];
                for(unsigned int k=0; k < interesados[cache_id][j].size(); k++){
                    for(unsigned int l=0; l<endpoints[interesados[cache_id][j][k]].latencias.size(); l++){
                        if((cache_id!=l) && (endpoints[interesados[cache_id][j][k]].latencias[l] != -1)){
                            int prio = prior(interesados[cache_id][j][k], l, prioridades[cache_id][k].first);
                            prioridades[l][prioridades[cache_id][k].first].second -= prio;
                            suma_total[l] -= prio;
                        }
                    }
                }
            }
        }
        os << i;
        for(unsigned int j=0; j<videos.size();j++){
            os << ' ' << videos[j];
        }
        os << endl;
    }
}

void Controlador::calculaprioridad() {
    for (unsigned int i = 0; i < endpoints.size(); i++) {
        for (int j = 0; j < ncaches; ++j) {
            for (unsigned int k = 0; k < tam_videos.size(); ++k) {
                if((endpoints[i].peticiones_video[k] != 0) && (endpoints[i].ncaches != 0) && (endpoints[i].latencias[j]!=0)) {
                    prioridades[j][k].second += prior(i,j,k);
                    interesados[j][k].push_back(i);
                }
            }
        }
    }
}

float Controlador::prior(int ep_id, int ch_id, int v_id){ //ENDPOINT, CACHE, VIDEO
    float res = (pow(endpoints[ep_id].latencia_center,1.0) * pow(endpoints[ep_id].peticiones_video[v_id],2.0)) /
                (pow(endpoints[ep_id].latencias[ch_id],2.0) * pow(endpoints[ep_id].ncaches,0.0));
    return res;
}
