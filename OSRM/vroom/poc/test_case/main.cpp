//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//
#include "routing/routed_wrapper.h"
#include "structures/vroom/input/input.h"

#include "utils/exception.h"
#include "util.h"

using namespace std;

void set_vehicule(vroom::Input *problem_instance,vector<vroom::Vehicle> vehicles, string vehicle_filename);
void set_jobs(vroom::Input *problem_instance,vector<vroom::Job> jobs, string job_filename);
void log_solution(const vroom::Solution& sol, bool geometry);

int main(int argc, char *argv[]) {
  //TODO faudras pas oublier de creer un ficher test pour le vehicule histoire
  //de le tester en kind of real condition.
  if(argc != 4){
    cout << "main wrong number of argument :" << argc-1 << endl;
    cout << "usage : " << endl;
    cout << "./test jobs.csv vehicle.csv output_file";
  }
  string input_job_filename = argv[1],
         input_vehicle_filename = argv[2],
         output_filename = argv[3];

  // Set OSRM host and povoid set_vehicule(vroom::Input *problem_instance,vector<vroom::Vehicle> vehicles, string vehicle_filename)rt.
  cout << "set OSRM host and port" << endl;
  auto routing_wrapper = make_unique<vroom::routing::RoutedWrapper>
  ("car",vroom::Server("localhost", "5000"));

  cout << "set vroom Input" << endl;
  vroom::Input problem_instance;
  problem_instance.set_routing(move(routing_wrapper));

  //TODO voir si on a besoin de ca ou pas.
  bool GEOMETRY = true;
  problem_instance.set_geometry(GEOMETRY); // Query for route geometry
  // after solving.
  cout << "set the vehicules" << endl;
  vector<vroom::Vehicle> vehicles;
  set_vehicule(&problem_instance,vehicles,input_vehicle_filename);

  cout << "set the jobs" << endl;
  vector<vroom::Job> jobs;
  set_jobs(&problem_instance,jobs,input_job_filename);

  // Solve!
  try {
    cout << "trying to solve the problem" << endl;
    auto sol = problem_instance.solve(5, 4);
    // Use argv[2] lvl expl and argv[3] threads.
    log_solution(sol, GEOMETRY);
  } catch (const vroom::Exception &e) {
    cerr << "[Error] " << e.message << endl;
  }

  //TODO une fois la solution trouver ecrire la solution dans un nouveau ficher.
  writer(output_filename);
  return 0;
}

void set_vehicule(vroom::Input *problem_instance,vector<vroom::Vehicle>* vehicles, string vehicle_filename) {
  //TODO feras appel a read special pour véhicule (quand ca sera le cas)
  reader(vehicle_filename,"vehicle",NULL,vehicles);

}
void set_jobs(vroom::Input *problem_instance,vector<vroom::Job>* jobs, string job_filename) {
  reader(job_filename,"job",jobs,NULL);
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
