//
// Created by Adina Katz on 13/05/2020.
//

#ifndef WET1_TEST_STREAMINGCHART_H
#define WET1_TEST_STREAMINGCHART_H

#include "streamingChart.h"
#include "streamingChartNode.h"

using namespace std;

class TestStreamingChart {
    streamingChart streams_list;
    void **artist1;
    void **artist2;
    void **artist3;
    void **artist4;
    void **artist5;
public:
    void test_addingNodes();
    void test_addingArtist();
    void test_addingSongs();
    void test_chart();

    TestStreamingChart() = default;
    ~TestStreamingChart() = default;

};

void TestStreamingChart::test_addingNodes() {
    cout << "num of nodes " << streams_list.getLength() << endl;
    for(int i = 0; i < 10; i++) {
        streams_list.pushStreamsChart(i);
    }
    cout << streams_list;

}

void TestStreamingChart::test_addingArtist() {
    artist1 = streams_list.pushNewArtist(12, 5);
    artist2 = streams_list.pushNewArtist(13, 7);

    cout << streams_list;
}

void TestStreamingChart::test_addingSongs() {
    auto* song = (ListNode<Song*>*)artist2[6];
    artist2[6] = streams_list.addToSongInZero(song, 13, 6, 1);

    cout << streams_list;

    auto* song1 = (ListNode<StreamingChartNodeTree*>*)artist2[6];
    streams_list.addToSong(song1, 13, 6, 2);

    cout << streams_list;
}

void TestStreamingChart::test_chart() {
    for(int i = 0; i < 5; i++) {
        streams_list.pushNewArtist(i, i+10);
    }
    cout << streams_list;


}

#endif //WET1_TEST_STREAMINGCHART_H
