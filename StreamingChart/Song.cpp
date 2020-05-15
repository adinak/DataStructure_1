//
// Created by Aviv9 on 08/05/2020.
//

#include "Song.h"

Song::Song(int artistID, int songID) : artist_id(artistID), song_id(songID) {}

int Song::getSongID() {
    return this->song_id;
}

int Song::getArtistID() {
    return this->artist_id;
}

