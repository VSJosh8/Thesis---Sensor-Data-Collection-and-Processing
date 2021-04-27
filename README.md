# Thesis---Sensor-Data-Collection-and-Processing
This is a repository of the source files for a library that would enable collection and processing of sensor network data 

In this repository, the base class, template class and the specialized cases can be found for both the original Berkeley Lab data as well as the specialized Chicago Beach data. 

The data files that were use can also be found. The Intel Berkeley Lab data can only be found as a portion of the full file as it was too big to be uploaded, even in a compressed form. The actual file can be found at [http://db.csail.mit.edu/labdata/labdata.html]. 

The beach lab data can also be found in the repository which was sourced from [https://data.world/cityofchicago/beach-water-quality-automated-sensors]

These source codes can be placed anywhere and accessed via another file with the exception of the "TestPlotter.cpp" file. This file requires the previously mentioned "gnuplot-iostream" library as well as the "Boost" library. The gnuplot library can be placed in anywhere and accessed within the code, but the Boost library requires installation where the path is added within the environment variables and it is included within the project library.


