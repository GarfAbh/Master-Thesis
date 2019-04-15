#!/usr/bin/python
# coging=utf-8
"""
Util geocoder module
====================

Use to get some usefull fonction for the geocoder as a json verifier
a json creator and a converter

:Example:

>>> json_is_ok([
  {
    "ID":"1",
    "address":"Avenue C-F Ramuz 95, 1009 Pully"
  }
  ])

>>> mn95_to_wgs84("12","13")

>>> to_json_object(("ID",("address",("match","%match",("longitude","latitude")))))
"""
#standard lib
from typing import Tuple, Dict


def json_is_ok(address: Dict) -> bool:
    """
    Check that the given json is correctly formated

    :param address: json list of object
    :return: True if correctly formated, False otherwise

    :Example:

    >>> json_is_ok([
      {
        "ID":"1",
        "address":"Avenue C-F Ramuz 95, 1009 Pully"
      }
      ])
    """
    is_ok = True
    for addr in enumerate(address):
        if all(k in addr[1].keys() for k in ('ID', 'address')):
            continue
        elif all(k in addr[1].keys() for k in ('ID', 'rue', 'NPA', 'ville')):
            continue
        else:
            is_ok = False
    return is_ok


Wgs84 = Tuple[str, str]
def mn95_to_wgs84(y: str, x: str) -> Wgs84:
    """
    Convert CH1903 - MN95 coordinate to WGS84 coordinate

    This function is base on the official paper from the swiss confederation

    :param y: East coordinate
    :param x: North coordinate
    :return: a tuple composed with longitude and latitude

    :Example:

    >>> mn95_to_wgs84("12","13")
    """
    y_p = (float(y)-2600000)/1000000
    x_p = (float(x)-1200000)/1000000

    longitude = (2.6779094
                 + 4.728982  * y_p
                 + 0.791484  * y_p * x_p
                 + 0.1306    * y_p * x_p**2
                 - 0.0436    * y_p**3)

    latitude = (16.9023892
                + 3.238272   * x_p
                - 0.270978   * y_p**2
                - 0.002528   * x_p**2
                - 0.0447     * y_p**2 * x_p
                - 0.0140     * x_p**3)

    longitude = longitude * 100/36
    latitude = latitude * 100/36

    return (str(longitude), str(latitude))


Tup = Tuple[str, Tuple[str, Tuple[str, str, Tuple[str, str]]]]
def to_json_object(response: Tup) -> Dict:
    """
    Create a json object from the given input.

    :param response: tuple composed with ID, input addr, match addr,
    %match long and lat

    :return: json object correctly formated

    :Example:
    >>> to_json_object(("ID",("address",("match","%match",("longitude","latitude")))))
    """
    return {'ID' : response[0],
            'input': response[1][0],
            'matching' : response[1][1][1],
            'matched_addr': response[1][1][0],
            'coordinate' : {
                'longitude' : response[1][1][2][0],
                'latitude' : response[1][1][2][1]
                }
            }
