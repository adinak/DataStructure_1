//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChartNode.h"

/**================= FATHER =====================**/

int StreamingChartNode::getNumberOfStreams() const {
    return this->numberOfStreams;
}

int StreamingChartNode::getNumberOfSongs() const {
    return this->numberOfSongs;
}

void StreamingChartNode::increaseNumOfSongs() {
    this->numberOfSongs++;
}

void StreamingChartNode::decreaseNumOfSongs() {
    this->numberOfSongs--;
}


/**================ ZERO NODE ==================**/
/**      C'TOR & D'TOR       **/
StreamingChartNodeZero::StreamingChartNodeZero(int numOfStreams) {
    this->numberOfStreams = numOfStreams;
}

StreamingChartNodeZero::~StreamingChartNodeZero() {
    this->songChart.clear();
}

/**      PUSH       **/
void* StreamingChartNodeZero::pushSong(int artistID, int songID) {
    List<Song*>* temp_list = *(this->songChart.find(artistID));
    if(temp_list == nullptr) {
        this->pushArtist(artistID);
        temp_list = *(this->songChart.find(artistID));
    }
    this->increaseNumOfSongs();
    auto new_song = new Song(artistID, songID);
    return temp_list->pushLast(new_song);
}

void StreamingChartNodeZero::pushArtist(int artistID) {
    auto new_list = new List<Song*>();
    this->songChart.insert(artistID, new_list);
}

/**      POP       **/
void StreamingChartNodeZero::popArtist(int artistID) {
    this->songChart.remove(artistID);
}

void StreamingChartNodeZero::popSong(int artistID, ListNode<Song*>* songNode) {
    List<Song*>** temp_list = this->songChart.find(artistID);
    (*temp_list)->popNode(songNode);
    if((*temp_list)->getLength() == 0) {
        this->popArtist(artistID);
    }
    this->decreaseNumOfSongs();
}

AVLTree<int, List<Song *>*> *StreamingChartNodeZero::getArtistTree() {
    return &(this->songChart);
}

void StreamingChartNodeZero::popSong(int artistID, int songID) {
    List<Song*>* temp_list = (*this->songChart.find(artistID));

    for (List<Song*>::Iterator itr = temp_list->beginFront();
            !(itr == temp_list->end()); ++itr) {
        if((*itr)->getData()->getSongID() == songID) {
            temp_list->popNode((*itr));
        }
    }
    this->decreaseNumOfSongs();
}


/**================ TREE NODE ==================**/
/**      C'TOR & D'TOR       **/
StreamingChartNodeTree::StreamingChartNodeTree(int numOfStreams) {
    this->numberOfStreams = numOfStreams;
}

StreamingChartNodeTree::~StreamingChartNodeTree() {
    this->songChart.clear();
}

/**      PUSH       **/
void* StreamingChartNodeTree::pushSong(int artistID, int songID) {
    AVLTree<int, Song*>* temp_tree = this->songChart.find(artistID);
    if(temp_tree == nullptr) {
        this->pushArtist(artistID);
        temp_tree = this->songChart.find(artistID);
    }
    auto new_song = new Song(artistID, songID);
    temp_tree->insert(songID,new_song);
    this->increaseNumOfSongs();

    void* ptr = static_cast<void*>(this);
    return ptr;
}

void StreamingChartNodeTree::pushArtist(int artistID) {
    auto* new_tree = new AVLTree<int, Song*>();
    this->songChart.insert(artistID, *new_tree);
}

/**      POP       **/
void StreamingChartNodeTree::popSong(int artistID, int songID) {
    AVLTree<int, Song*>* temp_tree = this->songChart.find(artistID);
    temp_tree->remove(songID);
    if(temp_tree->getSize() == 0) {
        this->popArtist(artistID);
    }
    this->decreaseNumOfSongs();
}

void StreamingChartNodeTree::popArtist(int artistID) {
    this->songChart.remove(artistID);
}

AVLTree<int, AVLTree<int, Song *>> *StreamingChartNodeTree::getArtistTree() {
    return &(this->songChart);
}






