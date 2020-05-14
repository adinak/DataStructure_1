//
// Created by Aviv9 on 08/05/2020.
//

#include "Artist.h"
#include <iostream>


Artist::Artist(int artist_ID, int num_of_songs): artist_id(artist_ID),
                                                num_of_songs(num_of_songs) {
    this->songs = new void*[num_of_songs];
}

Artist::~Artist() {
    delete this->songs;
}

int Artist::getArtistID() {
    return this->artist_id;
}

void * Artist::getSong(int i) {
    if(i>=num_of_songs||i<0){
        std::cerr<<"invalid song index"<<std::endl;
        return nullptr;
    }
    return songs[i];
}
