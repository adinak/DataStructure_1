//
// Created by Adina Katz on 08/05/2020.
//

#include "streamingChart.h"


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





