//
// Created by Aviv9 on 08/05/2020.
//

#ifndef AVLTREE_ARTIST_H
#define AVLTREE_ARTIST_H

#include "Song.h"

class Artist {
private:
    int artist_id;
    int num_of_songs;
    int* streams;
    void** songs;


public:
    Artist(int artist_ID, int num_of_songs);
    ~Artist();

    /**
     * @return artist id
     */
    int getArtistID();

    /**
     * @return the number of songs artist has
     */
    int getNumberOfSongs();

    /**
     * Retrieves the number of streams a certain song has
     * @param songID
     * @return number of streams songID has
     */
    int getStreamsOfSong(int songID);

    /**
     * Retrieves the ptr of songID
     * if the song has 0 streams the pointer is to type ListNode<Song*>
     * else the pointer is to type ListNode<StreamingChartTree*>*
     * @param songID
     * @return pointer to ListNode in music chart that contains the song
     */
    void * getSong(int songID);

    /**
     * Assigns an array of type void* to songs
     * @param ptrArray
     */
    void setSongs(void** ptrArray);

    /**
     * Assigns a new pointer to songID in songs array
     * @param songID
     * @param ptr
     */
    void setPtrToSong(int songID, void* ptr);

    /**
     * Increases the number of streams of songID by 1
     * @param songID
     */
    void setSongStream(int songID);
};


#endif //AVLTREE_ARTIST_H
