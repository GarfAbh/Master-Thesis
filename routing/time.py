#!/usr/bin/python
# coging=utf-8

"""
Time routing module
===================

Usefull function about the time management in TuxyRoad for vroom

"""

#standard lib
from typing import Dict
import datetime

DAY_IN_SEC = 86400 #number of second for 1 day

def correct_in_time(vehics_jobs: Dict) -> Dict:
    """
    correct all time in input i.e if in time_window [a,b] b < a add 1 day to b

    :param vehics_jobs: dict composed with list of vehicles and list of jobs
    :return: the input with the correct time
    """

    for vehic in enumerate(vehics_jobs['vehicles']):
        start = string_to_sec(vehic[1]['time_window'][0])
        end = string_to_sec(vehic[1]['time_window'][1])
        vehic[1]['time_window'][0] = start
        vehic[1]['time_window'][1] = end
        if end < start:
            vehic[1]['time_window'][1] = end + DAY_IN_SEC


    for job in enumerate(vehics_jobs['jobs']):
        if 'time_windows' in job[1].keys():
            for i, tw in enumerate(job[1]['time_windows']):
                start = string_to_sec(job[1]['time_windows'][i][0])
                end = string_to_sec(job[1]['time_windows'][i][1])
                job[1]['time_windows'][i][0] = start
                job[1]['time_windows'][i][1] = end
                if end < start:
                    job[1]['time_windows'][i][1] = end + DAY_IN_SEC

        job[1]['service'] = string_to_sec(job[1]['service'])
    return vehics_jobs


def correct_out_time(vroom_otp: Dict) -> Dict:
    """
    correct all time in input if in [a,b] b > DAY_IN_SEC substract 1 day to b

    :param vroom_otp: vroom's output
    :return: vroom's output with the correct time
    """
    for route in vroom_otp['routes']:
        for step in route['steps']:
            if step['arrival'] > DAY_IN_SEC:
                step['arrival'] = step['arrival'] - DAY_IN_SEC

    return vroom_otp


def second_to_string(time: int) -> str:
    """
    Convert second to string time ISO8601 standard

    :param time: time in second
    :return: formated string  hh:mm:ss

    :Example:

    >>> second_to_string(666)
    '0:11:06'
    """
    return str(datetime.timedelta(seconds=time))


def string_to_sec(time: str) -> int:
    """
    convert time string hh:mi:ss into seconds

    :param time: string representation of time
    :return: number of second time represent

    :Example:

    >>>string_to_sec('0:11:06')
    666

    """
    t_s = time.split(':')
    return int(t_s[0]) * 3600 + int(t_s[1]) * 60 + int(t_s[2])


def standardize_time(vroom_otp: Dict) -> Dict:
    """
    take all the time in the output and standardize it in ISO8601

    :param vroom_otp: vroom's output with the corrected seconds
    :return: vroom's output with standard time
    """
    summary = vroom_otp['summary']
    vroom_otp['summary']['cost'] = second_to_string(summary['cost'])
    vroom_otp['summary']['service'] = second_to_string(summary['service'])
    vroom_otp['summary']['duration'] = second_to_string(summary['duration'])
    vroom_otp['summary']['waiting_time'] = second_to_string(summary['waiting_time'])

    for route in vroom_otp['routes']:
        route['cost'] = second_to_string(route['cost'])
        route['service'] = second_to_string(route['service'])
        route['duration'] = second_to_string(route['duration'])
        route['waiting_time'] = second_to_string(route['waiting_time'])
        for step in route['steps']:
            if step['type'] == "job":
                step['service'] = second_to_string(step['service'])
                step['waiting_time'] = second_to_string(step['waiting_time'])
            step['duration'] = second_to_string(step['duration'])
            step['arrival'] = second_to_string(step['arrival'])

    return vroom_otp
