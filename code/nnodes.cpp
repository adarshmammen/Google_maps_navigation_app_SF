#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

int main()
{
      string testline;
      vector<string> word;
      string testline2;
      vector<string> word2;
      vector<string>word3;
      
  
      ifstream Test ( "cal_edges.txt" );

      if (!Test)
      {
          cout << "There was an error opening the file.\n";
          return 0;
      }

      //store words in vector
      while( Test>>testline )
              word.push_back(testline);


	ifstream Test2 ( "nodes_start_end.txt" );
      		if (!Test2)
      {
          cout << "There was an error opening the file.\n";
          return 0;
      }      

      while( Test2>>testline2 )
            word2.push_back(testline2);
	    string v =word2[0];
		cout<<endl<<v;
	int size1 = word.size();
	int sizet = (size1/4);
	

	for (int i=0;i<=sizet-1;i++)
	{


		int temp1 =(4*i)+1;
		int temp2 =(4*i)+2;


	if (word[temp1] == v)
	{		
	
	int h =temp1+1;

	string g = word[h];
	word3.push_back(g);
	
	
	}
	if(word[temp2]==v)
	{
	int h =temp1-1;
	
	string g1 = word[h];
	word3.push_back(g1);
	
	}
}

	int check=word3.size();
	cout<<endl<<check;
	//cout<<endl<<word3[2];
	//ofstream myfile3 ("neigh_node.txt");
      ofstream output_file("neigh_node.txt");
	
	
		ostream_iterator<string> output_iterator(output_file, "\n");
    copy(word3.begin(), word3.end(), output_iterator);

        	//myfile3 << '\n';
        	

 	
   //   else cout << "Unable to open file";

return(0);
}

