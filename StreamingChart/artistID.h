//
// Created by Adina Katz on 08/05/2020.
//

#ifndef WET1_ARTISTID_H
#define WET1_ARTISTID_H

#include "AVLTree.h"
#include "Song.h"

class ArtistID{
private:
    int artistID;
    int numberOfSongsInTree;
    AVLTree<int, Song> songs;

public:
    ArtistID(int artistId);
    ~ArtistID();

    bool isEmpty() const;
    bool isSongInTree(int songId) const;

    int getArtistID() const;
    int getNumberOfSongsInTree() const;

    void pushSong(int songID); //todo: need to check that song is in range
    void popSong(int songId); //todo: need to check that song exists
};

#endif //WET1_ARTISTID_H
