//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHARTNODE_H
#define WET1_STREAMINGCHARTNODE_H

#include "AVLTree.h"
#include "Song.h"

/**================= FATHER =====================**/

class StreamingChartNode{
private:
    const int numberOfStreams;
public:
    StreamingChartNode(int numOfStreams);
    virtual ~StreamingChartNode() = 0;

    virtual void pushSong(int artistID, int songID) = 0;
    virtual void pushArtist(int artistID) = 0;
    virtual void popSong(int artistID, int songID) = 0;
    virtual void popArtist(int artistID) = 0;
    int getNumberOfStreams() const;
};

/**================ ZERO NODE ==================**/

class StreamingChartNodeZero : public StreamingChartNode {
private:
    AVLTree<int, List<Song*>> songChart;
public:
    StreamingChartNodeZero(int numOfStreams);
    ~StreamingChartNodeZero();

    void pushSong(int artistID, int songID);
    void pushArtist(int artistID);

    void popSong(int artistID, int songID); //todo: do we need this?
    void popSong(int artistID, ListNode<Song*>* songNode);
    void popArtist(int artistID);
};
/**================ TREE NODE ==================**/

class StreamingChartNodeTree : public StreamingChartNode{
private:
    AVLTree<int, AVLTree<int, Song*>> songChart;
public:
    StreamingChartNodeTree(int numOfStreams);
    ~StreamingChartNodeTree();

    void pushSong(int artistID, int songID);
    void pushArtist(int artistID);

    void popSong(int artistID, int songID);
    void popArtist(int artistID);
};


#endif //WET1_STREAMINGCHARTNODE_H
