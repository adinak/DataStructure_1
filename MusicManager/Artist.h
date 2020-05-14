//
// Created by Aviv9 on 08/05/2020.
//

#ifndef AVLTREE_ARTIST_H
#define AVLTREE_ARTIST_H

#include "Song.h"

class Artist {
private:
    int artist_id;
    int num_of_songs;
    int* streams;
    void** songs;
public:
    Artist(int artist_ID, int num_of_songs);
    ~Artist();
    int getArtistID();
    int getNumberOfSongs();
    int getStreamsOfSong(int i);
    void * getSong(int i);
    void setSongs(void** ptrArray);
};


#endif //AVLTREE_ARTIST_H
