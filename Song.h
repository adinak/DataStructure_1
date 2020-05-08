//
// Created by Aviv9 on 08/05/2020.
//

#ifndef AVLTREE_SONG_H
#define AVLTREE_SONG_H


#include "StreamingChart/streamingChart.h"

class Song {
private:
    int artist_id;
    int song_id;
    streamingChartNode* chart_node;
public:
    Song(int artistID, int songID, streamingChartNode *chart_node= nullptr);
    ~Song() = default;
    int getArtistID();
    int getSongID();
    streamingChartNode* getChartNode();
    void setChartNode(streamingChartNode *new_chart_node);
};


#endif //AVLTREE_SONG_H
