# Master-Thesis

This is the repository of my master thesis at EPFL.

# Problem

This is an optimization problem.

You have to optimize the delivery system for a fleet of truck starting from A going to B through some stop points. All the stop points has to be delivered during the day.

# Specifications

### Constrainte :

-   OpenSource
-   Local use
-   Offline system
-   Based on OSM (Open Street Map)

### Step 1

-  [x] State of the art
-  [x] Identify the usefull tool

### Step 2

-  [ ] Developing the routing management system
-  [ ] From A to B with multiple inside points
-  [ ] Time management

### Step 3

-  [ ] Stop time management
-  [ ] Time of passage.
       Some machine may only be accessible at some precise time during the day
    ### Step 4
-  [ ] Validation of theoritical data

### Step 5

-  [ ] Traffic management

### Step 6

-  [ ] Integration in the intern soft
-  [ ] Integration of the routing in the GPS

## Tools' feature needed list

-  Still exist ?
-  Licence
-  Fit with the need ?
-  Offline
-  Active community
-  Documentation
-  Language
-  Algorithms

# Organization

![organizational graph of the project](https://github.com/GarfAbh/Master-Thesis/blob/master/Documentation/Image/Master_Thesis_Organizational_Graph.jpg)

# Instalation

Download the repository. Then go to the source folder and just run the instalation script. It will directly build the project, dowload the data, run the example executable.

this could take several minutes as OSRM is huge to build.

basicaly clone the repo then run :
`./osrm-script.sh`
