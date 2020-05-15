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
    this->updateNumberOfSongs(numOfSongs);
}

void MusicManager::removeArtist(int artistID) {
    Artist* artist = *(this->getArtistTree()->find(artistID));
    int streams;
    DataZero zero;
    List<Song*>* ptr_list;
    DataTree ptr_node_tree;
    ListNode<Song*>* ptr_song_zero;
    int n = artist->getNumberOfSongs();

    for (int i = 0; i < n; ++i) {
        streams = artist->getStreamsOfSong(i);
        if(streams == 0) {
            ptr_song_zero = static_cast<ListNode<struct Song *> *>(artist->getSong(i));
            zero = dynamic_cast<DataZero>(this->getMusicChart()->getHeadData());
            ptr_list = *(zero->getArtistTree()->find(artistID));
            ptr_list->popNode(ptr_song_zero);
        } else {
            ptr_node_tree = static_cast<DataTree>(artist->getSong(i));
            ptr_node_tree->popSong(artistID, i);
        }
    }
    this->updateNumberOfSongs(-n);
}

void MusicManager::addToSongCount(int artistID, int songID) {
    Artist* artist = *(this->getArtistTree()->find(artistID));
    int streams = artist->getStreamsOfSong(songID);
    streamingChart* chart = this->getMusicChart();
    void* new_ptr;
    if(streams == 0) {
        auto* song = static_cast<ListNode<struct Song *> *>(artist->getSong(songID));
        new_ptr = chart->addToSongInZero(song, artistID, songID, streams+1);
        artist->setPtrToSong(artistID, new_ptr);
    } else {
        auto chart_node = static_cast<ChartNode>(artist->getSong(songID));
        new_ptr = chart->addToSong(chart_node, artistID, songID, streams+1);
        artist->setPtrToSong(artistID, new_ptr);
    }
    artist->setSongStream(songID);
}

void MusicManager::updateNumberOfSongs(int num) {
    this->numberOfSongs += num;
}






