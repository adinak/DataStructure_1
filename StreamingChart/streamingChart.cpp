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
streamingChart::streamingChart() : List<DataChart>() { }

/**      GET       **/
int streamingChart::getNumberOfStreams(StreamingChartNode *chartNode) const {
    return chartNode->getNumberOfStreams();
}

void streamingChart::getBestSongs(int *artists, int *songs, int amountOfSongs) {
    for(List<DataChart>::Iterator itr = this->beginBack();
        !(itr == this->end()); --itr) {
        int delta = -1;
        if((*itr)->getData()->getNumberOfStreams() == 0) {
            //put list size of amountOfSongs into array
        } else {
            auto* chart_node = dynamic_cast<DataTree>((*itr)->getData());
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
ChartNode streamingChart::pushStreamsLast(int numOfStreams) {
    if(numOfStreams == 0) {
        auto* newChartNode = new StreamingChartNodeZero();
        return  this->pushFirst(newChartNode);
    } else {
        auto* newChartNode = new StreamingChartNodeTree(numOfStreams);
        return this->pushLast(newChartNode);
    }
}

ChartNode streamingChart::pushStreamsNode(int numOfStreams, //todo
        ChartNode afterNode) {
    auto* newChartNode = new StreamingChartNodeTree(numOfStreams);
    return this->pushNode(afterNode,
            reinterpret_cast<ListNode<struct StreamingChartNode *> *>(newChartNode));
}

void** streamingChart::pushNewArtist(int artistID, int numOfSongs) {
    ChartNode chartNode;
    if(this->getHead() == nullptr){
        chartNode = this->pushStreamsLast(0);
    } else {
        chartNode = this->getHead();
    }
    void** song_array = new void*[numOfSongs];
    auto* chartZero =  dynamic_cast<DataZero>(chartNode->getData());
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
    auto* chart_zero = dynamic_cast<DataZero>(this->getHeadData());
    chart_zero->popSong(artistID, song);
    ChartNode next_node = this->getHead()->getNext();
    if(next_node == nullptr) {
        next_node = this->pushStreamsLast(numOfStreams);
    }
    auto next_chart = dynamic_cast<DataTree>(next_node->getData());
    next_chart->pushSong(artistID, songID);
    return next_node;
}

void*
streamingChart::addToSong(ChartNode currentChart, int artistID, int songID,
                          int numOfStreams) {
    auto data_node = dynamic_cast<DataTree>(currentChart->getData());
    data_node->popSong(artistID, songID);
    ChartNode next_chart = currentChart->getNext();

    if(next_chart == nullptr ) {
        next_chart = this->pushStreamsLast(numOfStreams);
    } else if(next_chart->getData()->getNumberOfStreams() != numOfStreams) {
        next_chart = this->pushStreamsNode(numOfStreams, currentChart);
    }

    if(data_node->getNumberOfSongs() == 0) {
        this->popNode(reinterpret_cast<ListNode<DataChart> *>(currentChart)); //todo
    }
    data_node = dynamic_cast<DataTree>(next_chart->getData());

    return data_node->pushSong(artistID, songID);
}

std::ostream &operator<<(ostream &os, streamingChart &list) {
    for(List<DataChart>::Iterator node = list.beginFront();
        !(node == list.end()); ++node) {
        os << "Streams: " << (*node)->getData()->getNumberOfStreams() << " ";
        os << "Songs: " << (*node)->getData()->getNumberOfSongs() << std::endl;
    }
    return os;
}



























