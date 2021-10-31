#!/bin/bash

DATAPATH=$1 # no spaces!
CITY=$2
#YEAR=$3

Og=`pwd` #recording original directory where script is run
#echo $Og


cd $DATAPATH
CITYFILE="$DATAPATH/`grep -i -l -m 2 $CITY *`" # - m 2
echo $CITYFILE

if [[ "x$CITYFILE" == "x$DATAPATH/" ]]; then
	echo "City $CITY not found, exiting"
	exit 1
fi
#//make a temporary directory that is deleted end of script
mkdir $Og/SmhiCleaner/CleanerOutputs
cd $Og/SmhiCleaner/CleanerOutputs

$Og/SmhiCleaner/smhicleaner.sh $CITYFILE > ./shmicleaner.log 2>&1

RAWFILENAME=$(basename $CITYFILE)

RAWFILENAME="rawdata_${RAWFILENAME}"

cp $RAWFILENAME $Og/code/ClnData/Clean$CITY.csv

rm *

cd $Og

rmdir $Og/SmhiCleaner/CleanerOutputs
