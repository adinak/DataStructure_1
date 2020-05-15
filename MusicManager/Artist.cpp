//
// Created by Aviv9 on 08/05/2020.
//

#include "Artist.h"
#include <iostream>


Artist::Artist(int artist_ID, int num_of_songs): artist_id(artist_ID),
                                                num_of_songs(num_of_songs) {
    this->streams = new int[num_of_songs];
    for(int i = 0; i<num_of_songs; i++){
        streams[i] = 0;
    }
    this->songs = nullptr;
}

Artist::~Artist() {
    delete[] this->songs;
    delete[] this->streams;
}

int Artist::getArtistID() {
    return this->artist_id;
}

void * Artist::getSong(int songID) {
    if(songID >= num_of_songs || songID < 0){
        std::cerr<<"invalid song index"<<std::endl;
        return nullptr;
    }
    return songs[songID];
}

void Artist::setSongs(void **ptrArray) {
    this->songs = ptrArray;
}

int Artist::getStreamsOfSong(int songID) {
    return streams[songID];
}

int Artist::getNumberOfSongs() {
    return this->num_of_songs;
}

void Artist::setPtrToSong(int songID, void* ptr) {
    songs[songID] = ptr;
}

void Artist::setSongStream(int songID) {
    streams[songID]++;
}
