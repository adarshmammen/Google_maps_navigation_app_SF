#!/bin/sh
MONITORDIR="/home/engineer/Desktop/project_trial"
inotifywait -m -r -e create --format '%w%f' "${MONITORDIR}" | while read NEWFILE
do
        sh run.sh
done