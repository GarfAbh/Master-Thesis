#!/usr/bin/python
# coging=utf-8

"""
Frontend server
===============

Use to run a flask API for TuxyRoad

:Example:

/geocode /path/to/json

/vroom /path/to/json
"""

#standard lib
import json
import configparser
#related third party import
from flask import Flask, request, Response, g
from requests import get
#local application/lib import
from geocoder import util as gu
from geocoder import geocoder
from routing import util as ru
from routing import time as t
from routing import priority as prio

CONFIG = configparser.ConfigParser()
CONFIG.read('config.ini')
OSRM_PORT = CONFIG['DEFAULT']['OSRM_PORT']

APP = Flask(__name__)
SITE_NAME = '0.0.0.0:' + OSRM_PORT
MALUS = 0

#curl -XPOST --header 'Content-Type:application/json'
#--data @geocoder/input_output/input3.json 0.0.0.0:5000/geocode
@APP.route('/geocode', methods=['POST'])
def geocode():
    """
    Compute the geocoder request on the server.

    :Example:
    /geocode /path/to/json
    """


    data = request.get_json()
    if gu.json_is_ok(data):
        match = []
        for addr in enumerate(data):
            if 'address' in addr[1].keys():
                match.append(gu.to_json_object((addr[1]['ID'],
                                                geocoder.handle_addr_literal(addr[1]['address']))))
            else:
                match.append(gu.to_json_object(geocoder.handle_formated_addr(addr[1])))
        response = APP.response_class(
            response=json.dumps(match),
            status=200,
            mimetype='application/json'
        )
        return response
    return Response("Le json n'est pas formaté correctement\n", status=400)


#curl -X POST --header 'Content-Type:application/json'
#--data @routing/input_output/input1.json 0.0.0.0:5000/vroom?malus=20
@APP.route('/vroom', methods=['POST'])
def vroom():
    """
    Compute the vroom request on the server.

    :Example:
    /vroom /path/to/json
    /vroom?malus=x /path/to/json

    malus has to be a float greater than 0
    """
    global MALUS
    data = request.get_json()
    if ru.json_is_ok(data):
        MALUS = request.args.get('malus',0)
        vroom_otp = prio.handle_jobs_priority(data)
        response = APP.response_class(
            response=json.dumps(vroom_otp),
            status=200,
            mimetype='application/json'
        )
        return response
    return Response("le json n'est pas formaté corectement\n", status=400)


@APP.route('/', defaults={'path':''})
@APP.route('/<path:path>')
def proxy(path):
    """
    This is a proxy for the communication that vroom could do with OSRM
    The objective is to get the request and modify the responses to give
    a malus to every duration in the matrix.
    """
    global MALUS
    response = get(("http://{sname}/{p}").format(sname=SITE_NAME,p=path)).content
    json_response = json.loads(response.decode('utf-8'))
    mat = json_response['durations']
    for line in mat:
        for i, elem in enumerate(line):
            line[i] = elem + (elem * float(MALUS) / 100) + 120
    json_response['duration'] = mat
    response = json.dumps(json_response)
    return response

print("initialize db")
geocoder.init_db()
print("db initialized")
APP.run(host='0.0.0.0',port=5000)
