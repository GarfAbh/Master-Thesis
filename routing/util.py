#!/usr/bin/python
# coging=utf-8

"""
Util routing module
===================

Use to get some usefull fonction for the routing as a json verifier

:Example:

>>> json_is_ok({
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
      "location" : [6.631371,46.51953],
      "time_windows" : [[21600,31200]]
    }]
})
"""
#standard lib
from typing import Dict
import configparser
from subprocess import Popen, PIPE
import json

CONFIG = configparser.ConfigParser()
CONFIG.read('config.ini')
PATH_TO_EXEC = CONFIG['DEFAULT']['PATH_TO_EXEC']
OSRM_PORT = CONFIG['DEFAULT']['OSRM_PORT']


def json_is_ok(vehics_jobs: Dict) -> bool:
    """
    Check that the given json is correctly formated

    :param vehics_jobs: dict composed with list of vehicles and list of jobs
    :return: True if correctly formated, False otherwise

    :Example:

    >>> json_is_ok({
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
          "location" : [6.631371,46.51953],
          "time_windows" : [[21600,31200]]
        }]
    })
    """
    is_ok = True
    if all(k in vehics_jobs.keys() for k in ('vehicles', 'jobs')):
        for vehic in enumerate(vehics_jobs['vehicles']):
            if all(l in vehic[1].keys() for l in ('id', 'start', 'end', 'capacity', 'time_window')):
                continue
            else:
                is_ok = False
        for job in enumerate(vehics_jobs['jobs']):
            if all(l in job[1].keys() for l in ('id', 'service', 'amount', 'location','priority')):
                continue
            else:
                is_ok = False
    else:
        is_ok = False
    return is_ok


def send_to_vroom(vehics_jobs: Dict) -> Dict:
    """
    run an instance of vroom with the json given in arg

    :param vehics_jobs: dict composed with list of vehicles and list of jobs
    :return: the decoded output of vroom which is a json

    :Example:

    >>> send_to_vroom({
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
          "location" : [6.631371,46.51953],
          "time_windows" : [[21600,31200]]
        }]
    })

    """
    pop = Popen([PATH_TO_EXEC+'/vroom_exec',
                 json.dumps(vehics_jobs)],
                stdin=PIPE,
                stdout=PIPE)
    return json.loads(pop.stdout.read().decode("utf-8"))
