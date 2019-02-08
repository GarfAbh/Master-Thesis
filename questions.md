# What ?
this is where i'll write down the questions I have regardin the project and all the tips the teacher could give me. This way when I have an interagation regarding something I put it there and I just need to check that page when going to the teacher meeting.

### Question 1
Est ce que vous savez si il existe un moyen efficace de print efficacement l'output des scripts ? Et egalement de les checker ?

### Question 2
Jusqu'a maintenant je travail sur le repo de OSRM que j'ai fork. Mais cela ne me semble pas optimal pour la maintenance du code. En effet ne vaudrait il pas mieux faire de OSRM un subrepo linker directement depuis la source ? Si oui que preconisez vous comme bonne maniere de proceder ?

### Question 3
Mon architecture du code est disponible dans mon dossier src. Est ce qu'il vous semble bien et clair ou au contraire au regard de ce qui devrais arriver par la suite il faudrais changer quelque peu ?

### Question 4
Je trouve aucune information sur multi level Dijkstra j'ai l'impression qu'il s'agit de run dijkstra sur plusieurs niveau de route mais je trouve rien de relevant à ce sujet. Cependant j'ai trouver et comprend comment fonctionnais CH (Contraction Hierarchies) ca à l'air très très efficace (voir mieux que Dijkstra) ce qui est plutot cool dans l'idée faudras faire un benchmark. En revanche c'est pas ultra clair la distinction entre les deux au niveau de OSRM est-ce que vous en savez plus ou pas ?

### Question 5
Quel langue pourrions nous préconiser le plus ?
Contrainte du choix du language : performance pour ce que l'on veut faire. Environnement de dévelopement adapté et efficace.
S'adapte bien au différent outils que l'on prend en compte.
Pour le moment : C++ et Java sont (OSRM est en C++ et graphhopper est en java.) les plus probable

### Question 6
D'un point de vue algo, c'est pas ultra clair comment fonctionne chacun des outils que j'ai put explorer. IL y a toujours plus ou moins du Dijkstra qui reviens ainsi que du A*. Seulement beaucoup mentionne aussi CH (Contraction Hierarchy). Autant j'ai compris comment ca fonctionne autant j'ai l'impression que c'est une sorte de complement à Dijkstra et pas une sorte de concurrent comme A*.
De plus A* Vs Dijkstra, je vois bien la différence entre les deux mais je me demdande à quel point le corner case de A* est a ce point un algo potentielement moins optimal par rapport à ce que l'on veut achieve.
