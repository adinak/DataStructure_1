//
// Created by Aviv9 on 08/05/2020.
//

#ifndef AVLTREE_ARTIST_H
#define AVLTREE_ARTIST_H

#include "StreamingChart/Song.h"

class Artist {
private:
    int artist_id;
    int num_of_songs;
    Song** songs;
public:
    Artist(int artist_ID, int num_of_songs);
    ~Artist();
    int getArtistID();
    Song* getSong(int i);
};


#endif //AVLTREE_ARTIST_H
