//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChart.h"

/**================================ PRIVATE ================================**/
void streamingChart::increaseTotalNumberOfSongs(int numOfSongs) {
    this->totalNumberOfSongs += numOfSongs;
}

void streamingChart::decreaseTotalNumberOfSongs(int numOfSongs) {
    this->totalNumberOfSongs -= numOfSongs;
}
/**================================ PUBLIC =================================**/
/**      C'TOR       **/
streamingChart::streamingChart() : List<StreamingChartNode *>(),
                                    totalNumberOfSongs(0) { }

/**      GET       **/
int streamingChart::getNumberOfStreams(StreamingChartNode *chartNode) const {
    return chartNode->getNumberOfStreams();
}

int streamingChart::getTotalNumberOfSongs() const {
    return this->totalNumberOfSongs;
}

StreamingChartResult streamingChart::getBestSongs(int *artists, int *songs,
                                                    int amountOfSongs) {
    if(artists == nullptr || songs == nullptr) {
        return CHART_FAIL;
    }
    if(amountOfSongs > this->totalNumberOfSongs) {
        return CHART_NOT_ENOUGH_SONGS;
    }
    //todo: implementation is complicated, saving for last

    return CHART_SUCCESS;
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
    auto* song_list = new List<Song*>;

    for (int i = 0; i < numOfSongs; ++i) {
        auto new_song = new Song(artistID, i);
        song_array[i] = song_list->pushLast(new_song);
    }
    chartZero->getArtistTree()->insert(artistID, *song_list); //todo

    this->increaseTotalNumberOfSongs(numOfSongs);
    return song_array;
}

StreamingChartNode *
streamingChart::pushSong(int artistID, int songID, int numOfStreams) {
    for(List<StreamingChartNode*>::Iterator itr = this->beginFront();
        !(itr == this->end()); ++itr) {
        if(this->getNumberOfStreams((*itr)->getData()) == numOfStreams) {
            (*itr)->getData()->pushSong(artistID, songID);
            return (*itr)->getData();
        }
    }
    StreamingChartNode* newChart = this->pushStreamsChart(numOfStreams);
    newChart->pushSong(artistID, songID);
    return newChart;
}

/**      POP       **/
void streamingChart::popArtist(int artistID) {
    for(List<StreamingChartNode*>::Iterator itr = this->beginFront();
        !(itr == this->end()); ++itr) {

        if(this->getNumberOfStreams((*itr)->getData()) == 0) {
            auto* chart_zero = dynamic_cast<StreamingChartNodeZero*>
                                ((*itr)->getData());
            List<Song*>* song_list = chart_zero->getArtistTree()->find(artistID);
            if(song_list != nullptr){
                int length = song_list->getLength();
                song_list->clearList();
                this->decreaseTotalNumberOfSongs(length);
            }

        } else {
            auto* chartNode = dynamic_cast<StreamingChartNodeTree*>
                                ((*itr)->getData());

        }

    }
}



















