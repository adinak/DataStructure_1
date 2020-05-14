//
// Created by Adina Katz on 14/05/2020.
//

#include "library1.h"
#include "musicManager.h"

void *Init() {
    MusicManager* new_manager = new MusicManager();
    return new_manager;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if(DS == nullptr || numOfSongs <= 0 || artistID <= 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    if(music_manager->getArtistTree()->find(artistID) != nullptr) {
        return FAILURE;
    }
    music_manager->addArtist(artistID, numOfSongs);
    return SUCCESS;
}

StatusType RemoveArtist(void *DS, int artistID) {
    if(DS == nullptr || artistID <= 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    Artist* artist = *(music_manager->getArtistTree()->find(artistID));
    if(artist == nullptr) {
        return FAILURE;
    }

    return SUCCESS;
}





