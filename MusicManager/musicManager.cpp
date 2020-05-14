//
// Created by Adina Katz on 14/05/2020.
//

#include "musicManager.h"

MusicManager::MusicManager() : numberOfSongs(0) {
    this->musicChart = streamingChart();
    this->artistTree = AVLTree<ArtistID, Artist*>();
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




