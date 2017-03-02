//
// Created by anibal on 23/02/17.
//

#ifndef GHCCR_ENDPOINT_H
#define GHCCR_ENDPOINT_H

#include <vector>

using namespace std;

class Endpoint {
public:
    vector<int> latencias;
    vector<int> peticiones_video;
    int id;
    int latencia_center;
    int ncaches;

    Endpoint (int ident, int latencia_c, vector<int> lat_caches, int nvideos, int ncaches){
        id= ident;
        latencia_center= latencia_c;
        latencias= lat_caches;

        peticiones_video.resize(nvideos);

        this->ncaches = ncaches;

        for (int i= 0; i < nvideos; i++){
            peticiones_video[i]= 0;
        }
    }

    void aniadirPeticionVideo (int nvideo, int npeticiones){
        if(peticiones_video[nvideo]!=-1)
            peticiones_video[nvideo]+= npeticiones;
        else
            peticiones_video[nvideo]= npeticiones;
    }



};


#endif //GHCCR_ENDPOINT_H
