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

void StreamingChartNode::increaseNumOfSongs(int num) {
    this->numberOfSongs += num;
}

void StreamingChartNode::decreaseNumOfSongs(int num) {
    this->numberOfSongs -= num;
}


/**================ ZERO NODE ==================**/
/**      C'TOR & D'TOR       **/
StreamingChartNodeZero::StreamingChartNodeZero(int numOfStreams) {
    this->numberOfStreams = numOfStreams;
    this->numberOfSongs = 0;
}

StreamingChartNodeZero::~StreamingChartNodeZero() {
    List<List<Song*>*> tmp_list;
    this->getArtistTree()->getTreeToList(IN, &tmp_list);
    List<Song*> list_to_delete;
    for(List<List<Song*>*>::Iterator song_list = tmp_list.beginFront();
            !(song_list == tmp_list.end()); ++song_list) {
        for(List<Song*>::Iterator song = (*song_list)->getData()->beginFront();
            !(song == (*song_list)->getData()->end()); ++song){
            delete (*song)->getData();
        }
        delete (*song_list)->getData();
    }
}

/**      PUSH       **/
void* StreamingChartNodeZero::pushSong(int artistID, int songID) {
//    List<Song*>* temp_list = *(this->songChart.find(artistID));
//    if(temp_list == nullptr) {
//        this->pushArtist(artistID);
//        temp_list = *(this->songChart.find(artistID));
//    }
//    this->increaseNumOfSongs();
//    auto new_song = new Song(artistID, songID);
//    return temp_list->pushLast(new_song);
}//TODO:delete if not nessecery

void StreamingChartNodeZero::pushArtist(int artistID) {}
//TODO:delete if not nessecery

/**      POP       **/
void StreamingChartNodeZero::popArtist(int artistID) {
    this->songChart.remove(artistID);
}

void StreamingChartNodeZero::popSong(int artistID, ListNode<Song*>* songNode) {
    List<Song*>** temp_list = this->songChart.find(artistID);
    if(temp_list != nullptr) {
        (*temp_list)->popNode(songNode);
        if ((*temp_list)->getLength() == 0) {
            this->popArtist(artistID);
        }
        this->decreaseNumOfSongs();
    }
}

AVLTree<int, List<Song *>*> *StreamingChartNodeZero::getArtistTree() {
    return &(this->songChart);
}

void StreamingChartNodeZero::popSong(int artistID, int songID) {
    List<Song*>** temp_list = this->songChart.find(artistID);
    if(temp_list != nullptr) {
        for (List<Song *>::Iterator itr = (*temp_list)->beginFront();
             !(itr == (*temp_list)->end()); ++itr) {
            if ((*itr)->getData()->getSongID() == songID) {
                (*temp_list)->popNode((*itr));
            }
        }
    }
    this->decreaseNumOfSongs();
}


/**================ TREE NODE ==================**/
/**      C'TOR & D'TOR       **/
StreamingChartNodeTree::StreamingChartNodeTree(int numOfStreams) {
    this->numberOfStreams = numOfStreams;
    this->numberOfSongs = 0;
}

StreamingChartNodeTree::~StreamingChartNodeTree() {
    List<AVLTree<int,Song*>*> tmp_list;
    List<Song*> list_to_delete;
    this->getArtistTree()->getTreeToList(IN,&tmp_list);
    List<AVLTree<int,Song*>*>::Iterator i = tmp_list.beginFront();
    for(;!(i==tmp_list.end()); ++i){
        (*i)->getData()->getTreeToList(IN, &list_to_delete);
        delete (*i)->getData();
    }
    List<Song*>::Iterator j = list_to_delete.beginFront();
    for(;!(j==list_to_delete.end()); ++j){
        Song* d =  (*j)->getData();//to verify that we delete Song*
        delete d;
    }
}

/**      PUSH       **/
void* StreamingChartNodeTree::pushSong(int artistID, int songID) {
    if(this->numberOfSongs == 0) {
        this->pushArtist(artistID);
    }
    AVLTree<int, Song*>* temp_tree = *(this->songChart.find(artistID));
    if (temp_tree == nullptr) {
        this->pushArtist(artistID);
        temp_tree = *(this->songChart.find(artistID));
    }
    auto new_song = new Song(artistID, songID);
    temp_tree->insert(songID, new_song);
    this->increaseNumOfSongs();

    void* ptr = this;
    return ptr;
}

void StreamingChartNodeTree::pushArtist(int artistID) {
    auto new_tree = new AVLTree<int, Song*>();
    this->songChart.insert(artistID, new_tree);
}

/**      POP       **/
void StreamingChartNodeTree::popSong(int artistID, int songID) {
    AVLTree<int, Song*>** temp_tree = this->songChart.find(artistID);
    if(temp_tree != nullptr) {
        (*temp_tree)->remove(songID);
        if ((*temp_tree)->getSize() == 0) {
            this->popArtist(artistID);
        }
        this->decreaseNumOfSongs();
    }
}

void StreamingChartNodeTree::popArtist(int artistID) {
    this->songChart.remove(artistID);
}

AVLTree<int, AVLTree<int, Song*>*> *StreamingChartNodeTree::getArtistTree() {
    return &(this->songChart);
}






