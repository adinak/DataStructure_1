//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHART_H
#define WET1_STREAMINGCHART_H

#include "list.h"
#include "streamingChartNode.h"
#include "AVLTree.h"

typedef enum{CHART_SUCCESS, CHART_FAIL} StreamingChartResult;


class streamingChart {
private:
    List<StreamingChartNode> streamingChartList;
    StreamingChartNode* zero;
    StreamingChartNode* tail;
    StreamingChartNode* current;

    void setZero();
    void setTail();
    void resetCurrent();

public:
    streamingChart();
    ~streamingChart() = default;

    StreamingChartNode* getZero() const;
    StreamingChartNode* getTail() const;
    StreamingChartNode* getNext();
    int getCurrentNumberOfStreams() const;
    AVLTree<int, ArtistID>* getZeroArtists() const;
    AVLTree<int, ArtistID>* getTailArtists() const;
    AVLTree<int, ArtistID>* getCurrentArtists() const;


    //todo:first check if node exists
    StreamingChartResult pushStreamsChart(int numOfStreams);
    //todo: add song with number of streams
    StreamingChartResult pushSong(int artistID, int songID);

    StreamingChartResult popChartNode();

};


#endif //WET1_STREAMINGCHART_H
