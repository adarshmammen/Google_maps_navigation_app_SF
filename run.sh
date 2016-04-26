
#while inotifywait -e close_write myFile.txt; 
#do
./geodesic
./nnodes
#mv nodes_start_end.txt kshortestpaths/.
#cd kshortestpaths
#./kshortestpaths_2.1
#mv output.txt ../nodes_for_xml.txt
#cd ..
#./project_algo # this is for dijkstra
python createXML.py

cp latlong.xml /var/www/html/.

#cp spath.html /var/www/html/.
rm myFile.txt #nodes_start_end.txt neigh_node.txt latlong.xml 
#rm spath.html

#sudo chmod 777 /var/www/html/spath.html
sudo chmod 777 /var/www/html/latlong.xml
#sudo chmod 777 /var/www/html/latlong2.xml
#sudo chmod 777 /var/www/html/latlong3.xml

chromium-browser http://localhost/neighbours.html
#chromium-browser http://localhost/spath2.html
#chromium-browser http://localhost/spath3.html

#done;