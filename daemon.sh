#!/bin/bash
MONITORDIR="/home/engineer/Desktop/project_trial"
myfile="/home/engineer/Desktop/project_trial/myFile.txt"
inotifywait -m -r -e create --format '%w%f' "${MONITORDIR}" | while read file
do
	if [ "$file" = "$myfile" ]; then
        sh run.sh
        echo "The file '$file' appeared" 
    else
    
    	echo "nope $file = $myfile "
    fi
    
done
