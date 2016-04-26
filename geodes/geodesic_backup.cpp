///Author Adarsh Verghese
///Keep comments for debugging

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// this is to calculate the geodesic distance later
#include <math.h>
#include <stdio.h>

#define pi 3.14159265358979323846

double deg2rad(double);
double rad2deg(double);
double difference_start[30000],difference_end[30000];

double distance1(double lat1, double lon1, double lat2, double lon2, char unit) {
  double theta, dist;
  theta = lon1 - lon2;
  dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;
  switch(unit) {
    case 'M': // miles
      break;
    case 'K': //kilometers, choose whatever you want
      dist = dist * 1.609344;
      break;
  }
  return (dist);
}


/* This function converts decimal degrees to radians*/

double deg2rad(double deg) {
  return (deg * pi / 180);
}


/*  This function converts radians to decimal degrees */

double rad2deg(double rad) {
  return (rad * 180 / pi);
}



int main()
{
      string testline;
      vector<string> word;
      string testline2;
      vector<string> word2;
      char M = 'K';
  
      ifstream Test ( "cal_cnode.txt" );

      if (!Test)
      {
          cout << "There was an error opening the file.\n";
          return 0;
      }

      //store words in vector
      while( Test>>testline )
              word.push_back(testline);


      // multiples of 3 from 0 are index number +1 = lat +1 = long
      //    0   -121.904167   41.974556

      /*cout<<word[0]<<"("<<0<<")"<<endl;
      cout<<word[1]<<"("<<1<<")"<<endl;
      cout<<word[2]<<"("<<2<<")"<<endl;
      cout<<word[30]<<"("<<30<<")"<<endl;*/

      ifstream Test2 ( "myFile.txt" );
      if (!Test2)
      {
          cout << "There was an error opening the file.\n";
          return 0;
      }      

      while( Test2>>testline2 )
            word2.push_back(testline2);

          //cout<<word2[1]<<"("<<1<<")"<<endl;

      // 37.67512527892127 -121.058349609375 36.58906837139909 -120.399169921875
      // lat long lat long

      /*                                              */
      /*              Calculate the differences       */
      int j =0;
      for (int i =1; i<=word.size(); i++)
      {
        // from start 
        difference_start[j]=distance1(stod(word[i+1]),stod(word[i+2]),stod(word2[1]),stod(word2[0]),M);
        difference_end[j] =distance1(stod(word[i+1]),stod(word[i+2]),stod(word2[3]),stod(word2[2]),M);
        //printf("%f\n",difference_start[j] );
        //cout<<"\nstart "<<stod(word[i+1])<<" "<<stod(word[i+2])<<" "<<stod(word2[1])<<" "<<stod(word2[0]);
        //cout<<"\nend "<<stod(word[i+1])<<" "<<stod(word[i+2])<<" "<<stod(word2[3])<<" "<<stod(word2[2]);
        //cout<<difference_start[j]<<"("<<j<<")"<<endl;
        //cout<<difference_end[j]<<"("<<j<<")"<<endl<<endl;
        //printf("%f (%d)\n", difference_start[j],j);
        j = j+1;
        i = i+2;
      }

      /*                                              */
      /*              find the smallest value         */
      double smallest_start=10000,smallest_end=10000;
      int node_start,node_end;

      for (int i =1;i<=j;i++)
      {
          if(smallest_start > difference_start[i]){
            smallest_start = difference_start[i];
            node_start = i;
            //printf("start%d\n",node_start);
          }

          if(smallest_end > difference_end[i]){
            smallest_end = difference_end[i];
            node_end = i;
            //printf("end%d\n", node_end);
          }
      }
      printf("Start node:   %d\nEnd node:   %d\n", node_start,node_end);


    ofstream myfile3 ("nodes_start_end.txt");
      if (myfile3.is_open())
      {
        myfile3 << node_start;
        myfile3 << '\n';
        myfile3 << node_end;
        myfile3 << '\n';
        myfile3.close();
      }
      else cout << "Unable to open file";
      return 0;
    }