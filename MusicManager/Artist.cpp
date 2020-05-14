//
// Created by Aviv9 on 08/05/2020.
//

#include "Artist.h"
#include <iostream>


Artist::Artist(int artist_ID, int num_of_songs): artist_id(artist_ID),
                                                num_of_songs(num_of_songs) {
    this->streams = new int[num_of_songs]();
}

Artist::~Artist() {
    delete this->songs;
    delete this->streams;
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

void Artist::setSongs(void **ptrArray) {
    this->songs = ptrArray;
}

int Artist::getStreamsOfSong(int i) {
    return streams[i];
}

int Artist::getNumberOfSongs() {
    return this->num_of_songs;
}
