//
// Created by Adina Katz on 13/05/2020.
//

#ifndef WET1_TEST_STREAMINGCHART_H
#define WET1_TEST_STREAMINGCHART_H

#include "streamingChart.h"

using namespace std;

class TestStreamingChart {
    streamingChart streams_list;
public:
    void test_addingNodes();
    void test_addingArtist();
    void test_addingSongs();
    void test_deleteNode();
    void test_deleteArtist();
    void test_deleteSongs();

    TestStreamingChart() = default;
    ~TestStreamingChart() = default;

};

void TestStreamingChart::test_addingNodes() {
    cout << "num of nodes" << streams_list.getLength() << endl;
    for(int i = 0; i < 10; i++) {
        streams_list.pushStreamsChart(i);
    }
    cout << streams_list;

}

void TestStreamingChart::test_addingArtist() {

}

void TestStreamingChart::test_addingSongs() {

}

void TestStreamingChart::test_deleteNode() {

}

void TestStreamingChart::test_deleteArtist() {

}

void TestStreamingChart::test_deleteSongs() {

}


#endif //WET1_TEST_STREAMINGCHART_H
