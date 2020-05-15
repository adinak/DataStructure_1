//
// Created by Adina Katz on 14/05/2020.
//

#include "musicManager.h"

MusicManager::MusicManager() : numberOfSongs(0) {
    this->musicChart = streamingChart();
    this->artistTree = AVLTree<ArtistID, Artist*>();
}

MusicManager::~MusicManager() {
    List<Artist*> list_to_delete;
    this->artistTree.getTreeToList(IN,&list_to_delete);
    List<Artist*>::Iterator i = list_to_delete.beginFront();
    for(;!(i == list_to_delete.end()); ++i){
        Artist* d = (*i)->getData();
        delete d;
    }
}

int MusicManager::getNumberOfSongs() const {
    return this->numberOfSongs;
}

streamingChart *MusicManager::getMusicChart() {
    return &this->musicChart;
}

AVLTree<ArtistID, Artist *> *MusicManager::getArtistTree() {
    return &this->artistTree;
}

void MusicManager::addArtist(int artistID, int numOfSongs) {
    void** ptr_array = this->getMusicChart()->pushNewArtist(artistID, numOfSongs);
    auto* new_artist = new Artist(artistID, numOfSongs);
    new_artist->setSongs(ptr_array);
    this->getArtistTree()->insert(artistID, new_artist);
}

void MusicManager::removeArtist(int artistID) {
    AVLTree<ArtistID, Artist*>* tree = this->getArtistTree();
    Artist* artist = *(tree->find(artistID));
    int streams;
    void* song_ptr;
    for (int i = 0; i < artist->getNumberOfSongs(); ++i) {
        streams = artist->getStreamsOfSong(i);
        if(streams == 0) {

        } else {

        }
    }
}






