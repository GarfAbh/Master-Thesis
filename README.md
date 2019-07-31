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

-  [x] Developing the routing management system
-  [x] From A to B with multiple inside points
-  [x] Time management

### Step 3

-  [x] Stop time management
-  [x] Time of passage.
       Some machine may only be accessible at some precise time during the day

### Step 4
-  [x] Validation of theoritical data

### Step 5

-  [x] Traffic management

### Step 6

-  [ ] Integration in the intern soft
-  [ ] Integration of the routing in the GPS

# Requirement

Language : Python 3.5

Librairy to install :

- fuzzywuzzy : https://github.com/seatgeek/fuzzywuzzy (pip install fuzzywuzzy)
- flask : pip install flask
- pandas : pip install pandas
- git
- build-essential
- cmake
- pkg-config
- libbz2-dev
- libxml2-dev
- libzip-dev
- liboost-all-dev
- lua5.2
- liblua5.2-dev
- libtbb-dev

all of the is automaticaly install when using the install script describe after.
Or using the dependancies_install.sh script.

Database :

- openaddresses : https://openaddresses.io/

# Installation

run :
cd scripts
./install-script.sh

Then just write the path where you would like that the soft install the executable.
Then the path for the needed data.
Then the internal communication port (to initialize correctly OSRM).
Some times it will ask your password.

The installation may take 20 minutes or more.

When it's installed run an OSRM instance using:
./osrm-server-launch.sh CH

- CH is use for better performance but longer to initialize
- MLD is use for good performance and fast initialization

then just go back to the root of the project and run:
python3 server.py

after that you are good to go

here is a run example for routing :
curl -X POST --header 'Content-Type:application/json' --data @routing/input_output/input1.json 127.0.0.1:5000/vroom?malus=20

here is a run example for geocoding :
curl -XPOST --header 'Content-Type:application/json' --data @geocoder/input_output/input3.json 127.0.0.1:5000/geocode

# Data Analysis

There are two given file.
Both are equivalent but the .ipynb can only be run and use with jupyter notebook
in anaconda.
I recommend you to use it to run the whole code instead of just running the .py
