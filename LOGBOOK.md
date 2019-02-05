# Description

This is the logbook of my master thesis.
I will here describe all the step i followed during the whole project. The interrogation the solution I found how and why. the idea is to be able to reconstruct the whole process of the project i've made.

# Day 1

Setup of the github repo and also familiarisation with the developpement tools I'll use for the rest of the project. Also start to work on OSRM as suggested by my Supervisor.
I forked the repo and try to build / run it.
First issue : the osrm-example that should be install after the whole build and make process is not present.
I chated with some dev from OSRM developement team about that on <https://webchat.oftc.net/>

They are really cool and kindly answer to me but there is no solution at this point. I will then code my own test file to explore how the tool work.

Finally Found how to get this osrm-exampl executable. I'll develop a script to make a whole installation of osrm until having the osrm-example executable while I'm home.

### Relevant Link :

To download data from osm : <http://download.geofabrik.de/europe.html>

My github repo : <https://github.com/GarfAbh/Master-Thesis/>

OSRM repo : <https://github.com/Project-OSRM/osrm-backend>

OSRM API : <http://project-osrm.org/docs/v5.5.1/api/#routestep-object>

### Dev tool

For test and Developement at the moment I use Atom. No package for the moment.
Language : C++

# Day 2

I need data to use the executable so first dl the convertor by simply : `sudo apt install osmctools`
