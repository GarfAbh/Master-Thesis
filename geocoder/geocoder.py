#!/usr/bin/python
# coging=utf-8

"""
Geocoder module
===============

Use to do the geocoding on different input.
Need the swiss federal data base to work properly.

:Example:

>>> find_match("Avenue Charles Ferdinand Ramuz 95, 1009 Pully",1009)

>>> handle_addr_literal("Avenue Charles Ferdinand Ramuz 95, 1009 pully")

>>> handle_formated_addr({
                      "ID" : "1",
                      "rue":"Avenue Charles Ferdinand Ramuz 95",
                      "NPA":"1009",
                      "ville":"Pully"
})


"""

#standard lib
import re
import os
import configparser
from typing import Dict, Tuple
#related third party import
from fuzzywuzzy import fuzz
from pandas import pandas as pd
#local application/lib import
from . import util


CONFIG = configparser.ConfigParser()
print(CONFIG.read('config.ini'))
PATH_TO_DATA = CONFIG['DEFAULT']['PATH_TO_DATA']


def init_db():
    """
    Initialize the data base about all the address coming from the confederation

    This get into the memory the DB from the swiss federal institute.
    It then filter the DB to be sure to have all the needed value to be
    able to do the comparison.

    :param: None
    :return: None

    :Example:

    >>> init_db()
    """
    global DB
    DB = pd.read_csv(os.path.abspath(PATH_TO_DATA+'/Addr/CH.csv'), sep=';')
    DB = DB[DB.STRNAME.notnull()]
    DB = DB[DB.PLZ4.notnull()]
    DB = DB[DB.DEINR.notnull()]
    DB = DB[DB.PLZNAME.notnull()]
    DB = DB[DB.GKODE.notnull()]
    DB = DB[DB.GKODN.notnull()]


Match = Tuple[str, str, Tuple[str, str]]
def find_match(addr: str, postal_code: str) -> Match:
    """
    Compare the input address to the data base to find the best match

    It use the NPA to optimize the time search and the efficiency.

    :param addr: the address to test
    :param postal_code: the NPA to otpimise the search
    :return: a tupple composed with the match, % of match, longitude, latitude

    :Example:
    >>> find_match("Avenue Charles Ferdinand Ramuz 95, 1009 Pully",1009)
    """
    global DB
    best = 0
    best_match = ()
    if DB[DB['PLZ4'] == int(postal_code)].empty:
        best_match = ("code postal non trouvé", 0, (0, 0))
    else:
        for row in DB[DB['PLZ4'] == int(postal_code)].iterrows():
            addr_tmp = row[1]['STRNAME'] + " " + str(row[1]['DEINR']) + ", " +\
                         str(row[1]['PLZ4']) + " " + row[1]['PLZNAME']
            ratio_tmp = fuzz.ratio(addr, addr_tmp)
            if ratio_tmp > best:
                best = ratio_tmp
                best_match = (addr_tmp, best, (str(row[1]['GKODE']), str(row[1]['GKODN'])))
    return (best_match[0], best_match[1], util.mn95_to_wgs84(best_match[2][0], best_match[2][1]))



def handle_addr_literal(addr_literal: str):
    """
    Manage a literal address through the whole process

    Take the literal address and get the NPA from it
    Then pass all the needed param to find_match

    :param addr_literal: the address in one string
    :return: a tupple composed with the addr_lit and the output of find_match

    :Example:
    >>> handle_addr_literal("Avenue Charles Ferdinand Ramuz, 1009 Pully")
    """

    npa = re.search(r'[0-9]{4}', addr_literal).group(0)
    return (addr_literal, find_match(addr_literal, npa))


def handle_formated_addr(formated_addr: Dict):
    """
    Manage a formated address through the whole process

    form a literal address to give as param to find_match with the NPA

    :param formated_addr: the address in a json object with multiple fields
    rue, NPA, ville, ID.
    :return: a tupple composed with the literal formed address
    and the output of find_match

    :Example:
    >>> handle_formated_addr({
                          "ID" : "1",
                          "rue":"Avenue Charles Ferdinand Ramuz 95",
                          "NPA":"1009",
                          "ville":"Pully"
    })
    """
    addr_lit = formated_addr['rue'] + ", " + formated_addr['NPA'] + " " + formated_addr['ville']
    return (formated_addr['ID'], (addr_lit, find_match(addr_lit, formated_addr['NPA'])))
