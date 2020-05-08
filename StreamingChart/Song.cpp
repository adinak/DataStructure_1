//
// Created by Aviv9 on 08/05/2020.
//

#include "Song.h"
#include "streamingChart.h"

Song::Song(int artistID, int songID, StreamingChartNode *chart_node) :
        artist_id(artistID), song_id(songID), chart_node(chart_node) {}

StreamingChartNode *Song::getChartNode() {
    return this->chart_node;
}

int Song::getSongID() {
    return this->song_id;
}

int Song::getArtistID() {
    return this->artist_id;
}

void Song::setChartNode(StreamingChartNode *new_chart_node) {
    this->chart_node = new_chart_node;
}
