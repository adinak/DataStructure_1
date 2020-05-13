//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChart.h"
#include "streamingChartNode.h"

/**================================ PRIVATE =================================**/
void streamingChart::convertLinkedListToArray(int *array, List<Song*> *list,
                                              int size, int start) {
    for(List<Song*>::Iterator i = list->beginFront(); !(i == list->end()); ++i){
        size--;
        if(size == 0) {
            break;
        }

    }

}

/**================================ PUBLIC =================================**/
/**      C'TOR       **/
streamingChart::streamingChart() : List<StreamingChartNode *>() { }

/**      GET       **/
int streamingChart::getNumberOfStreams(StreamingChartNode *chartNode) const {
    return chartNode->getNumberOfStreams();
}

void streamingChart::getBestSongs(int *artists, int *songs, int amountOfSongs) {
    for(List<StreamingChartNode*>::Iterator itr = this->beginBack();
        !(itr == this->end()); --itr) {
        int delta = -1;
        if((*itr)->getData()->getNumberOfStreams() == 0) {
            //put list size of amountOfSongs into array
        } else {
            auto* chart_node = dynamic_cast<StreamingChartNodeTree*>
                                ((*itr)->getData());
            if(amountOfSongs <= chart_node->getNumberOfSongs()) {
                //generate list from tree
                //put list size of amountOfSongs into array
                break;
            } else {
                delta = (chart_node->getNumberOfSongs() - amountOfSongs);
                //generate list from tree
                //put list size of chart_node->getNumberOfSongs() into array
                amountOfSongs = delta;
            }
        }
    }
    //todo: make a function that transfers a list into an array

}

/**      PUSH       **/
ListNode<StreamingChartNode*>* streamingChart::pushStreamsChart(int
                                                            numOfStreams) {
    if(numOfStreams == 0) {
        auto* newChartNode = new StreamingChartNodeZero();
        return  this->pushFirst(newChartNode);
    } else {
        auto* newChartNode = new StreamingChartNodeTree(numOfStreams);
        return this->pushLast(newChartNode);
    }
}

void** streamingChart::pushNewArtist(int artistID, int numOfSongs) {
    ListNode<StreamingChartNode*>* chartNode;
    if(this->getHead() == nullptr){
        chartNode = this->pushStreamsChart(0);
    } else {
        chartNode = this->getHead();
    }
    void** song_array = new void*[numOfSongs];
    auto* chartZero =  dynamic_cast<StreamingChartNodeZero*>(chartNode->getData());
    auto song_list = new List<Song*>;

    for (int i = 0; i < numOfSongs; ++i) {
        auto new_song = new Song(artistID, i);
        song_array[i] = song_list->pushLast(new_song);
    }
    chartZero->getArtistTree()->insert(artistID, song_list);
    chartZero->increaseNumOfSongs(numOfSongs);
    return song_array;
}

void*
streamingChart::addToSongInZero(ListNode<Song *>* song, int artistID,
                                int songID, int numOfStreams) {
    auto* chart_zero = dynamic_cast<StreamingChartNodeZero *>(this->getHeadData());
    chart_zero->popSong(artistID, song);
    ListNode<StreamingChartNode*>* list_node = this->getHead()->getNext();
    if(list_node == nullptr) {
        list_node = this->pushStreamsChart(numOfStreams);
    }
    auto next_chart = dynamic_cast<StreamingChartNodeTree *>(this->getHead()->getNext()->getData());
    next_chart->pushSong(artistID, songID);
    return list_node;
}

void*
streamingChart::addToSong(ListNode<StreamingChartNodeTree *>* chart,
        int artistID, int songID, int numOfStreams) {
    StreamingChartNodeTree* chart_node = chart->getData();
    chart_node->popSong(artistID, songID);
    if(chart->getNext() == nullptr) {
        this->pushStreamsChart(numOfStreams);
    }
    chart = chart->getNext();
    chart_node = dynamic_cast<StreamingChartNodeTree*>(chart->getData());
    return chart_node->pushSong(artistID, songID);
}

std::ostream &operator<<(ostream &os, streamingChart &list) {
    for(List<StreamingChartNode*>::Iterator node = list.beginFront();
        !(node == list.end()); ++node) {
        os << "Streams: " << (*node)->getData()->getNumberOfStreams() << " ";
        os << "Songs: " << (*node)->getData()->getNumberOfSongs() << std::endl;
    }
    return os;
}

























