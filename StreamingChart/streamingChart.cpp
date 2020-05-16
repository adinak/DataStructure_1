//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChart.h"
#include "streamingChartNode.h"


/**================================ PRIVATE =================================**/
void streamingChart::convertListToArray(int *artist, int *songs,
                                        List<Song*> *src, int size) {
    int j = 0;
    for(List<Song*>::Iterator i = src->beginFront();
        !(i == src->end()) && (size > 0); ++i, j++) {
        size--;
        artist[j] = (*i)->getData()->getArtistID();
        songs[j] = (*i)->getData()->getSongID();
    }
}

/**================================ PUBLIC =================================**/
/**      C'TOR       **/
streamingChart::streamingChart() : List<DataChart>() {}

/**      D'TOR       **/
streamingChart::~streamingChart() {
    for(Iterator i = this->beginFront();!(i == this->end());++i){
        DataChart d = (*i)->getData();
        delete d;
    }
}

/**      GET       **/
void streamingChart::getBestSongs(int *artists, int *songs, int amountOfSongs) {
    int n = amountOfSongs;

    class DoSomething {
    private:
    public:
        DoSomething() = default;
        ~DoSomething() = default;

        void operator()(AVLTree<int, Song*>* tree, int &n, List<Song*>* list) {
            tree->getTreeToList(IN, list, n);
        }
        void operator()(List<Song*>* src, int &n, List<Song*>* dst) {
            for(List<Song*>::Iterator i = src->beginFront();
            !(i == src->end()) && (n > 0); ++i) {
                dst->pushLast((*i)->getData());
                n--;
            }
        }
    };
    DoSomething function;
    List<Song*> list_dst;

    for(List<DataChart>::Iterator itr = this->beginBack();
        !(itr == this->end()) && (n > 0); --itr) {

        if((*itr)->getData()->getNumberOfStreams() == 0) {
            auto* chart_node = dynamic_cast<DataZero>((*itr)->getData());
            chart_node->getArtistTree()->doSomethingInOrder(function, n,
                                                            &list_dst);
        } else {
            auto* chart_node = dynamic_cast<DataTree>((*itr)->getData());
            chart_node->getArtistTree()->doSomethingInOrder(function, n,
                    &list_dst);
        }
    }
    this->convertListToArray(artists, songs, &list_dst, amountOfSongs);
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

ChartNode streamingChart::pushStreamsNode(int numOfStreams,
        ChartNode afterNode) {
    auto* newChartNode = new StreamingChartNodeTree(numOfStreams);
    return this->pushNode(afterNode, newChartNode);
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
    if(chart_zero == nullptr) {
        return nullptr;
    }
    chart_zero->popSong(artistID, song);
    ChartNode next_node = this->getHead()->getNext();
    if(next_node == nullptr) {
        next_node = this->pushStreamsLast(numOfStreams);
    } else if(next_node->getData()->getNumberOfStreams() != numOfStreams) {
        next_node = this->pushStreamsNode(numOfStreams, this->getHead());
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
        delete data_node;
        this->popNode(currentChart);
    }
    data_node = dynamic_cast<DataTree>(next_chart->getData());
    data_node->pushSong(artistID, songID);
    return next_chart;
}

std::ostream &operator<<(ostream &os, streamingChart &list) {
    for(List<DataChart>::Iterator node = list.beginFront();
        !(node == list.end()); ++node) {
        os << "Streams: " << (*node)->getData()->getNumberOfStreams() << " ";
        os << "Songs: " << (*node)->getData()->getNumberOfSongs() << std::endl;
    }
    return os;
}





























