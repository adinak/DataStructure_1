//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHART_H
#define WET1_STREAMINGCHART_H

#include "list.h"
#include "streamingChartNode.h"
#include "AVLTree.h"

typedef enum{CHART_SUCCESS, CHART_FAIL,
             CHART_NOT_ENOUGH_SONGS} StreamingChartResult;

class streamingChart : public List<StreamingChartNode*>{
private:
    int totalNumberOfSongs; //todo: will be easier to update from BigData class

    void increaseTotalNumberOfSongs(int numOfSongs);
    void decreaseTotalNumberOfSongs(int numOfSongs);

public:
    streamingChart();
    ~streamingChart() = default;

    int getNumberOfStreams(StreamingChartNode* chartNode) const;
    int getTotalNumberOfSongs() const; //todo
    StreamingChartResult getBestSongs(int* artists, int* songs, int amountOfSongs);

    StreamingChartNode* pushStreamsChart(int numOfStreams);
    void** pushNewArtist(int artistID, int numOfSongs);
    StreamingChartNode* pushSong(int artistID, int songID, int numOfStreams);

    void popArtist(int artistID); //todo: started implementing removeArtist -
                                    // not very efficient
    StreamingChartResult popChartNode(int numOfStreams); //todo: can use list
                                                         //pop function
};


#endif //WET1_STREAMINGCHART_H
