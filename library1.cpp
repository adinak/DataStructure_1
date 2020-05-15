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
    Artist** artist = music_manager->getArtistTree()->find(artistID);
    if(artist == nullptr) {
        return FAILURE;
    }
    music_manager->removeArtist(artistID);
    return SUCCESS;
}

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if(DS == nullptr || artistID <= 0 || songID < 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    Artist* artist = *(music_manager->getArtistTree()->find(artistID));
    if(artist == nullptr) {
        return FAILURE;
    }
    if(songID >= artist->getNumberOfSongs()) {
        return INVALID_INPUT;
    }
    music_manager->addToSongCount(artistID, songID);
    return SUCCESS;
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if(DS == nullptr || songID < 0 || artistID <= 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    Artist* artist = *(music_manager->getArtistTree()->find(artistID));
    if(artist == nullptr) {
        return FAILURE;
    }
    if(songID >= artist->getNumberOfSongs()) {
        return INVALID_INPUT;
    }
    *streams = artist->getStreamsOfSong(songID);
    return SUCCESS;
}

StatusType
GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    if(DS == nullptr) {
        return INVALID_INPUT;
    }
    if(numOfSongs <= 0) {
        return ALLOCATION_ERROR;
    }
    auto* music_manager = (MusicManager*)DS;
    if(numOfSongs > music_manager->getNumberOfSongs()) {
        return FAILURE;
    }
    music_manager->getMusicChart()->getBestSongs(artists, songs, numOfSongs);
    return SUCCESS;
}

void Quit(void **DS) {
    auto* music_manager = (MusicManager*)DS;
    delete music_manager;
}










