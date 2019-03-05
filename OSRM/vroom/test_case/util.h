//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//

#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

//external lib
#include <boost/algorithm/string.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/adaptor/indexed.hpp>

//external code
#include "structures/vroom/job.h"
#include "structures/vroom/vehicle.h"
#include "structures/vroom/input/input.h"
#include "routing/routed_wrapper.h"

//internal code
#include "debug.h"

void reader(std::string filename,
            std::string kind,
            std::vector<vroom::Job>* jobs,
            std::vector<vroom::Vehicle>* vehicles);

void writer(std::string filename,const vroom::Solution& sol, bool geometry);
void format_input(std::vector<vroom::Job>* jobs,
                  std::vector<vroom::Vehicle>* vehicles,
                  std::string output_filename);
vroom::Job create_new_job(std::vector<std::string> job_param);
vroom::Vehicle create_new_vehicle(std::vector<std::string> vehicle_param);
std::string sec_to_formated_string(int nb_sec);
int string_to_sec(std::string duraction);
std::string format_distance(int nb_m);

int total_cost();
int service_time(int index);
std::string get_arrival(int index);
