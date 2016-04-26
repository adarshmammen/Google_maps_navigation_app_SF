/************************************************************************/
/* $Id: MainP.cpp 65 2010-09-08 06:48:36Z yan.qi.asu $                                                                 */
/************************************************************************/
#include <time.h>
#include <limits>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstdio>
#include <iostream>
#include "GraphElements.h"
#include "Graph.h"
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.h"


using namespace std;

void testYenAlg(int source, int dest, int k)
{
	Graph my_graph("data/cal_edges");

	YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex(source),
		my_graph.get_vertex(dest));

    freopen("output.txt","w",stdout);
    for(int i = 0; i<k; i++){
        yenAlg.next()->PrintOut(cout);
	}
}

int main()
{

  string testline;
  vector<string> word;
  ifstream Test ( "nodes_start_end.txt" );

  if (!Test)
  {
      cout << "There was an error opening the file.\n";
      return 0;
  }
  //store words in vector

    while( Test>>testline ){ word.push_back(testline);}
    int source = atoi(word[0].c_str());
    int dest = atoi(word[1].c_str());
    int k = 3;
    testYenAlg(source, dest, k);

    //freopen("output.txt","w",stdout);


    /*
    int n = 21048;
    int m=500;//how many calls to YenAlg to avg
    float times[m];
    float avg = 0;
    int k = 3;
    for (int i = 0;i<m;i++){
        int source = rand() % n + 1;
        int dest = rand() % n + 1;
        clock_t t1,t2;
        t1=clock();
        testYenAlg(source, dest, k);
        t2=clock();
        float diff ((float)t2-(float)t1);
        diff = diff/CLOCKS_PER_SEC;
        //cout<<i<<" YenAlg time from "<<source<<" to "<<dest<<" took "<<diff<<" seconds."<<endl;
        cout<<diff<<endl;
        times[i] = diff;
        avg += diff/m;
    }

    float sdev = 0;
    float min = 100;
    float max = 0;
    for (int i = 0; i<m; i++){
        sdev += (times[i]-avg)*(times[i]-avg);
        if(times[i]<min){min = times[i];}
        if(times[i]>max){max = times[i];}
    }
    float var = sdev/m;
    float sd = sqrt(var);
    float cv = (sd/avg)*100;

    cout<<"avg time: "<<avg<<endl;
    cout<<"min time: "<<min<<endl;
    cout<<"max time: "<<max<<endl;
    cout<<"std time: "<<sd<<endl;
    cout<<"Coefficient of Variation: "<<cv<<endl;*/
}
