#ifndef VALHALLA_MJOLNIR_OSMDATA_H
#define VALHALLA_MJOLNIR_OSMDATA_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include <valhalla/mjolnir/osmaccessrestriction.h>
#include <valhalla/mjolnir/osmnode.h>
#include <valhalla/mjolnir/osmrestriction.h>
#include <valhalla/mjolnir/osmway.h>
#include <valhalla/mjolnir/uniquenames.h>

namespace valhalla {
namespace mjolnir {

struct OSMBike {
  uint8_t bike_network;
  size_t name_index;
  size_t ref_index;
};

struct OSMLaneConnectivity {
  uint32_t to_way_id;
  uint32_t from_way_id;
  std::string to_lanes;
  std::string from_lanes;
};

using RestrictionsMultiMap = std::unordered_multimap<uint32_t, OSMRestriction>;

using ViaSet = std::unordered_set<uint64_t>;

using AccessRestrictionsMultiMap = std::unordered_multimap<uint64_t, OSMAccessRestriction>;

using BikeMultiMap = std::unordered_multimap<uint64_t, OSMBike>;

using OSMStringMap = std::unordered_map<uint64_t, std::string>;

using OSMLaneConnectivityMultiMap = std::unordered_multimap<uint32_t, OSMLaneConnectivity>;

enum class OSMType : uint8_t { kNode, kWay, kRelation };

struct OSMWayNode {
  OSMNode node;
  size_t way_index;
  size_t way_shape_node_index;
};

/**
 * Simple container for OSM data.
 * Populated by the PBF parser and sent into GraphBuilder.
 *
 */
struct OSMData {
  uint64_t max_changeset_id_; // The largest/newest changeset id encountered when parsing OSM data
  size_t osm_node_count;      // Count of osm nodes
  size_t osm_way_count;       // Count of osm ways
  size_t osm_way_node_count;  // Count of osm nodes on osm ways
  size_t intersection_count;  // Count of intersection nodes
  size_t node_count;          // Count of all nodes
  size_t edge_count;          // Estimated count of edges

  // Stores simple restrictions. Indexed by the from way Id
  RestrictionsMultiMap restrictions;

  // unordered set used to find out if a wayid is in the vector of vias
  ViaSet via_set;

  // Stores access restrictions. Indexed by the from way Id.
  AccessRestrictionsMultiMap access_restrictions;

  // Stores bike information from the relations.  Indexed by the way Id.
  BikeMultiMap bike_relations;

  // Map that stores all the ref info on a node
  OSMStringMap node_ref;

  // Map that stores all the exit_to info on a node
  OSMStringMap node_exit_to;

  // Map that stores all the name info on a node
  OSMStringMap node_name;

  // Map that stores an updated ref for a way
  OSMStringMap way_ref;

  // References
  UniqueNames ref_offset_map;

  // Names
  UniqueNames name_offset_map;

  // Forward turn lane strings
  UniqueNames fwd_turn_lanes_map;

  // Backward turn lane strings
  UniqueNames bwd_turn_lanes_map;

  // Lane connectivity, index by the to way Id
  OSMLaneConnectivityMultiMap lane_connectivity_map;
};

} // namespace mjolnir
} // namespace valhalla

#endif // VALHALLA_MJOLNIR_OSMDATA_H