//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHARTNODE_H
#define WET1_STREAMINGCHARTNODE_H

#include "AVLTree.h"
#include "artistID.h"

typedef enum {CHART_ZERO, NOT_CHART_ZERO} NodeType;

class StreamingChartNode{
private:
    int numberOfStreams;
    NodeType type; //todo: do i need this?
    AVLTree<int, ArtistID>* artistTree;
public:
    StreamingChartNode(int numOfStreams);
    ~StreamingChartNode();

    int getNumberOfStreams();
    NodeType getNodeType(); //todo: do i need this?

};


#endif //WET1_STREAMINGCHARTNODE_H
