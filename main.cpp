#include <gtest/gtest.h>
#include <vector>

#include "dinic.hpp"

using namespace std;

void addEdge(vector<vector<int>>& graph, int u, int v, int w){
  graph[u][v] = w;
}

TEST(Dinic, smallGraph1){

  int v = 6;
  vector<vector<int>> g1(v, vector<int> (6,0));

    addEdge(g1, 0, 1, 10);
    addEdge(g1, 0, 2, 10);
    addEdge(g1, 1, 2, 2);
    addEdge(g1, 1, 3, 4);
    addEdge(g1, 1, 4, 8);
    addEdge(g1, 2, 4, 9);
    addEdge(g1, 3, 5, 10);
    addEdge(g1, 4, 3, 6);
    addEdge(g1, 4, 5, 10);

    int solution = 19;

    EXPECT_EQ(dinic_algorithm(v, g1, 0, 5), solution);

}

TEST(Dinic, smallGraph2){
      int v = 6;
    int s = 5;
    int t = 4;

   vector<vector<int>> g2(v, vector<int> (6,0));
    

    // Source edges
    addEdge(g2, 5, 0, 10);
    addEdge(g2, 5, 1, 10);

    // Sink edges
    addEdge(g2, 2, 4, 10);
    addEdge(g2, 3, 4, 10);

    // Middle edges
    addEdge(g2, 0, 1, 2);
    addEdge(g2, 0, 2, 4);
    addEdge(g2, 0, 3, 8);
    addEdge(g2, 1, 3, 9);
    addEdge(g2, 3, 2, 6);

     int solution = 19;

    EXPECT_EQ(dinic_algorithm(v, g2, 5, 4), solution);

   
}

TEST(Dinic, smallGraph3){
   int v = 6;

   vector<vector<int>> g(v, vector<int>(v, 0));
    addEdge(g, 0, 1, 16);
    addEdge(g, 0, 2, 13);
    addEdge(g, 1, 2, 10);
    addEdge(g, 1, 3, 12);
    addEdge(g, 2, 1, 4);
    addEdge(g, 2, 4, 14);
    addEdge(g, 3, 2, 9);
    addEdge(g, 3, 5, 20);
    addEdge(g, 4, 3, 7);
    addEdge(g, 4, 5, 4);

    int solution = 23;
    EXPECT_EQ(dinic_algorithm(v, g, 0, 5), solution);
}

TEST(Dinic, smallGraph4){
   int v = 6;

   vector<vector<int>> g(v, vector<int>(v, 0));
        addEdge(g,0, 1, 3 );
        addEdge(g, 0, 2, 7 ) ;
        addEdge(g, 1, 3, 9);
        addEdge(g, 1, 4, 9 );
        addEdge(g, 2, 1, 9 );
        addEdge(g, 2, 4, 9);
        addEdge(g, 2, 5, 4);
        addEdge(g, 3, 5, 3);
        addEdge(g, 4, 5, 7 );
        addEdge(g, 0, 4, 10);

    int solution = 14;
    EXPECT_EQ(dinic_algorithm(v, g, 0, 5), solution);
}

TEST(Dinic, bigGraph1){
    int v = 11;
    int s = 10;
    int t = 9;

    vector<vector<int>> g3(v, vector<int> (11,0));

    // Source edges
    addEdge(g3, 10, 0, 5);
    addEdge(g3,10, 1, 10);
    addEdge(g3, 10, 2, 15);

    // Middle edges
    addEdge(g3, 0, 3, 10);
    addEdge(g3, 1, 0, 15);
    addEdge(g3, 1, 4, 20);
    addEdge(g3, 2, 5, 25);
    addEdge(g3,3, 4, 25);
    addEdge(g3,3, 6, 10);
    addEdge(g3,3, 7, 20);
    addEdge(g3,4, 2, 5);
    addEdge(g3, 4, 7, 30);
    addEdge(g3, 5, 7, 20);
    addEdge(g3, 5, 8, 10);
    addEdge(g3, 7, 8, 15);

    // Sink edges
    addEdge(g3, 6, 9, 5);
    addEdge(g3, 7, 9, 15);
    addEdge(g3, 8, 9, 10);

    int solution = 30;

    EXPECT_EQ(dinic_algorithm(v, g3, 10, 9), solution);
}


// Here the source and sink is same
TEST(Dinic, SourceEqualsSink) {
  int v = 3;
  vector<vector<int>> g(v, vector<int>(v, 0));
  
  EXPECT_EQ(dinic_algorithm(v, g, 1, 1), 0);
}
//Here when there ar no edges, meaning the graph is disconnected
TEST(Dinic, noEdges_ZeroFlow) {
  int v = 4;
  vector<vector<int>> g(v, vector<int>(v, 0));
  EXPECT_EQ(dinic_algorithm(v, g, 0, 3), 0);
}
//Here the graph has edges, but no path from the source to sink
TEST(Dinic, disconnected_NoPath) {
  int v = 4;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 5);  
  addEdge(g, 1, 2, 5);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 3), 0);
}
//here we have a graph with a single edge
TEST(Dinic, singleEdge) {
  int v = 2;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 7);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 1), 7);
}
TEST(Dinic, selfLoops_Ignored) {
  int v = 4;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 0, 100); // self-loop should be irrelevant
  addEdge(g, 1, 1, 50);  // self-loop should be irrelevant
  addEdge(g, 0, 2, 6);
  addEdge(g, 2, 3, 4);
  // bottleneck is 4 via 0->2->3; loops don't help
  EXPECT_EQ(dinic_algorithm(v, g, 0, 3), 4);
}

TEST(Dinic, zeroCapacity) {
  int v = 3;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 0);
  addEdge(g, 1, 2, 10);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 2), 0);
}

//This graph over here will need multiple phases
TEST(Dinic, needsMultiplePhasesBackEdges) {
  // s=0, a=1, b=2, c=3, t=4
  int v = 5;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 10);
  addEdge(g, 1, 2, 1);   // tight edge
  addEdge(g, 2, 4, 10);
  addEdge(g, 0, 3, 10);
  addEdge(g, 3, 2, 9);   // most flow must move through 3->2
  // back edges make phases matter
  addEdge(g, 2, 1, 9);

  // Max in to node 2 is 1 (from 1) + 9 (from 3) = 10; out to t is 10.
  EXPECT_EQ(dinic_algorithm(v, g, 0, 4), 10);
}

// since the algorihtm also provides solution to the maximum bipartite matching problem
TEST(Dinic, bipartiteMatching_UnitCaps) {
  // Left: L1=1,L2=2,L3=3 ; Right: R1=4,R2=5,R3=6 ; s=0, t=7
  int v = 8;
  vector<vector<int>> g(v, vector<int>(v, 0));
  // s -> L
  addEdge(g, 0, 1, 1);
  addEdge(g, 0, 2, 1);
  addEdge(g, 0, 3, 1);
  // L -> R (possible matches)
  addEdge(g, 1, 4, 1); // L1-R1
  addEdge(g, 1, 5, 1); // L1-R2
  addEdge(g, 2, 5, 1); // L2-R2
  addEdge(g, 3, 5, 1); // L3-R2
  addEdge(g, 3, 6, 1); // L3-R3
  // R -> t
  addEdge(g, 4, 7, 1);
  addEdge(g, 5, 7, 1);
  addEdge(g, 6, 7, 1);
  // Perfect matching of size 3 exists: (L1-R1), (L2-R2), (L3-R3)
  EXPECT_EQ(dinic_algorithm(v, g, 0, 7), 3);
}

// This tests that residual edges are handled properly
TEST(Dinic, residualReverseEdges_Utilized) {
  // s=0, a=1, b=2, t=3
  int v = 4;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 5);
  addEdge(g, 1, 2, 3); // bottleneck 3
  addEdge(g, 2, 3, 5);
  // explicit reverse capacity (shouldn’t increase max flow)
  addEdge(g, 2, 1, 3);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 3), 3);
}

// this test ensures that the maximum flow algorithm respects the minimum cut property
TEST(Dinic, tightCut_SumToSink) {
  int v = 4; // s=0, a=1, b=2, t=3
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 5);
  addEdge(g, 0, 2, 5);
  addEdge(g, 1, 3, 3);
  addEdge(g, 2, 3, 7);
  // extra cross edges that shouldn't change the cut
  addEdge(g, 1, 2, 100);
  addEdge(g, 2, 1, 100);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 3), 10); // cut {1,2}->3 limits to 3+7
}

TEST(Dinic, multipleParallelConcept_SummedCapacity) {
  // Matrix model can’t store parallel edges separately; simulate by summing.
  // Parallel edges s->a: (2) and (3) => total 5
  int v = 3;
  vector<vector<int>> g(v, vector<int>(v, 0));
  addEdge(g, 0, 1, 5);  // 2 + 3 combined
  addEdge(g, 1, 2, 4);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 2), 4); // limited by 1->2
}

TEST(Dinic, largeIntRange) {
  // Keep totals under INT_MAX to avoid overflow with int capacities
  int v = 4;
  vector<vector<int>> g(v, vector<int>(v, 0));
  const int C = 1'000'000; // 1e6
  addEdge(g, 0, 1, C);
  addEdge(g, 0, 2, C);
  addEdge(g, 1, 3, C);
  addEdge(g, 2, 3, C);
  EXPECT_EQ(dinic_algorithm(v, g, 0, 3), 2 * C);
}



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}