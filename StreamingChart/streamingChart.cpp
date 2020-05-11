//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChart.h"

/**================================ PRIVATE ================================**/
/**      SET       **/
void streamingChart::setZero(StreamingChartNode *newZero) {
    this->zero = newZero;
}

void streamingChart::setTail(StreamingChartNode *newChartTail) {
    this->tail = newChartTail;
}

void streamingChart::resetCurrent(ChartDirection direction) {
    if(direction == CHART_FRONT) {
        this->current = this->zero;
    } else if(direction == CHART_BACK) {
        this->current = this->tail;
    }
}

/**================================ PUBLIC =================================**/
/**      C'TOR       **/
streamingChart::streamingChart() : streamingChartList(), zero(nullptr),
                                    tail(nullptr), current(nullptr){ }

/**      GET       **/
StreamingChartNode *streamingChart::getZero() const {
    return this->zero;
}

StreamingChartNode *streamingChart::getTail() const {
    return this->tail;
}

StreamingChartNode *streamingChart::getNext() {
    if(this->current == nullptr) {
        this->resetCurrent(CHART_FRONT);
    }
    StreamingChartNode* current_chart_node = this->current;
    this->current = this->streamingChartList.getNextData();
    return current_chart_node;
}

StreamingChartNode *streamingChart::getPrev() {
    if(this->current == nullptr) {
        this->resetCurrent(CHART_BACK);
    }
    StreamingChartNode* current_chart_node = this->current;
    this->current = this->streamingChartList.getPrevData();
    return current_chart_node;
}

int streamingChart::getCurrentNumberOfStreams() const {
    return this->current->getNumberOfStreams();
}

StreamingChartResult streamingChart::getBestSongs(int *artists, int *songs,
                                                    int amountOfSongs) {
    if(artists == nullptr || songs == nullptr) {
        return CHART_FAIL;
    }
    if(amountOfSongs > this->totalNumberOfSongs) {
        return CHART_NOT_ENOUGH_SONGS;
    }
    //todo: implementation is complicated, saving for last

    return CHART_SUCCESS;
}









