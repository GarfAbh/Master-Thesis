Language : Python 3.5

Librairie à installer :

- fuzzywuzzy : https://github.com/seatgeek/fuzzywuzzy (pip install fuzzywuzzy)
- flask : pip install flask

Base de donnée :

- openaddresses : https://openaddresses.io/

Usage :

def geocode():
  geocoder.init_db()
  data = request.get_json()

  match = []
  for i,object in enumerate(data):
        if 'address' in object.keys():
            match.append(util.to_json_object((object['ID'],geocoder.handle_string(object['address']))))
        else:
            match.append(util.to_json_object(geocoder.handle_object(object)))
  
