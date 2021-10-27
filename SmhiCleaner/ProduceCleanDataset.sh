#!/bin/bash -x

DATAPATH=$1 # no spaces!
CITY=$2
#YEAR=$3

dirNAME=`dirname "$0"`

Og=`pwd` #recording original directory where script is run
#echo $Og
cd $DATAPATH
CITYFILE="$DATAPATH/`grep -i -l -m 2 $CITY *`" # - m 2
echo $CITYFILE
cd $Og/SmhiCleaner/CleanerOutputs

$dirNAME/smhicleaner.sh $CITYFILE

RAWFILENAME=$(basename $CITYFILE)

RAWFILENAME="rawdata_${RAWFILENAME}"

cp $RAWFILENAME $Og/CleanDatasets/Clean$CITY

rm *
