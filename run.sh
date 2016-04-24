#while inotifywait -e close_write myFile.txt; 
#do
./geodesic
./project_algo
python createXML.py
rm myFile.txt nodes_for_xml.txt nodes_start_end.txt
#done;