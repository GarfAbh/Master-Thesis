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
      "location" : [6.631371,46.51953]
    }]
})
"""
#standard lib
from typing import Dict

def json_is_ok(vehics_jobs: Dict) -> bool:
    """
    Check that the given json is correctly formated

    :param vehics_jobs: json object with 2 list
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
          "location" : [6.631371,46.51953]
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
            if all(l in job[1].keys() for l in ('id', 'service', 'amount', 'location')):
                continue
            else:
                is_ok = False
    else:
        is_ok = False
    return is_ok
