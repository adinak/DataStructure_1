//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHART_H
#define WET1_STREAMINGCHART_H

#include "list.h"
#include "streamingChartNode.h"
#include "AVLTree.h"

typedef enum{CHART_SUCCESS, CHART_FAIL} StreamingChartResult;
typedef enum{CHART_FRONT, CHART_BACK} ChartDirection;

class streamingChart {
private:
    List<StreamingChartNode> streamingChartList; //TODO:aviv - there is no such object, need to be StreamingChartNode*
    StreamingChartNode* zero;
    StreamingChartNode* tail;
    StreamingChartNode* current;

    void setZero(StreamingChartNode* newZero);
    void setTail(StreamingChartNode* newChartTail);
    void resetCurrent(ChartDirection direction);

public:
    streamingChart();
    ~streamingChart() = default;

    StreamingChartNode* getZero() const;
    StreamingChartNode* getTail() const;
    StreamingChartNode* getNext();
    StreamingChartNode* getPrev();
    int getCurrentNumberOfStreams() const;
    void getBestSongs(int* artists, int* songs, int amountOfSongs);

    StreamingChartResult initializeCurrentToNode(StreamingChartNode* chartNode);
    //todo:first check if node exists
    StreamingChartResult pushStreamsChart(int numOfStreams);
    //call when first time adding an artist
    void** pushNewArtist(int artistID, int numOfSongs);
    StreamingChartResult pushChartNode(int numOfStreams);
    //todo: add song with number of streams
    StreamingChartNodeTree* pushSong(int artistID, int songID,
                                        int numOfStreams);

    StreamingChartResult popSong(int artistID, int songID);
    StreamingChartResult popSong(ListNode<Song>* songNode);
    StreamingChartResult popChartNode(int numOfStreams);

};


#endif //WET1_STREAMINGCHART_H
