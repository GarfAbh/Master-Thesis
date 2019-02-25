# Description

This is the logbook of my master thesis.
I will here describe all the step I followed during the whole project. The interrogation the solution I found how and why. the idea is to be able to reconstruct the whole process of the project I've made.

W1D1 means week 1 day 1

# W1D1

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

For test and Developement at the moment I use Atom Clion Intelij.
Language : C++, Java

# W1D2

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


# W1D3

I started the day with the thinking of my futur code architecture. The idea is to first have a clear code architecture to not struggles at some point where you have multiple piece of code and you don't know where to put what. I also tried to do a makefile and a kind of test file to use osrm. Issue : we cannot use makefile ase easy as i thought for that kind of project I documment then my self on Cmake (already use for osrm building ...). I also checked documentation on the algorithms used by osrm to have a better understanding of the tool. Unfortunately MLD(Multiple Level Dijkstra) has not really documentation on the web. I'll figure out what is really and how it works. I found some CH (Contraction Hierarchies) documentation. The best example found is on the french wikipedia page (available in the relevant link of the day).



### Relevant link :

French wikipedia page for CH : <https://fr.wikipedia.org/wiki/Contractions_hi%C3%A9rarchiques>

# W1D4

It is time to continue to study the other existing tool. There is a non exhaustiv list existing on the wikipedia page in the relevant link.
Based on what I seen with OSRM and the specification of the project I establish a list of needed feature the the tool must / should have in order to be consider or not for the rest of the project.
The list is in the README file.
I had been recommanded to have a look at graphhopper.
It seems pretty full of functionnality. I dl the repo as with OSRM and try some run. I had an issues with there automatic install script. I then try there forum and the community sound active i had a response 30 minutes after having ask. At the end it seems that the offline mode is not possible with this tool. Continue to explore then.

I also have a quick look on all the other tool from the list. In order to simply see if this is usefull or not to go deep in the exploration with them or if i can go straigth forward.


### Relevant link :

Wikipedia list : <https://wiki.openstreetmap.org/wiki/Routing>

Graphhoper git repo : <https://github.com/graphhopper>

Graphhopper API : https://graphhopper.com/api/1/docs/route-optimization/

# W1D5

End of the 1st week. Let's make a table that resume the whole exploration and also finishing the exploration with the potentialy interesting tool I've seen the day before. The table is available in the relevant link section.
OptaPlanner sound to be the optimization tool. Linking with the routing tool then you have the product. I'll explore this during the day after finishing exploring the other tool.

### Relevant link :

Resume table : <https://docs.google.com/spreadsheets/d/1TJBpeRNf6NmgbpopDPa9OuvlgIHcmkL10r7P27FXFIU/edit?usp=sharing>

OptaPlanner : <https://www.optaplanner.org/learn/useCases/vehicleRoutingProblem.html>

OpenRouteService repo : <https://github.com/GIScience/openrouteservice/>


# W2D1

The aim of the day was to go deeper in graphHopper to clarify the unclear points.
The websit is beautifull and atractive but not relevant in term of organization to understand how it works.
Finally figure out that yes there is an open source repo to our routing issues : jsprit

It's build on top of graphopper so it's resolving issue in place (offline <3) but not on the map.
The problem then remain to get our data properly and pass it correctly to jsprit to solve it.

For the moment I don't have a deep understanding of jsprit but using the example code and going through the source code I may say that it could be a better choice than OSRM as we will have less implementation to do. However I have to keep in mind that it's in java and JNI would be needed in order to have a good interface with python. But this is a latter issue.

While going through the internet to checkout which kind of algorithm is used or not I found Vroom. It's like jsprit but with OSRM. and it seems to have the needed functionnality.


### Relevant link :

Jsprit repo : <https://github.com/graphhopper/jsprit>

Vroom repo : <https://github.com/VROOM-Project/vroom>

# W2D2

Today is teacher meeting and also conclusion of the first step of the thesis.
All the comments and component I took into acount to choose some tool in particular are resume in my resume table.

Meeting were concluant. Still need to explore one tool that was put aside too soon : OpenTripPlanner.

Otherwise in any case now I clean my repo to keep Vroom with OSRM and jsprit with graphhopper. The idea now is to make 2 / 3 POC (Proof of concept) and already make some benchmark in order to have a better idea on where we are going.

Begining of the work on the 1st POC : Vroom + OSRM i made 2 script a first one to make the whole folder organisation correctly to make my soft call inteligent the second one to run the OSRM server using CH or MLD.
I also started to do the source code of a tester that will make some test on real potential use case.
I use random generator to be sure not having bias and at the i would like to be able to compare CH and MLD with different configuration (comparable with jsprit of course) doing an average on each run ...

### Relevant link :

Resume table : <https://docs.google.com/spreadsheets/d/1TJBpeRNf6NmgbpopDPa9OuvlgIHcmkL10r7P27FXFIU/edit?usp=sharing>

# W2D3

I make a deeper search about OpenTripPlanner. It's more about planning it's trip than having a really usable routing planification with multiple stops for vehicule. So we drop this tools and now i focus on making POC for the 2 other tool we decided to keep.

# W2D4

the first POC is in progress. As i'll use it to make a little benchmark I try to make it the most random possible to get real possible value. One of the issue is to get a random address there is some website that give that but impossible to make some request to it and get simple answer. I decided to use the OSRM API. Once the server is on there is a request that ask for the nearest point from the one you are giving. THe idea is so to use curl library on local host server to get random address.

Now i'm struggle with the location of the curl library on the office computer.

# W2D5

lets find the path to this library and make the first poc work and also start having some statistic from this.
I also figure out that it could be possible to simply launch a vroom instance and pass it a json file. So it could be usefull to think about some code that juste create and format json from our need.
Finally manage to get a working code. It create 1 vehicule and optimize it's routing between a starting point and an end point (both given) random generation of jobs (address). Still have to figure out some parameters that could be taken into acount. Also think about which parameters should be fixed or given at the execution. Create the script to make the whole execution automatic and then get the results properly outputed. When this is done repeat with Graphhopper and jsprit. Then make the comparison analysis

Issue of the day was working with libcurl that is not that easy to understand. This lib was mandatory to make a random address generator for the testing.

# W3D1



I started to put my thougth on each tool in a resume table available in the relevant link part. I also make script ... to get some statistics from the OSRM + Vroom POC. Still need to analyse and make beautiful graph ...
Still need to do the same with graphhopper and jsprit.

### Relevant link :

Resume table : <https://docs.google.com/spreadsheets/d/1nqe-WgKlpyFsKYEEa1XLbwym1JEsX-8OC5GJM5zoBXc/edit#gid=0>
Performance stats : <https://docs.google.com/spreadsheets/d/1uCsiI2CiCoS5z6I_O5LnAgnBi8EK8CnKl3NOUeQjpcQ/edit#gid=696287079>

# W3D2

I've done the POC for graphHopper + Jsprit it runs still need to figure some function that could not be use in order to have something comparable with OSRM + vroom. I figure out that it would be possible to use parallelism work so I will update my performance test to work between 1 and 64 threads and see which is better. I will also update the perf test for Vroom + OSRM.

### Relevant link :

Performance stats : <https://docs.google.com/spreadsheets/d/14h6lwvHTuU6UD3Tn3puHuVa4lB2KTFjQrSSrcxXTK0U/edit>

# W3D3

I should finish the whole test of both tools with POC files compared in the resume table and both performance test in the drive too.
Finally got issues with Jsprit and Graphhopper. Some internal server error make me realize that graphopper literaly consider a country and not a til when it work on a map. Instead of OSRM that use the entire tile and do not return error if you are out of bound.

So I had to change my test to be able to get something more close between those 2 tools.
Other issue but here I don't knoe why it's happening. Jsprit + graphhopper is long tu use for multiple run. There is a kind of wait delay of 1 sec (or more) between each run which make 20 000 different run for performance really long !
Probably will try to running it at night.

### Relevant link :

Resume table : <https://docs.google.com/spreadsheets/d/1nqe-WgKlpyFsKYEEa1XLbwym1JEsX-8OC5GJM5zoBXc/edit#gid=0>
Performance stats Vroom + OSRM : <https://docs.google.com/spreadsheets/d/1uCsiI2CiCoS5z6I_O5LnAgnBi8EK8CnKl3NOUeQjpcQ/edit#gid=696287079>
Performance stats Jsprit + Graphhopper : <https://docs.google.com/spreadsheets/d/14h6lwvHTuU6UD3Tn3puHuVa4lB2KTFjQrSSrcxXTK0U/edit>

# W3D4

Today I'm presenting my work to my chief. Unfortunately the runs during the nigth didn't gone well. Which make me try to run again this morning. But I don't expect to have it done before the presentation. The presentation is done everything is ok. Still have to explore a bit graphhopper + jsprit to make sur that what I pointed out in my resume table is correct. Also now i'll ask to the dev if a geocoder could interest them and also make some qualittativ test.

### Relevant link :

Resume table : <https://docs.google.com/spreadsheets/d/1nqe-WgKlpyFsKYEEa1XLbwym1JEsX-8OC5GJM5zoBXc/edit#gid=0>

# W3D5

As after all presentation it's the cleaning repo day. Also seting up the new todo list to work on and start working on it by the first easy stuff to do keeping the biggest work for the next week.

# W4D1

Today I start the qualittativ test on OSRM + Vroom. I also still wait for an answer from OSRM regarding integrate a geocoder in it (Cause it makes more sens to have one in OSRM than in vroom). Last day it was more or less clear that graphhopper has some good tool(geocoder + matrix use) but not in the open source version. Let see then if we want to use it or not.
