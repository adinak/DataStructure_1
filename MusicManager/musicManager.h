//
// Created by Adina Katz on 14/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "streamingChart.h"
#include "Artist.h"

typedef int ArtistID;

class MusicManager {
private:
    int numberOfSongs;
    streamingChart musicChart;
    AVLTree<ArtistID, Artist*> artistTree;

    void updateNumberOfSongs(int num);

public:
    MusicManager();
    ~MusicManager() = default;

    /**
     * @return total number of songs in music manager
     */
    int getNumberOfSongs() const;

    /**
     * @return pointer to streaming chart list
     */
    streamingChart* getMusicChart();

    /**
     * @return pointer to artist tree
     */
    AVLTree<ArtistID, Artist*>* getArtistTree();

    /**
     * Adds a new artist to the artists tree and adds all the artist songs to
     * the streaming chart
     * @param artistID
     * @param numOfSongs
     */
    void addArtist(int artistID, int numOfSongs);

    /**
     * Deletes artist from artists tree and deletes all of the artist songs
     * from the streaming chart
     * @param artistID
     */
    void removeArtist(int artistID);

    /**
     * Increases songID streams by:
     * - increasing number of streams in streams[songID]
     * - moving the song from current node in music chart to next node
     * @param artistID
     * @param songID
     */
    void addToSongCount(int artistID, int songID);
};


#endif //WET1_MUSICMANAGER_H
