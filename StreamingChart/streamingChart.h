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
    void convertListToArray(int *artist, int *songs, List<Song*> *src,
            int size);
public:
    /**
     * Creates a new music chart list
     */
    streamingChart();

    /**
     * Destroy music chart list
     */
    ~streamingChart();

    /**
     * Fills songs array with the songs id's of songs with the most streams
     * Fills artists array with artist id's respectfully to songs array
     * @param artists
     * @param songs
     * @param amountOfSongs
     */
    void getBestSongs(int* artists, int* songs, int amountOfSongs);

    /**
     * Adds a new stream node with numOfStreams to end of the list
     * @param numOfStreams
     * @return new node added
     */
    ChartNode pushStreamsLast(int numOfStreams);

    /**
     * Adds a new stream node with numOfStreams after specified node
     * @param numOfStreams
     * @param afterNode
     * @return new node added
     */
    ChartNode pushStreamsNode(int numOfStreams, ChartNode afterNode);

    /**
     * Adds songs of new artist to zero node
     * @param artistID
     * @param numOfSongs
     * @return songs array
     */
    void** pushNewArtist(int artistID, int numOfSongs);

    /**
     * Increases amount of streams to specified song which currently has 0
     * streams by adding the song to chart node with 1 streams
     * @param song - pointer to the song node
     * @param artistID
     * @param songID
     * @param numOfStreams
     * @return pointer to new songs location
     */
    void* addToSongInZero(ListNode<Song *>* song, int artistID, int songID,
                        int numOfStreams);

    /**
     * Increases amount of streams to specified song which currently has 1 or
     * more streams by adding the song to chart node with numOfStreams
     * @param currentChart - current location of song
     * @param artistID
     * @param songID
     * @param numOfStreams
     * @return pointer to new songs location
     */
    void* addToSong(ChartNode currentChart, int artistID, int songID,
                    int numOfStreams);

    friend std::ostream& operator<<(std::ostream& os, streamingChart& list);
};

#endif //WET1_STREAMINGCHART_H
