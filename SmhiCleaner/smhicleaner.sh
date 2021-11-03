#!/bin/bash

# Code Inspirations from Florido Paganelli florido.paganelli@hep.lu.se //Tutorial 3
#
# Description: this script manuipulates specific SMHI dataset and 
#              performs some cleaning actions on it, namely:
#              - Takes an SMHI datafile <filename> from a specified path in the filesystem
#              - Cleanses up unwanted information in the data file and
#                 extracts just the raw temperature data in
#                 - rawdata_<filename>
#              - prepares the file to be read by standard C++ 
#                CSV libraries
#
# Examples:
#        ./smhicleaner.sh ./DatasetFolder/smhi-opendata_1_52240_20200905_163726.csv
#
# NOTE: the paths above are examples.
# So do NOT assume the file is exactly in any of the above paths.
#
########################################################################


###### Functions #######################################################

## usage
# this function takes no parameters and prints an error with the 
# information on how to run this script.
usage(){
	echo "----"
	echo -e "  To call this script please use"
	echo -e "   $0 '<path>'"
	echo -e "  Example:"
    echo -e "   $0 '/tutorial3/homework3/data/smhi-opendata_1_52240_20200905_163726.csv'"
	echo "----"
}

###### Functions END =##################################################


# Get the first parameter from the command line:
# and put it in the variable SHMIINPUT
SMHIINPUT=$1

# Input parameter validation:
# Check that the variable SMHIINPUT is defined, if not, 
# inform the user, show the script usage by calling the usage() 
# function in the library above and exit with error
if [[ "x$SMHIINPUT" == 'x' ]]; then
   echo "Missing input file parameter, exiting"
   usage
   exit 1
fi

# Extract filename:
# Extract the name of the file using the "basename" command 
# basename examples: https://www.geeksforgeeks.org/basename-command-in-linux-with-examples/
# then store it in a variable DATAFILE
DATAFILE=$(basename $SMHIINPUT)

# Analyze the input parameter and copy:

# If $SMHIINPUT not empty
if [[ "x$SMHIINPUT" != "x" ]]; then
   # Copy the file in the current directory as
   #    original_$DATAFILE
   # use the -a option to preserve filesystem information (permissions etc)
   echo "Copying input file $SMHIINPUT to original_$DATAFILE"
   cp -a $SMHIINPUT ./original_$DATAFILE
fi 

# Check that the input file has been copied with no errors:
# Write an IF statement that does the following:
# If any of the previous commands failed, exit with error 
# and tell the user what happened.
# remind the user of the syntax by calling the usage() function defined
# in the libraries section above.
if [[ $? != 0 ]]; then
   echo "Error downloading or copying file, maybe wrong command syntax? exiting...."
   usage
   exit 1
fi

# If we got here without errors, we can start cleaning up!

# Identify the data starting line:
# Looking at the SHMI data, it seems that the line that contains the
# string "Datum" is the beginning of data.
# Find what line contains the string "Datum" using grep
# put the value in a variable called STARTLINE
# - use the grep option -n  and cut to take just the number.
# - use the cut command to select field 1 using ':' as separator
# - Use the pipe | to pass the output of grep to cut
echo "Finding the first line containing 'Datum'..."
STARTLINE=$(grep -n 'Datum' original_${DATAFILE} | cut -d':' -f 1)

# skip one more header line:
# Use arithmetic expansion to add a line, since the actual 
# data starts at the STARTLINE + 1 line, so to remove the header
# where Datum;... is contained
STARTLINE=$(( $STARTLINE ))

# Remove unnecessary lines at the top of the datafile:
# Strip away the top STARTLINE lines (the value of $STARTLINE) using 
# the tail command and write the result 
# to as file called clean1_$DATAFILE using the > operator to 
# redirect the standard output.
echo "Removing the first $STARTLINE lines, result in clean1_${DATAFILE}"
tail -n +$STARTLINE original_${DATAFILE} > clean1_${DATAFILE}

# Fix format for the strange lines with comments:
# consider only the relevant columns (1,2,3,4) using cut
# this will clean up the lines at the beginning of the data 
# that are not consistent with the format, so that we can use the data 
# these lines contain without discarding them.
# Write the result to a file called clean2_${DATAFILE} using the > operator
echo "Selecting only relevant columns, result in clean2_${DATAFILE}"
cut -d';' -f 1,2,3,4 clean1_${DATAFILE} > clean2_${DATAFILE}

# Convert format to comma separated variables so it can be read by standard C++ csv parsers:
# Change semicolons to commas using sed and 
# write out the result to a file called rawdata_${DATAFILE}
echo "Substituting the ; with spaces, result in rawdata_${DATAFILE}"
sed 's/;/,/g' clean2_${DATAFILE} > rawdata_${DATAFILE}

#done
