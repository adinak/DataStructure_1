//
// Created by Adina Katz on 14/05/2020.
//

#include "library1.h"
#include "musicManager.h"
using std::bad_alloc;

void *Init() {
    MusicManager *new_manager;
    try {
        new_manager = new MusicManager();
    }
    catch (...) {
        new_manager = nullptr;
    }
    return (void *) new_manager;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if(DS == nullptr || numOfSongs <= 0 || artistID <= 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    if(music_manager->getArtistTree()->find(artistID) != nullptr) {
        return FAILURE;
    }
    try {
        music_manager->addArtist(artistID, numOfSongs);
    }
    catch (bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
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
    try {
        music_manager->removeArtist(artistID);
    }
    catch (bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if(DS == nullptr || artistID <= 0 || songID < 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    Artist** artist = (music_manager->getArtistTree()->find(artistID));
    if(artist == nullptr) {
        return FAILURE;
    }
    if(songID >= (*artist)->getNumberOfSongs()) {
        return INVALID_INPUT;
    }
    try {
        music_manager->addToSongCount(artistID, songID);
    }
    catch (bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if(DS == nullptr || songID < 0 || artistID <= 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    Artist** artist = music_manager->getArtistTree()->find(artistID);
    if(artist == nullptr) {
        return FAILURE;
    }
    if(songID >= (*artist)->getNumberOfSongs()) {
        return INVALID_INPUT;
    }
    try {
        *streams = (*artist)->getStreamsOfSong(songID);
    }
    catch (bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType
GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    if(DS == nullptr || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    auto* music_manager = (MusicManager*)DS;
    if(numOfSongs > music_manager->getNumberOfSongs()) {
        return FAILURE;
    }
    try {
        music_manager->getMusicChart()->getBestSongs(artists, songs, numOfSongs);
    }
    catch (bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void **DS) {
    MusicManager* music_manager = (MusicManager*)*DS;
    delete music_manager;
    *DS = nullptr;
}










