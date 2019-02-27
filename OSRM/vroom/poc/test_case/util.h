//
// Created by Arnaud Boissaye-Heaume on 2019-02-13.
//

#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//external lib
#include <boost/algorithm/string.hpp>

//external code
#include "structures/vroom/job.h"
#include "structures/vroom/vehicle.h"

void reader(std::string filename,
            std::string kind,
            std::vector<vroom::Job>* jobs,
            std::vector<vroom::Vehicle>* vehicles);
void writer(std::string filename);
vroom::Job create_new_job(std::vector<std::string> job_param);
vroom::Vehicle create_new_vehicle(std::vector<std::string> vehicle_param);
