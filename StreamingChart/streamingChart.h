//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHART_H
#define WET1_STREAMINGCHART_H

#include "list.h"
#include "streamingChartNode.h"
#include "AVLTree.h"

class streamingChart : public List<StreamingChartNode*>{
private:
    void convertLinkedListToArray(int *array, List<Song*>* list, int size,
            int start);
public:
    streamingChart();
    ~streamingChart() = default;

    int getNumberOfStreams(StreamingChartNode* chartNode) const;
    void getBestSongs(int* artists, int* songs, int amountOfSongs);

    StreamingChartNode* pushStreamsChart(int numOfStreams);
    void** pushNewArtist(int artistID, int numOfSongs);
    void* addToSongInZero(ListNode<Song *>* song, int artistID, int songID,
                        int numOfStreams);
    void* addToSong(ListNode<StreamingChartNodeTree*>* chart, int artistID,
                    int songID, int numOfStreams);
    friend std::ostream& operator<<(std::ostream& os, const
    List<StreamingChartNode*>& list);

};

//todo: do we need popArtist()? if so better to implement in StreamingChartNode

#endif //WET1_STREAMINGCHART_H
