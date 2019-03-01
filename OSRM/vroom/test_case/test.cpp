//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//
#include "routing/routed_wrapper.h"
#include "structures/vroom/input/input.h"

#include "utils/exception.h"
#include "util.h"


using namespace std;

void set_vehicule(vroom::Input *problem_instance,vector<vroom::Vehicle>* vehicles, string vehicle_filename);
void set_jobs(vroom::Input *problem_instance,vector<vroom::Job>* jobs, string job_filename);
void log_solution(const vroom::Solution& sol, bool geometry);

int main(int argc, const char *argv[]) {
  Debug::init(argc,argv);

  if(argc != 4){
    cout << "main wrong number of argument : " << argc-1 << endl;
    cout << "usage : " << endl;
    cout << "./test jobs.csv vehicle.csv output_file" << endl;
    return -1;
  }
  string input_job_filename = argv[1],
         input_vehicle_filename = argv[2],
         output_filename = argv[3];

  // Set OSRM host and povoid set_vehicule(vroom::Input *problem_instance,vector<vroom::Vehicle> vehicles, string vehicle_filename)rt.
  debug << "set OSRM host and port";
  auto routing_wrapper = make_unique<vroom::routing::RoutedWrapper>
  ("car",vroom::Server("localhost", "5000"));

  debug << "set vroom Input";
  vroom::Input problem_instance;
  problem_instance.set_routing(move(routing_wrapper));

  //TODO voir si on a besoin de ca ou pas.
  bool GEOMETRY = true;
  problem_instance.set_geometry(GEOMETRY); // Query for route geometry
  // after solving.
  debug << "set the vehicules";
  vector<vroom::Vehicle> vehicles;
  set_vehicule(&problem_instance,&vehicles,input_vehicle_filename);

  debug << "set the jobs";
  vector<vroom::Job> jobs;
  set_jobs(&problem_instance,&jobs,input_job_filename);

  // Solve!
  try {
    debug << "trying to solve the problem";
    auto sol = problem_instance.solve(5, 4);
    // Use argv[2] lvl expl and argv[3] threads.
    log_solution(sol, GEOMETRY);
  } catch (const vroom::Exception &e) {
    cerr << "[Error] " << e.message << endl;
  }

  //TODO une fois la solution trouver ecrire la solution dans un nouveau ficher.
  //writer(output_filename);
  return 0;
}

void set_vehicule(vroom::Input *problem_instance,vector<vroom::Vehicle>* vehicles, string vehicle_filename) {
  debug << "read : " << vehicle_filename;
  reader(vehicle_filename,"vehicle",NULL,vehicles);
  debug << "vehicle size : " << vehicles->size();
  for(auto v : *vehicles){
    problem_instance->add_vehicle(v);
  }
}
void set_jobs(vroom::Input *problem_instance,vector<vroom::Job>* jobs, string job_filename) {
  debug << "read : " << job_filename;
  reader(job_filename,"job",jobs,NULL);
  debug << "jobs size : " << jobs->size();
  for(auto j : *jobs){
    problem_instance->add_job(j);
  }
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