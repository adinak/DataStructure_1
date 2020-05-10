//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChartNode.h"

/**================= FATHER =====================**/

int StreamingChartNode::getNumberOfStreams() const {
    return this->numberOfStreams;
}

StreamingChartNode::StreamingChartNode(int numOfStreams)
        : numberOfStreams(numOfStreams){
}


/**================ ZERO NODE ==================**/
/**      C'TOR & D'TOR       **/
StreamingChartNodeZero::StreamingChartNodeZero(int numOfStreams)
        : StreamingChartNode(numOfStreams) { }

StreamingChartNodeZero::~StreamingChartNodeZero() {
    this->songChart.clear();
}

/**      PUSH       **/
void StreamingChartNodeZero::pushSong(int artistID, int songID) {
    List<Song*>* temp_list = this->songChart.find(artistID);
    if(temp_list == nullptr) {
        this->pushArtist(artistID);
        temp_list = this->songChart.find(artistID);
    }
    auto* new_song = new Song(artistID, songID, this); //todo: problem
    temp_list->pushLast(new_song);
}

void StreamingChartNodeZero::pushArtist(int artistID) {
    auto* new_list = new List<Song*>();
    this->songChart.insert(artistID, *new_list);
}

/**      POP       **/
void StreamingChartNodeZero::popArtist(int artistID) {
    this->songChart.remove(artistID);
}

void StreamingChartNodeZero::popSong(int artistID, ListNode<Song*>* songNode) {
    List<Song*>* temp_list = this->songChart.find(artistID);
    temp_list->popNode(songNode);
}

/**================ TREE NODE ==================**/
/**      C'TOR & D'TOR       **/
StreamingChartNodeTree::StreamingChartNodeTree(int numOfStreams)
        : StreamingChartNode(numOfStreams) { }

StreamingChartNodeTree::~StreamingChartNodeTree() {
    this->songChart.clear();
}

/**      PUSH       **/
void StreamingChartNodeTree::pushSong(int artistID, int songID) {
    AVLTree<int, Song*>* temp_tree = this->songChart.find(artistID);
    if(temp_tree == nullptr) {
        this->pushArtist(artistID); //todo: would be more efficient to return
                                    // pointer-- need to implement in tree
        temp_tree = this->songChart.find(artistID);
    }
    auto* new_song = new Song(artistID, songID, this);
    temp_tree->insert(new_song);
}

void StreamingChartNodeTree::pushArtist(int artistID) {
    auto* new_tree = new AVLTree<int, Song*>();
    this->songChart.insert(artistID, *new_tree);
}

/**      POP       **/
void StreamingChartNodeTree::popSong(int artistID, int songID) {
    AVLTree<int, Song*>* temp_tree = this->songChart.find(artistID);
    temp_tree->remove(songID);
}

void StreamingChartNodeTree::popArtist(int artistID) {
    this->songChart.remove(artistID);
}




