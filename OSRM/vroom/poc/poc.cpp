//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//

#include <iostream>
#include <curl/curl.h>
#include <regex>

#include "routing/routed_wrapper.h"
#include "structures/vroom/input/input.h"
#include "structures/vroom/job.h"
#include "structures/vroom/vehicle.h"
#include "utils/exception.h"

#include "string.h"


#define URL "0.0.0.0:5000/nearest/v1/driving/"
#define END_URL "?number=1&bearing=0,0"

/*
 * Il s'agit la d'un ficher test destiné a un benchmark pour de la réalité.
 * Les spécification sont les suivantes :
 * 20% des jobs doivent être fait dans une time window bien précise (ici entre 8h et 10h)
 * Les camions n'on pas de capacité particuliere.
 * il n'y a pas de skill
 * le temps de service est de 15 minutes
 * le point de départ est chez altux
 * le point d'arriver est chez moi
 * les autres job sont random partout en suisse
 * */

using namespace std;
const int TW_JOB_PER = 20;

void set_vehicule(vroom::Input *problem_instance);
void set_jobs(int nb_jobs, vroom::Input *problem_instance, string zone, string rand);
double random_long_lat_generator(std::string ll, string zone);
void random_addr_generator(double *long_lat,string zone);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
void log_solution(const vroom::Solution& sol, bool geometry);



int main(int argc, char *argv[]) {

    if (argc != 7) {
        cout << "usage : \n";
        cout << "./main x y z : \n";
        cout << "x is the number of job for the simulation\n";
        cout << "y is the number of exploration level\n";
        cout << "z is the number of thread you'd like to use\n";
        cout << "lausanne / swiss if you wish to work in lausanne or nothing for anywhere else in switzerland\n";
        cout << "true false depending on randomness for timewindowed job\n";
        cout << "seed for the randomizer (unsigned int)\n";
        return 1;
    }
    //TODO il me faut moi même donné un random et le passé à srand()
    //sinon j'aurais un million de fois le même réultats youpie
    //passée peut être la cpacité du nombre de job que peut faire chaque véhicule.
    //il faut que je vérifie que tout les résultats sont correct.

    bool GEOMETRY = true;
    srand(atoi(argv[6]));
    // Set OSRM host and port.
    cout << "set OSRM host and port \n";
    auto routing_wrapper =
            make_unique<vroom::routing::RoutedWrapper>
            ("car",vroom::Server("localhost", "5000"));

    cout << "set vroom Input \n";
    vroom::Input problem_instance;
    problem_instance.set_routing(move(routing_wrapper));

    //TODO voir si on a besoin de ca ou pas.
    problem_instance.set_geometry(GEOMETRY); // Query for route geometry
    // after solving.
    cout << "set the vehicules \n";
    set_vehicule(&problem_instance);

    cout << "set the jobs \n";
    set_jobs(atoi(argv[1]), &problem_instance,string(argv[4]),string(argv[5]));


    // Solve!
    try {
        cout << "trying to solve the problem \n";
        auto sol = problem_instance.solve(atoi(argv[2]), atoi(argv[3]));
        // Use argv[2] lvl expl and argv[3] threads.
        log_solution(sol, GEOMETRY);
    } catch (const vroom::Exception &e) {
        cerr << "[Error] " << e.message << endl;
    }

    return 0;
}
void set_vehicule(vroom::Input *problem_instance) {

    // Create one-dimension capacity restrictions to model the situation
    // where one vehicle can handle 4 jobs.
    vroom::Amount vehicle_capacity(1);
    vehicle_capacity[0] = 100;


    //c'est en remplissant ce tableau que je peut donner plus de contrainte a chaque fois
    //du moment que je les ai setup corretement avec vehicule_capacity.
    //vehicle_capacity[0] = 4;

    //c'est les horaire de boulot quand ca commence et quand ca fini en seconde
    //28800s = 8h; 61200 = 17h
    vroom::TimeWindow vehicle_tw(0, 86340);

    //46.50190,6.68973 coordinate of Altux
    //46.50910,6.64357 coordinate of my home
    vroom::Location depot(vroom::Coordinates({{6.68973, 46.50190}}));
    vroom::Location house(vroom::Coordinates({{6.64357, 46.50910}}));

    vroom::Vehicle v(1,                // id
                     depot,            // start
                     house,            // end
                     vehicle_capacity, // capacity
                     {},               // skills
                     vehicle_tw);      // time window

    problem_instance->add_vehicle(v);
    cout << "vehicule setup \n";
}
void set_jobs(int nb_jobs, vroom::Input *problem_instance, string zone, string ra) {
    //c'est la durée d'un stop pour faire le job ici le remplissage
    vroom::Duration service = 15 * 60; // 15 minutes

    // Job to be done between 8 and 10 AM.
    vector <vroom::TimeWindow> job_tw({{28800, 36000}});

    //je doit encore figure out ce que c'est
    vroom::Amount job_amount(1);
    job_amount[0] = 1;

    double long_lat[2];

    vector <vroom::Job> jobs;
    for (int i = 0; i < nb_jobs; ++i) {
        //20% des livraisons peuvent être obligatoirement entre 8h et 10h
        random_addr_generator(long_lat,zone);
        cout << long_lat[0] << endl;
        cout << long_lat[1] << endl;
        if( (rand() % 100 < TW_JOB_PER) && (ra.compare("true") == 0) ) {
            //on push un job avec une timewindow entre 8 et 10h
            jobs.push_back(vroom::Job(i + 1,
                    //Todo ici il me faut un générateur de coordoner en long lat en suisse
                                      vroom::Coordinates({{long_lat[0], long_lat[1]}}),
                                      service,
                                      job_amount,
                                      {},
                                      job_tw));
        } else {
            //on push un job sans contrainte
            jobs.push_back(vroom::Job(i + 1,
                    //Todo ici il me faut un générateur de coordoner en long lat en suisse
                                      vroom::Coordinates({{long_lat[0], long_lat[1]}}),
                                      service,
                                      job_amount,
                                      {}));
        }
    }
    cout << "jobs setup \n";
    cout << problem_instance->amount_size() << endl;
    for (const auto &j : jobs) {
        problem_instance->add_job(j);
    }
    cout << "jobs setup \n";
}
static size_t write_function(void *ptr, size_t size, size_t nmemb, void *userp){
  ((std::string*)userp)->append((char*)ptr, size * nmemb);
  return size * nmemb;
}
void random_addr_generator(double *long_lat,string zone) {
    CURL* curl;
    CURLcode sucess;
    string buffer;
    double lon, lat;
    do{
      lon = random_long_lat_generator("long",zone);
      lat = random_long_lat_generator("lat",zone);
      string url = "0.0.0.0:5000/nearest/v1/driving/" + to_string(lon) + "," + to_string(lat) + "?number=1&bearings=0,0";
      curl = curl_easy_init();
      cout << "url is : " << url << "\n";

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
      sucess = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
    }while(sucess != CURLE_OK);

    cout << buffer << "\n";

    //regex to capture the needed information.
    regex reg ("\\[(\\s*([^\"]*)\\s*)\\]");
    smatch m;
    string::const_iterator searchStart(buffer.cbegin());

    for(int i = 0 ; i < 2 ; i++){
      regex_search(searchStart,buffer.cend(),m,reg);
      searchStart = m.suffix().first;
    }

    stringstream ss;
    ss.str(m.str(1));
    string token;
    for(int i = 0 ; i < 2 ; i++){
      getline(ss,token,',');
      long_lat[i] = stod(token);
      // long_lat[0] = 6.54848;
      // long_lat[1] = 46.62047;
    }
  }

double random_long_lat_generator(std::string ll, string zone) {
    double max_lon, max_lat, min_lon, min_lat;
    if(zone.compare("lausanne") == 0){
      max_lon = 6.732;
      min_lon = 6.5075;

      max_lat = 46.5845;
      min_lat = 46.4878;
    }else if(zone.compare("swiss") == 0){
      max_lon = 10.492;
      min_lon = 5.956;

      max_lat = 47.80842;
      min_lat = 45.818;
    }else{
      cout << "c'est pas possible essaye encore <3";
      max_lon = 10.492;
      min_lon = 5.956;

      max_lat = 47.80842;
      min_lat = 45.818;
    }

    double tmp;
    double r = double(rand()) / (double(RAND_MAX));
    double range;
    if (ll.compare("long") == 0) {
        range = max_lon-min_lon;
        tmp = r * range + min_lon;
    } else {
        range = max_lat - min_lat;
        tmp = r * range + min_lat;
    }
    return tmp;
}
void log_solution(const vroom::Solution& sol, bool geometry) {
    std::cout << "Total cost: " << sol.summary.cost << std::endl;
    std::cout << "Unassigned: " << sol.summary.unassigned << std::endl;

    // Log unassigned jobs if any.
    std::cout << "Unassigned job ids: ";
    for (const auto& j : sol.unassigned) {
        std::cout << j.id << ", ";
    }
    std::cout << std::endl;

    // Describe routes in solution.
    for (const auto& route : sol.routes) {
        std::cout << "Steps for vehicle " << route.vehicle
                  << " (cost: " << route.cost;
        std::cout << " - duration: " << route.duration;
        std::cout << " - service: " << route.service;
        if (geometry) {
            std::cout << " - distance: " << route.distance;
        }

        std::cout << ")" << std::endl;

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
            std::cout << step_type;

            // Add job ids.
            if (step.type == vroom::STEP_TYPE::JOB) {
                std::cout << " " << step.job;
            }

            // Add location if known.
            if (step.location.has_coordinates()) {
                std::cout << " - " << step.location.lon() << ";" << step.location.lat();
            }

            std::cout << " - arrival: " << step.arrival;
            std::cout << " - duration: " << step.duration;
            std::cout << " - service: " << step.service;

            // Add extra step info if geometry is required.
            if (geometry) {
                std::cout << " - distance: " << step.distance;
            }
            std::cout << std::endl;
        }
    }
}
