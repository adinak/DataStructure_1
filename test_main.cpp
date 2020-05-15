//
// Created by Adina Katz on 15/05/2020.
//
#include "library1.h"
#include "musicManager.h"
using namespace std;

int main() {
    void* music_manager = Init();
    if(AddArtist(music_manager, 123, 5) == SUCCESS) {
        cout << "Added artist" << endl;
    } else {
        cout << "FAIL!" << endl;
    }
    if(AddToSongCount(music_manager, 123, 6) == INVALID_INPUT) {
        cout << "Song doesn't exist" << endl;
    } else {
        cout << "FAIL!" << endl;
    }
    if(AddToSongCount(music_manager, 123, 4) == SUCCESS) {
        cout << "Added to song count" << endl;
    } else {
        cout << "FAIL!" << endl;
    }
    int streams;
    if(NumberOfStreams(music_manager, 123, 4, &streams) == SUCCESS &&
            streams == 1) {
        cout << "Number of Streams is Correct" << endl;
    } else {
        cout << "FAIL!" << endl;
    }
    if(RemoveArtist(music_manager, 789) == FAILURE) {
        cout << "Artist doesn't exist" << endl;
    } else {
        cout << "FAIL!" << endl;
    }
    Quit(&music_manager);

    return 0;
}
