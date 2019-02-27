//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//
//internal code
#include "util.h"

using namespace std;
using namespace boost;


//pour les bien du test il faudrais que j'ai un mapping qui existe entre job_id
//et start_time end_time comme ca par la suite je pourrais faire des comparaison cool


void reader(string filename,string kind,vector<vroom::Job>* jobs,vector<vroom::Vehicle>* vehicles){
  ifstream file (filename);
  if(!file){
    cout << "reader : error on opening file :" << filename << endl;
    //TODO voir pour rajouter un code erreur ici
  }

 string line;
 vector<string> row;
 bool first_line = true;
 while(getline(file,line)){
   //TODO faut faire attention à cela ca peut être dangereux il faut bien être
   //sur du format des donnée qui sont passé en argument à tout moment !
   if(first_line){
     first_line = false;
     continue;
   }
   split(row,line, [](char c){
     return c == ',';
   });
   if(kind.compare("job") == 0){
     vroom::Job job = create_new_job(row);
     jobs->push_back(job);
   }else if(kind.compare("vehicle") == 0 ){
     vroom::Vehicle v = create_new_vehicle(row);
     vehicles->push_back(v);
   }else{
     //TODO gestion d'erreur ici.
     cout << "reader : invalid argument kind exception :" << kind << endl;
     cout << "must be : 'job' or 'vehicle'"<<endl;
   }
 }
}
vroom::Vehicle create_new_vehicle(vector<string> vehicle_param){
  //TODO en fait en attendant on peu faire que ca le fait avec le même ficher
  //car y a beaucoup de par default faudras pas oublier de faire de la vérification
  //de parametre aussi
  string date = vehicle_param[0],
         job_id = vehicle_param[1],
         id_tour = vehicle_param[2],
         start_time = vehicle_param[3],
         end_time = vehicle_param[4],
         entreprise = vehicle_param[5],
         magasin = vehicle_param[6],
         address_num = vehicle_param[7],
         postal = vehicle_param[8],
         ville = vehicle_param[9],
         canton = vehicle_param[10],
         latitude = vehicle_param[11],
         longitude = vehicle_param[12];

  //TODO on le met en constante pour le moment pour remplir nos condition mais
  //a terme ce seras une variable.
  vroom::Amount vehicle_capacity(1);
  vehicle_capacity[0] = 100;

  //c'est les horaire de boulot quand ca commence et quand ca fini en seconde
  //28800s = 8h; 61200 = 17h
  //TODO faire une fonction qui prent start time et le traduit en seconde.
  //il faut aussi penser que ce seras une variable pour l'avenir.
  vroom::TimeWindow vehicle_tw(0,61200);

  //46.50190,6.68973 coordinate of Altux
  //46.50910,6.64357 coordinate of my home
  vroom::Location depot(vroom::Coordinates({{6.68973, 46.50190}}));
  vroom::Location house(vroom::Coordinates({{6.64357, 46.50910}}));

  return vroom::Vehicle(stoul(id_tour),depot,house,vehicle_capacity,{},vehicle_tw);
}
vroom::Job create_new_job(vector<string> job_param){
  //TODO faire de la vérification de paramètre si jamais longitude latitude
  //sont pas correct faire une gestion d'erreur.
  string date = job_param[0],
         job_id = job_param[1],
         id_tour = job_param[2],
         start_time = job_param[3],
         end_time = job_param[4],
         entreprise = job_param[5],
         magasin = job_param[6],
         address_num = job_param[7],
         postal = job_param[8],
         ville = job_param[9],
         canton = job_param[10],
         latitude = job_param[11],
         longitude = job_param[12];

  //TODO voir si c'est une variable dépendante de l'input ou si c'est une constante.
  //pour l'instant ca sera une constante
  vroom::Duration service = 15 * 60; // 15 minutes

   //TODO ca sera une variable pour sûr pour l'instant ca sera donc une constante non utilisé
  vector <vroom::TimeWindow> job_tw({{0, 86400}});

  //TODO ca aussi ca sera une variable mais pour l'instant on reste sur une constante.
  vroom::Amount job_amount(1);
  job_amount[0] = 1;

  vroom:: Coordinates coo = vroom::Coordinates({{stod(longitude),stod(latitude)}});

  return vroom::Job(stoul(job_id),coo,service,job_amount,{});
}
void writer(string filename){
}
