# Description

This is the logbook of my master thesis.
I will here describe all the step I followed during the whole project. The interrogation the solution I found how and why. the idea is to be able to reconstruct the whole process of the project I've made.

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

To do the conversion :
`osmconvert youfile.itextension >yourfile.thenewextension`

in fact I discover that OSRM provide already converter tool to get osrm data exactly as they need. So i'll use it instead.

Keep in mind that data are not present in my repo as they are too large to be in it. My instalation script would also create the folder data at the good place and dl the data for you and convert it at the good needed format

The wiki how has one of the step describe not working. If you get the error : "Profile profiles/car.lua not found"  (probably when runing the extract )then you have to give the path to the car.lua profile to the execution file.

solutions : osrm-extract path/to/my-map.osm.pbf -p path/to/car.lua

I have a total runing system now i know which command do what and how it works well (at least for the begining). I'll develop the script for a whole installation and running of the example this afternoon. Next step is to identify what part of the osrm are relevant for our project.

After that being done, think about the next step and what's the relevant part to do.

The script is done and work perfectly well some improvement are possible (TODO). But at this point now i have to familiarize my self with the code it self and find how i can provide my own code runing what i need using OSRM. After that check if some other tool for some other needed objectives exist or not.

creation of an organizational graph on latex to have a better representation of the repo + differentiation between data, source code, tool ...

![organizational graph of the project](https://github.com/GarfAbh/Master-Thesis/blob/master/Documentation/Image/Master_Thesis_Organizational_Graph.jpg)

### Relevant link :
<https://github.com/Project-OSRM/osrm-backend/wiki/Running-OSRM>


# Day 3

I started the day with the thinking of my futur code architecture. The idea is to first have a clear code architecture to not struggles at some point where you have multiple piece of code and you don't know where to put what. I also tried to do a makefile and a kind of test file to use osrm. Issue : we cannot use makefile ase easy as i thought for that kind of project I documment then my self on Cmake (already use for osrm building ...). I also checked documentation on the algorithms used by osrm to have a better understanding of the tool. Unfortunately MLD(Multiple Level Dijkstra) has not really documentation on the web. I'll figure out what is really and how it works. I found some CH (Contraction Hierarchies) documentation. The best example found is on the french wikipedia page (available in the relevant link of the day).



### Relevant link :

French wikipedia page for CH : <https://fr.wikipedia.org/wiki/Contractions_hi%C3%A9rarchiques>
