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
public:
    MusicManager();
    ~MusicManager() = default;

    int getNumberOfSongs() const;
    streamingChart* getMusicChart();
    AVLTree<ArtistID, Artist*>* getArtistTree();

};


#endif //WET1_MUSICMANAGER_H
