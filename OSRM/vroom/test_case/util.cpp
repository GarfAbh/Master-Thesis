//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//

//internal code
#include "util.h"

using namespace std;
using namespace boost;
using namespace boost::adaptors;


vector<string> jobs_id;
vector<boost::tuple<string,string> > start_stop_tuple;
//pour les bien du test il faudrais que j'ai un mapping qui existe entre job_id
//et start_time end_time comme ca par la suite je pourrais faire des comparaison cool


void reader(string filename,
            string kind,
            vector<vroom::Job>* jobs,
            vector<vroom::Vehicle>* vehicles){

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
     debug << "just jump out the first line";
     first_line = false;
     continue;
   }
   split(row,line, [](char c){
     return c == ';';
   });
   if(kind.compare("job") == 0){
     debug << "let's create a new job :" << line;
     vroom::Job job = create_new_job(row);
     jobs->push_back(job);
   }else if(kind.compare("vehicle") == 0 ){
     debug << "let's create a new vehicle :" << line;
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
  //28800s = 6h; 61200 = 17h
  //TODO faire une fonction qui prent start time et le traduit en seconde.
  //il faut aussi penser que ce seras une variable pour l'avenir.
  vroom::TimeWindow vehicle_tw(21600,61200);

  //46.50190,6.68973 coordinate of Altux
  //46.50910,6.64357 coordinate of my home
  vroom::Location depot(vroom::Coordinates({{6.68973, 46.50190}}));
  vroom::Location house(vroom::Coordinates({{6.64357, 46.50910}}));

  return vroom::Vehicle(stoul(id_tour),depot,depot,vehicle_capacity,{},vehicle_tw);
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

  //ces deux ligne sont vouer a disparaitre elle n'ont d'utilité que pour la présentation future.
  jobs_id.push_back(job_id);
  start_stop_tuple.push_back(boost::tuple<string,string>(start_time,end_time));
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
void writer(string filename,const vroom::Solution& sol, bool geometry){
  ofstream file;
  file.open(filename,ios_base::app);
  int total_cost = sol.summary.cost + sol.routes[0].service;
  file << "Total cost: " << sec_to_formated_string(total_cost) << endl;
  file << "Unassigned: " << sol.summary.unassigned << endl;

  if(sol.summary.unassigned != 0){
    // Log unassigned jobs if any.
    file << "Unassigned job ids: ";
    for (const auto& j : sol.unassigned) {
      file << j.id << ", ";
    }
    file << endl;
  }
  // Describe routes in solution.
  for (const auto& route : sol.routes) {
    file << "Steps for vehicle " << route.vehicle;
    file << " - duration: " << sec_to_formated_string(route.duration);
    file << " - service: " << sec_to_formated_string(route.service);
    if (geometry) {
      file << " - distance: " << format_distance(route.distance);
    }
    file << endl;
    // Describe all route steps.
    for (const auto& step : route.steps) {
      std::string step_type;
      switch (step.type) {
        case vroom::STEP_TYPE::START:
        step_type = "Start";
        break;
        case vroom::STEP_TYPE::END:
        step_type = "End";
        break;
        case vroom::STEP_TYPE::JOB:
        step_type = "Job";
        break;
      }
      file << step_type;

      // Add job ids.
      if (step.type == vroom::STEP_TYPE::JOB) {
        file << " " << step.job;
      }

      file << " - arrival: " << sec_to_formated_string(step.arrival);
      file << " - duration: " << sec_to_formated_string(step.duration);
      file << " - service: " << sec_to_formated_string(step.service);

      // Add extra step info if geometry is required.
      if (geometry) {
        file << " - distance: " << format_distance(step.distance);
      }
      file << std::endl;
    }
  }
  file.close();
}
void format_input(vector<vroom::Job>* jobs,
                  vector<vroom::Vehicle>* vehicles,
                  string output_filename){
  ofstream file;
  file.open(output_filename,ios_base::app);
  //faut que je le compute avec les datas.
  file << "Total cost: " << sec_to_formated_string(total_cost()) << endl;
  //on en a forcement 0 sur cette tournée puisque l'on est sur des tournée
  //qui ont eux lieu.
  file << "Unassigned: " << 0 << endl;

  for(auto v : *vehicles){
    //faut remplir encore ici les datas
    file << "Steps for vehicle " << v.id;
    file << " - duration: " << endl;
    file << " - service: " << endl;
    file << " - no distance data";
    file << endl;

    //faudras surement changer la boucle for qu'il y a ici pour
    //parcourir les tableaux en même temps.
    int current_duration = 0 ;
    for(auto j : *jobs){
      //TODO y a une erreur ici il faut explorer.
      debug << jobs;
      current_duration += string_to_sec(get_arrival(j.index()));
      file << " Job";
      file << " - arrival: " << get_arrival(j.index());
      file << " - duration: " << sec_to_formated_string(current_duration);
      file << " - service: " << sec_to_formated_string(service_time(j.index()));
      //ici je met tout les jobs.

    }
  }


  //INSERT CODE HERE
  file.close();
}

//TODO ameliorer pour être sur d'avoir hh:mm:ss et moi h:m:s(donc complete avec des zero.)
//changer le nom des fonction pour que ce soit plus explicite et beau (même si on en auras surement plus besoin après)
string sec_to_formated_string(int nb_sec){
  int heure = floor(nb_sec / 3600.0);
  int min = floor(((nb_sec % 3600) / 60.0));
  int sec = nb_sec % 3600 % 60;
  return to_string(heure) + ":" + to_string(min) + ":" + to_string(sec);
}
int string_to_sec(string duraction){
  vector<string> time;
  split(time,duraction, [](char c){
    return c == ':';
  });
  return atoi(time[0].c_str()) * 3600 + atoi(time[1].c_str()) * 60 + atoi(time[2].c_str());
}
string format_distance(int nb_m){
  return to_string(nb_m/1000.0) + "km";
}

//voué a disparaitre c'est juste pour la présenteation
int total_cost(){
  return string_to_sec(get<1>(start_stop_tuple.back())) - 21600;
}
int service_time(int index){
  return string_to_sec(get<1>(start_stop_tuple[index])) - string_to_sec(get<0>(start_stop_tuple[index]));
}
string get_arrival(int index){
  return get<0>(start_stop_tuple[index]);
}
// voir si y a s d'autre data interessante a print de facon fancy et donc prévoir les fonctions qui vont bien.
//genre la distance qui est censé être en m

// voir également si je fais tout cela ici ou si au contraire on considere un petit renommage des ficher avec plus de modularisation.
// suivant tout ce qu'il y auras à faire ca peux valoir la peine pour la suite
