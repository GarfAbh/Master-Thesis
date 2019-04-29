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
#related third party import
from flask import Flask, request, Response
#local application/lib import
from geocoder import util as gu
from geocoder import geocoder
from routing import util as ru
from routing import time as t
from routing import priority as prio

APP = Flask(__name__)


#curl -XPOST --header 'Content-Type:application/json'
#--data @Geocoder/input_output/input3.json 127.0.0.1:5000/geocode
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
#--data @Routing/input_output/input1.json 127.0.0.1:5000/vroom
@APP.route('/vroom', methods=['POST'])
def vroom():
    """
    Compute the vroom request on the server.

    :Example:
    /vroom /path/to/json
    """
    data = request.get_json()
    if ru.json_is_ok(data):
        vroom_otp = prio.handle_jobs_priority(data)
        response = APP.response_class(
            response=json.dumps(vroom_otp),
            status=200,
            mimetype='application/json'
        )
        return response
    return Response("le json n'est pas formaté corectement\n", status=400)

print("initialize db")
geocoder.init_db()
print("db initialized")
APP.run()
