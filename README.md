# Final_Project_TeamB


## Overview of project
This project has the objective of producing three Results from the data given by the Swedish Meteorological and Hydrological Insitute (SMHI) regarding the temperatures recorded in different cities in Sweden. The original data is found in the datasets folder of the repository. The three Results that will be created are:

1. Plotting a histogram of the temperature of a specific day (given as input by the user)
2. Plotting the maximum/minimum temperature of each year for all the years there is available data for
3.1 Plotting the average temperature for every day in the data available
3.2 Plotting the difference between the yearly peaks of the daily temperature to observe if there has been any shift in seasons over the years.




## Cleaning the datafiles  
Run the ProduceCleanDataset.sh bash script on the terminal in the base folder (Final_Project_TeamB)  
with the datapath to the dataset and the city of interest as parameters  
A clean dataset with the name Clean"City".csv will be produced in the ClnData folder, which is stored inside the  code directory(Final_Project_TeamB/code/ClnData)



## Obtaining Results
Within the directory /Final_Project_TeamB/code open ROOT in the terminal. This will automatically compile the program and you will be able to use all the functions and classes contained in the code. To see all three results one should run project(). Instructions will appear on the terminal asking for input depending on what the user will want to plot. 

If the user wants to create only specific plots or use specific functions an object can be initialized in the tempTrender class by passing a filepath to a csv datafile as a parameter. Then the user can run member functions of this class to create the specific plots desired. 


