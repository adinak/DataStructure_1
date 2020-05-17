//
// Created by Adina Katz on 07/05/2020.
//

#ifndef WET1_STREAMINGCHARTNODE_H
#define WET1_STREAMINGCHARTNODE_H

#include "AVLTree.h"
#include "list.h"
#include "Song.h"

/**================= FATHER =====================**/
/**
 * Polymorphic class
 */
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
    void increaseNumOfSongs(int num = 1);
    void decreaseNumOfSongs(int num = 1);
};

/**================ ZERO NODE ==================**/
/**
 * Son class of StreamingChartNode.
 * Inherits the private section and implements all the virtual functions.
 * This is the data section of the first node in the music chart list.
 * It is different from the rest of the nodes because it contains an AVL Tree
 * of Linked List.
 */
class StreamingChartNodeZero : public StreamingChartNode {
private:
    AVLTree<int, List<Song*>*> songChart;
public:
    /**
     * Creates the Data section of the first List Node.
     * The numberOfStreams variable is set to 0 by default.
     * @param numOfStreams
     */
    StreamingChartNodeZero(int numOfStreams = 0);

    /**
     * Destroys the Data section in the first List Node.
     * The destructor starts by deleting all the linked lists in the AVL Tree
     * and finally deletes the AVL Tree.
     */
    ~StreamingChartNodeZero() override;

    /**
     * @return a pointer to the songChart AVL Tree
     */
    AVLTree<int, List<Song*>*>* getArtistTree();

    /**
     * This function isn't used. It remains for polymorphism reasons.
     * The function that preforms the relevant action is pushNewArtist() in
     * streamingChart.h
     * @param artistID
     * @param songID
     * @return nullptr
     */
    void* pushSong(int artistID, int songID) override ;

    /**
     * This function isn't used. It remains for polymorphism reasons.
     * The function that preforms the relevant action is pushNewArtist() in
     * streamingChart.h
     * @param artistID
     */
    void pushArtist(int artistID) override;

    /**
     * This function isn't used. It remains for polymorphism reasons.
     * @param artistID
     * @param songID
     */
    void popSong(int artistID, int songID) override ;

    /**
     * Deletes a List Node object from the Linked List of the relevant artist
     * @param artistID
     * @param songNode - pointer to the List Node containing the song that
     * will be deleted
     */
    void popSong(int artistID, ListNode<Song*>* songNode);

    /**
     * Removes the artist from the AVL Tree songChart, after deleting all the
     * artists songs from the list (if exist), and deleting the list.
     * @param artistID
     */
    void popArtist(int artistID) override;
};
/**================ TREE NODE ==================**/
/**
 * Son class of StreamingChartNode.
 * Inherits the private section and implements all the virtual functions.
 * This is the data section of music chart list.
 * This data section contains an AVL Tree artists the contains AVL Trees of
 * the artist songs.
 */
class StreamingChartNodeTree : public StreamingChartNode{
private:
    AVLTree<int, AVLTree<int, Song*>*> songChart;
public:
    /**
     * Creates a new Data section of ListNode in the music chart.
     * The numberOfStreams variable is initialized with numOfStreams
     * that's passed passed.
     * @param numOfStreams
     */
    StreamingChartNodeTree(int numOfStreams);

    /**
     * Destroys the Data section in the List Node object of music chart list.
     * The destructor deletes each AVL Tree of songs of each artist and then
     * deletes the artist AVL Tree.
     */
    ~StreamingChartNodeTree() override;

    /**
     * @return a pointer to the songChart AVL Tree
     */
    AVLTree<int, AVLTree<int, Song*>*>* getArtistTree();

    /**
     * Adds a song to the relevant AVL Tree, according to the key artistID.
     * @param artistID
     * @param songID
     * @return pointer to the ListNode object in which the song was added to.
     */
    void* pushSong(int artistID, int songID) override;

    /**
     * Adds an artist to the songChart AVL Tree.
     * At this point the artist has no songs in it's songs AVL Tree.
     * @param artistID
     */
    void pushArtist(int artistID) override;

    /**
     * Removes a song from the relevant AVL Tree according to the key artistID.
     * @param artistID
     * @param songID
     */
    void popSong(int artistID, int songID) override;

    /**
     * Removes the artist from the AVL Tree songChart, after deleting all the
     * artists songs from the AVL Tree (if exist).
     * @param artistID
     */
    void popArtist(int artistID) override;
};


#endif //WET1_STREAMINGCHARTNODE_H
