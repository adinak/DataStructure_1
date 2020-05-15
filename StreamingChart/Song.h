//
// Created by Aviv9 on 08/05/2020.
//

#ifndef AVLTREE_SONG_H
#define AVLTREE_SONG_H


class Song {
private:
    int artist_id;
    int song_id;
public:
    Song(int artistID, int songID);
    ~Song() = default;

    /**
     * @return artist_id
     */
    int getArtistID();

    /**
     * @return song_id
     */
    int getSongID();
};


#endif //AVLTREE_SONG_H
