//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChart.h"

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
StreamingChartNode* streamingChart::pushStreamsChart(int numOfStreams) {
    if(numOfStreams == 0) {
        auto* newChartNode = new StreamingChartNodeZero();
        this->pushFirst(newChartNode);
        return newChartNode;
    } else {
        auto* newChartNode = new StreamingChartNodeTree(numOfStreams);
        this->pushLast(newChartNode);
        return newChartNode;
    }
}

void** streamingChart::pushNewArtist(int artistID, int numOfSongs) {
    StreamingChartNode* chartNode;
    if(this->getHead() == nullptr){
        chartNode = this->pushStreamsChart(0);
    } else {
        chartNode = this->getHeadData();
    }
    chartNode->pushArtist(artistID);
    void** song_array = new void*[numOfSongs];
    auto* chartZero =  dynamic_cast<StreamingChartNodeZero*>(chartNode);
    auto song_list = new List<Song*>;

    for (int i = 0; i < numOfSongs; ++i) {
        auto new_song = new Song(artistID, i);
        song_array[i] = song_list->pushLast(new_song);
    }
    chartZero->getArtistTree()->insert(artistID, song_list);
    return song_array;
}

void*
streamingChart::addToSongInZero(ListNode<Song *>* song, int artistID,
        int songID, int numOfStreams) {
    auto* chart_zero = dynamic_cast<StreamingChartNodeZero *>(this->getHeadData());
    chart_zero->popSong(artistID, song);
    if(this->getHead()->getNext() == nullptr) {
        this->pushStreamsChart(numOfStreams);
    }
    StreamingChartNode* next_chart = this->getHead()->getNext()->getData();
    return next_chart->pushSong(artistID, songID);
}

void*
streamingChart::addToSong(ListNode<StreamingChartNodeTree *>* chart,
        int artistID, int songID, int numOfStreams) {
    auto* chart_node = dynamic_cast<StreamingChartNodeTree*>(chart->getData());
    chart_node->popSong(artistID, songID);
    if(chart->getNext() == nullptr) {
        this->pushStreamsChart(numOfStreams);
    }
    chart = chart->getNext();
    chart_node = dynamic_cast<StreamingChartNodeTree*>(chart->getData());
    return chart_node->pushSong(artistID, songID);
}
























