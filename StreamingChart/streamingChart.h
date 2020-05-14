//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHART_H
#define WET1_STREAMINGCHART_H

#include "list.h"
#include "streamingChartNode.h"
#include "AVLTree.h"

typedef ListNode<StreamingChartNode*>* ChartNode;
typedef ListNode<StreamingChartNodeZero*>* ChartZero;
typedef ListNode<StreamingChartNodeTree*>* ChartTree;

typedef StreamingChartNode* DataChart;
typedef StreamingChartNodeZero* DataZero;
typedef StreamingChartNodeTree* DataTree;

class streamingChart : public List<DataChart>{
private:
    void convertLinkedListToArray(int *artist, int *songs,
                                  List<Song*> *src, int size);
public:
    streamingChart();
    ~streamingChart() = default; //todo: do we need this?

    void getBestSongs(int* artists, int* songs, int amountOfSongs);

    ChartNode pushStreamsLast(int numOfStreams);
    ChartNode pushStreamsNode(int numOfStreams, ChartNode afterNode);
    void** pushNewArtist(int artistID, int numOfSongs);

    void* addToSongInZero(ListNode<Song *>* song, int artistID, int songID,
                        int numOfStreams);
    void* addToSong(ChartNode currentChart, int artistID, int songID,
                    int numOfStreams);

    friend std::ostream& operator<<(std::ostream& os, streamingChart& list);
};

#endif //WET1_STREAMINGCHART_H
