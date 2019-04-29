#!/usr/bin/python
# coging=utf-8

"""
Priority routing module
=======================

Use to manage the priority while calling the vroom service

"""
#standard lib
from typing import Dict, List, NamedTuple
from itertools import combinations
#local application/lib import
from . import util
from . import time


def job_sort_priority(vehics_jobs: Dict) -> NamedTuple:
    """
    Sort the jobs using their priority. Output 1 list per priority

    :param vehics_jobs: dict composed with list of vehicles and list of jobs
    :return: first the list of all the have to be done jobs, second the list of
    all the nice to be done jobs.

    :Example:

    >>> job_sort_priority({
      "vehicles":[
        {
          "id":601,
          "start": [6.68973,46.50190],
          "end": [6.64357,46.50910],
          "capacity": [100],
          "time_window" : [21600, 61200]
        }
      ],
      "jobs": [
        {
          "id": 48968,
          "service" : 720,
          "amount" : [1],
          "priority" : 1,
          "location" : [6.631371,46.51953]
        }]
    })

    first_priority has 1 element. second_priority is empty.

    """
    first_priority = []
    second_priority = []
    for job in enumerate(vehics_jobs['jobs']):
        if job[1]['priority'] == 1:
            first_priority.append(job[1])
        else:
            second_priority.append(job[1])

    return first_priority, second_priority


def add_job(vehics_jobs: Dict, job: Dict) -> Dict:
    """
    Add a new job to the current input

    :param vehics_jobs: dict composed with list of vehicles and list of jobs
    :param job: new job to add
    :return: a new input with the added job

    :Example:

    >>> job_sort_priority({
      "vehicles":[
        {
          "id":601,
          "start": [6.68973,46.50190],
          "end": [6.64357,46.50910],
          "capacity": [100],
          "time_window" : [21600, 61200]
        }
      ],
      "jobs": [
        {
          "id": 48968,
          "service" : 720,
          "amount" : [1],
          "priority" : 1,
          "location" : [6.631371,46.51953]
        }]
    }),
    {
      "id": 12458,
      "service" : 720,
      "amount" : [1],
      "priority" : 2,
      "location" : [6.631371,46.51953]
    }

    """
    jobs_list = vehics_jobs['jobs'].copy()
    jobs_list.append(job)
    return {
        'vehicles' : vehics_jobs['vehicles'],
        'jobs' : jobs_list
    }


def remove_duplicates(jobs_comb: List) -> List:
    """
    remove the combinations that are included in other one.
    To keep only the most complete combinations of jobs
    [(456),(456,12)] -> [(456,12)]
    (456) is already in the second tuple so we don't need
    to count it as unique value

    :param jobs_comb: List of tuple containing all the possible combinations of jobs
    :return: jobs_comb withouth any combination include in an other one


    :Example:

    >>> remove_duplicates([(1),(1,2),(1,2,3),(4)])
    [(1,2,3),(4)]

    """
    to_del = []
    for comb in jobs_comb:
        for check in jobs_comb:
            if sorted(comb) != sorted(check):
                if set(comb).issubset(check):
                    to_del.append(comb)
                    break

    for elem in to_del:
        jobs_comb.remove(elem)
    return jobs_comb


Result = List[Dict]
def handle_jobs_priority(vehics_jobs: Dict) -> Result:
    """
    Handle the whole process for managing 2 priority level with vroom.
    first check if the must have jobs are doable or not.
    if not return the output
    if yes try to add some nice to have job in order to obtain a full List
    of vroom output with all the possible add

    :param vehics_jobs: dict composed with list of vehicles and list of jobs
    :return: a list of dict corresponding each of them to one ouput of vroom

    """
    correct_input = time.correct_in_time(vehics_jobs)
    jobs_must_to_have, jobs_nice_to_have = job_sort_priority(correct_input)

    vj_must_to_have = {
        'vehicles' : correct_input['vehicles'],
        'jobs' : jobs_must_to_have
    }

    vroom_must = util.send_to_vroom(vj_must_to_have)
    if vroom_must['summary']['unassigned'] != 0 or not jobs_nice_to_have:
        return [time.standardize_time(time.correct_out_time(vroom_must))]

    ids = set()
    job_to_del = set()
    id_to_job = dict()
    for job in jobs_nice_to_have:
        ids.add(job['id'])
        id_to_job[job['id']] = job

    tmp_ids = ids.copy()
    final_jobs_comb = []
    i = 1
    while i <= len(tmp_ids):
        jobs_comb = list(combinations(ids, i))
        job_to_del = tmp_ids.copy()

        for comb in jobs_comb:
            tmp_input = vj_must_to_have
            for job_id in list(comb):
                tmp_input = add_job(tmp_input, id_to_job[job_id])
            tmp_output = util.send_to_vroom(tmp_input)
            if tmp_output['summary']['unassigned'] == 0:
                for job in comb:
                    if job in job_to_del:
                        job_to_del.remove(job)
                final_jobs_comb.append(comb)

        tmp_ids = tmp_ids - job_to_del
        i += 1

    if not final_jobs_comb:
        return [time.standardize_time(time.correct_out_time(vroom_must))]

    final_jobs_comb = remove_duplicates(final_jobs_comb)
    final_output_list = []

    for jobs_comb in final_jobs_comb:
        tmp_input = vj_must_to_have
        for job_id in list(jobs_comb):
            tmp_input = add_job(tmp_input, id_to_job[job_id])
        tmp_output = util.send_to_vroom(tmp_input)
        tmp_output = time.standardize_time(time.correct_out_time(tmp_output))
        unassigned_ids = ids.copy()-set(jobs_comb)
        ids_list = list()
        for uid in unassigned_ids:
            ids_list.append({'id':uid})
        tmp_output['unassigned'] = list(ids_list)
        final_output_list.append(tmp_output)

    return final_output_list
