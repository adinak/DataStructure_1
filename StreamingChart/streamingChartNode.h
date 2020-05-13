//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHARTNODE_H
#define WET1_STREAMINGCHARTNODE_H

#include "AVLTree.h"
#include "list.h"
#include "Song.h"

/**================= FATHER =====================**/

class StreamingChartNode{
protected:
    int numberOfStreams;
    int numberOfSongs;
public:
    virtual ~StreamingChartNode() {};

    virtual void* pushSong(int artistID, int songID) = 0;;
    virtual void pushArtist(int artistID) = 0;

    virtual void popSong(int artistID, int songID) = 0;
    virtual void popArtist(int artistID) = 0;

    int getNumberOfStreams() const;
    int getNumberOfSongs() const;
    void increaseNumOfSongs();
    void decreaseNumOfSongs();
};

/**================ ZERO NODE ==================**/

class StreamingChartNodeZero : public StreamingChartNode {
private:
    AVLTree<int, List<Song*>*> songChart;
public:
    StreamingChartNodeZero(int numOfStreams = 0);
    ~StreamingChartNodeZero() override;

    AVLTree<int, List<Song*>*>* getArtistTree();

    void* pushSong(int artistID, int songID) override ;
    void pushArtist(int artistID) override;

    void popSong(int artistID, int songID) override ;
    void popSong(int artistID, ListNode<Song*>* songNode);
    void popArtist(int artistID) override;
};
/**================ TREE NODE ==================**/

class StreamingChartNodeTree : public StreamingChartNode{
private:
    AVLTree<int, AVLTree<int, Song*>> songChart;
public:
    StreamingChartNodeTree(int numOfStreams);
    ~StreamingChartNodeTree() override;

    AVLTree<int, AVLTree<int, Song*>>* getArtistTree();

    void* pushSong(int artistID, int songID) override;
    void pushArtist(int artistID) override;

    void popSong(int artistID, int songID) override;
    void popArtist(int artistID) override;
};


#endif //WET1_STREAMINGCHARTNODE_H
