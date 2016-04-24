//============================================================================
// Name        : dijkstra_yen_pq.cpp
// Author      : Software Engineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : dijkstra_pq.cpp
// Author      : Silvia Ionescu
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <list>
#include <fstream>
#include <time.h>
#include <limits> // for numeric_limits
#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <map>
using namespace std;

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef vector<vector<neighbor> > adjacency_list_t;
typedef pair<weight_t, vertex_t> weight_vertex_pair_t;

void DijkstraComputePaths(vertex_t source,
                          const adjacency_list_t &adjacency_list,
                          vector<weight_t> &min_distance,
                          vector<vertex_t> &previous)
{
    int n = adjacency_list.size();

    min_distance.clear();

    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);

    // we use greater instead of less to turn max-heap into min-heap
    priority_queue<weight_vertex_pair_t,
			vector<weight_vertex_pair_t>,
			greater<weight_vertex_pair_t> > vertex_queue;

    // makes a pair without us telling it what type of variables :) #cute
    vertex_queue.push(make_pair(min_distance[source], source));


    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.top().first;
        vertex_t u = vertex_queue.top().second;
        vertex_queue.pop();

	// Because we leave old copies of the vertex in the priority queue
	// (with outdated higher distances), we need to ignore it when we come
	// across it again, by checking its distance against the minimum distance
	if (dist > min_distance[u])
	    continue;

        // Visit each edge exiting u
	const vector<neighbor> &neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
	    if (distance_through_u < min_distance[v]) {
	        min_distance[v] = distance_through_u;
	        previous[v] = u;
	        vertex_queue.push(std::make_pair(min_distance[v], v));

	    }

        }
    }
}


list<vertex_t> DijkstraGetShortestPathTo(
    vertex_t vertex, const vector<vertex_t> &previous)
{
    list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
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
      while( Test>>testline )
              word.push_back(testline);

          printf("%d\n",stoi(word[0]) );
          printf("%d\n",stoi(word[1]) );


    
	int starting = stoi(word[0]);
	int ending = stoi(word[1]);

	// read from the text file
    ifstream fileReader;
    //string file = "graaf.txt";
    string file = "cal_edges.txt";
    fileReader.open(file.c_str());

    // check if file exists (try opening it)
    if(!fileReader.is_open()){
    	cout << "Can't open: " << file << endl;
    	return 1;
    }
    //read(fileReader);

    // n is the total number of nodes
    // m is the total line-link number
    int n, m;
    fileReader >> n;
    fileReader >> m;

    adjacency_list_t adjacency_list(m);
    int index, start,stop;
    double weight;


    for (int i=0; i< m; i++)
    {
    	fileReader >> index;
    	fileReader >> start;
    	fileReader >> stop;
    	fileReader >> weight;

    	// add to adjacency list both ways - undirected graph
    	adjacency_list[start].push_back(neighbor(stop, weight));
    	adjacency_list[stop].push_back(neighbor(start, weight));

    }

	clock_t t1,t2;
	t1 = clock();

    vector<weight_t> min_distance;
    vector<vertex_t> previous;
    map<weight_t, list<vertex_t>> store_lists;

    DijkstraComputePaths(starting, adjacency_list, min_distance, previous);
    //cout << "Distance: " << min_distance[ending] << std::endl;
    list<vertex_t> path = DijkstraGetShortestPathTo(ending, previous);
    //cout << "Path : " << endl;


    for (list<vertex_t>::const_iterator it = path.begin(); it != path.end() ; ++it)
    {
    	int node = *it;
    	//cout<<"Node:"<< node << endl;

    	vector<neighbor> &ref = adjacency_list[*it];
    	int size = ref.size();
    	//cout<<"Size1:"<< size<<endl;
    	vector<neighbor>::iterator pt = ref.begin();

    	for ( int i = 0; i < size; ++i)
    	{

    		int next_node = *(++it);
    		//cout<<"next_node:" << next_node<<endl;

    		if(pt->target == next_node)
    		{

    			vertex_t adj_target = pt->target;
    			weight_t adj_weight = pt->weight;

    			// calculate distance form beginning to where the pointer is
    			int a = distance(ref.begin(), pt);
    			//cout << a << endl;

    			// erase the node link
    			ref.erase(ref.begin() + a);
    			//cout <<"Size2:"<< ref.size() << endl;

    			// compute the Dijkstra, distance, and list
    			DijkstraComputePaths(starting, adjacency_list, min_distance, previous);
    			//cout << "Distance: " << min_distance[ending] << std::endl;
    			list<vertex_t> path_var = DijkstraGetShortestPathTo(ending, previous);


    			// store in map<distance, list>
    			store_lists[min_distance[ending]] = path_var;

    			// push values back in the adj_list
    			ref.push_back(neighbor(adj_target, adj_weight));
    		}
    		else
    			++pt;
    		--it;
    	}

    	//cout<<" "<<endl;

    }

    // Print first shortest path

    copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, "->"));
    cout << endl;
    cout <<"************************" << endl;

    // make a map iterator

    map<weight_t, list<vertex_t>> :: const_iterator iter = store_lists.begin();
    list<vertex_t> path2 = iter->second;
    copy(path2.begin(), path2.end(), std::ostream_iterator<vertex_t>(std::cout, "->"));
    cout << endl;
    cout <<"************************" << endl;

    ++iter;

    list<vertex_t> path3 = iter->second;
    copy(path3.begin(), path3.end(), std::ostream_iterator<vertex_t>(std::cout, "->"));
    cout << endl;
    cout <<"************************" << endl;

	t2 = clock();
	float diff((float)t2 - (float)t1);
	diff = diff/CLOCKS_PER_SEC;
	cout<< "YenAlg time from "<< starting << " to " << ending << " took " <<diff <<" sec "<<endl;



    ofstream myfile3 ("nodes_for_xml.txt");
          if (myfile3.is_open())
          {
            copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(myfile3, ","));
            myfile3 << '\n';
            copy(path2.begin(), path2.end(), std::ostream_iterator<vertex_t>(myfile3, ","));
            myfile3 << '\n';
            copy(path3.begin(), path3.end(), std::ostream_iterator<vertex_t>(myfile3, ","));

            /*myfile3 << path.begin();
            myfile3 << '\n';
            myfile3 << path2.end();
            myfile3 << '\n'; */
            myfile3.close();
          }
          else cout << "Unable to open file";




    return 0;
}
