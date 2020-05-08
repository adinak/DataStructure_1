//
// Created by Aviv9 on 08/05/2020.
//

#ifndef AVLTREE_SONG_H
#define AVLTREE_SONG_H


#include "streamingChartNode.h"


class Song {
private:
    int artist_id;
    int song_id;
    StreamingChartNode* chart_node;
public:
    Song(int artistID, int songID, StreamingChartNode *chart_node= nullptr);
    ~Song() = default;
    int getArtistID();
    int getSongID();
    StreamingChartNode* getChartNode();
    void setChartNode(StreamingChartNode *new_chart_node);
};


#endif //AVLTREE_SONG_H
