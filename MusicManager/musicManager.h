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
    ~MusicManager();

    int getNumberOfSongs() const;
    streamingChart* getMusicChart();
    AVLTree<ArtistID, Artist*>* getArtistTree();

    void addArtist(int artistID, int numOfSongs);
    void removeArtist(int artistID);
    void addToSongCount(int artistID, int songID);

};


#endif //WET1_MUSICMANAGER_H
