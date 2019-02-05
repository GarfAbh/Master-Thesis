#ifndef OSMIUM_INDEX_MAP_HPP
#define OSMIUM_INDEX_MAP_HPP

/*

This file is part of Osmium (http://osmcode.org/libosmium).

Copyright 2013-2018 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <osmium/util/string.hpp>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace osmium {

    struct map_factory_error : public std::runtime_error {

        explicit map_factory_error(const char* message) :
            std::runtime_error(message) {
        }

        explicit map_factory_error(const std::string& message) :
            std::runtime_error(message) {
        }

    }; // struct map_factory_error

    namespace index {

        /**
         * @brief Key-value containers with unique integer values for a key
         */
        namespace map {

            /**
             * This abstract class defines an interface to storage classes
             * intended for storing small pieces of data (such as coordinates)
             * indexed by a positive integer (such as an object ID). The
             * storage must be very space efficient and able to scale to billions
             * of objects.
             *
             * Subclasses have different implementations that store the
             * data in different ways in memory and/or on disk. Some storage
             * classes are better suited when working with the whole planet,
             * some are better for data extracts.
             *
             * Note that these classes are not required to track "empty" fields.
             * When reading data you have to be sure you have put something in
             * there before.
             *
             * A typical use for this and derived classes is storage of node
             * locations indexed by node ID. These indexes will only work
             * on 64 bit systems if used in this case. 32 bit systems just
             * can't address that much memory!
             *
             * @tparam TId Id type, usually osmium::unsigned_object_id_type,
             *             must be an unsigned integral type.
             * @tparam TValue Value type, usually osmium::Location or size_t.
             *                Copied by value, so should be "small" type.
             */
            template <typename TId, typename TValue>
            class Map {

                static_assert(std::is_integral<TId>::value && std::is_unsigned<TId>::value,
                              "TId template parameter for class Map must be unsigned integral type");

            protected:

                Map(Map&&) noexcept = default;
                Map& operator=(Map&&) noexcept = default;

            public:

                /// The "key" type, usually osmium::unsigned_object_id_type.
                using key_type = TId;

                /// The "value" type, usually a Location or size_t.
                using value_type = TValue;

                Map() noexcept = default;

                Map(const Map&) = delete;
                Map& operator=(const Map&) = delete;

                virtual ~Map() noexcept = default;

                virtual void reserve(const size_t /*size*/) {
                    // default implementation is empty
                }

                /// Set the field with id to value.
                virtual void set(const TId id, const TValue value) = 0;

                /**
                 * Retrieve value by id.
                 *
                 * @param id The id to look for.
                 * @returns Value.
                 * @throws osmium::not_found if the id could not be found.
                 */
                virtual TValue get(const TId id) const = 0;

                /**
                 * Retrieve value by id.
                 *
                 * @param id The id to look for.
                 * @returns Value or, if not found, the empty value as defined
                 *          by osmium::index::empty_value<TValue>() which is
                 *          usually the default constructed value of type
                 *          TValue.
                 */
                virtual TValue get_noexcept(const TId id) const noexcept = 0;

                /**
                 * Get the approximate number of items in the storage. The storage
                 * might allocate memory in blocks, so this size might not be
                 * accurate. You can not use this to find out how much memory the
                 * storage uses. Use used_memory() for that.
                 */
                virtual size_t size() const = 0;

                /**
                 * Get the memory used for this storage in bytes. Note that this
                 * is not necessarily entirely accurate but an approximation.
                 * For storage classes that store the data in memory, this is
                 * the main memory used, for storage classes storing data on disk
                 * this is the memory used on disk.
                 */
                virtual size_t used_memory() const = 0;

                /**
                 * Clear memory used for this storage. After this you can not
                 * use the storage container any more.
                 */
                virtual void clear() = 0;

                /**
                 * Sort data in map. Call this after writing all data and
                 * before reading. Not all implementations need this.
                 */
                virtual void sort() {
                    // default implementation is empty
                }

                // This function can usually be const in derived classes,
                // but not always. It could, for instance, sort internal data.
                // This is why it is not declared const here.
                virtual void dump_as_list(const int /*fd*/) {
                    throw std::runtime_error{"can't dump as list"};
                }

                // This function can usually be const in derived classes,
                // but not always. It could, for instance, sort internal data.
                // This is why it is not declared const here.
                virtual void dump_as_array(const int /*fd*/) {
                    throw std::runtime_error{"can't dump as array"};
                }

            }; // class Map

        } // namespace map

        template <typename TId, typename TValue>
        class MapFactory {

        public:

            using id_type         = TId;
            using value_type      = TValue;
            using map_type        = osmium::index::map::Map<id_type, value_type>;
            using create_map_func = std::function<map_type*(const std::vector<std::string>&)>;

        private:

            std::map<const std::string, create_map_func> m_callbacks;

            MapFactory() = default;

            ~MapFactory() = default;

        public:

            MapFactory(const MapFactory&) = delete;
            MapFactory& operator=(const MapFactory&) = delete;

            MapFactory(MapFactory&&) = delete;
            MapFactory& operator=(MapFactory&&) = delete;

            static MapFactory<id_type, value_type>& instance() {
                static MapFactory<id_type, value_type> factory;
                return factory;
            }

            bool register_map(const std::string& map_type_name, create_map_func func) {
                return m_callbacks.emplace(map_type_name, func).second;
            }

            bool has_map_type(const std::string& map_type_name) const {
                return m_callbacks.count(map_type_name) != 0;
            }

            std::vector<std::string> map_types() const {
                std::vector<std::string> result;

                for (const auto& cb : m_callbacks) {
                    result.push_back(cb.first);
                }

                std::sort(result.begin(), result.end());

                return result;
            }

            std::unique_ptr<map_type> create_map(const std::string& config_string) const {
                std::vector<std::string> config{osmium::split_string(config_string, ',')};

                if (config.empty()) {
                    throw map_factory_error{"Need non-empty map type name"};
                }

                const auto it = m_callbacks.find(config[0]);
                if (it != m_callbacks.end()) {
                    return std::unique_ptr<map_type>((it->second)(config));
                }

                throw map_factory_error{std::string{"Support for map type '"} + config[0] + "' not compiled into this binary"};
            }

        }; // class MapFactory

        namespace map {

            template <typename TId, typename TValue, template <typename, typename> class TMap>
            struct create_map {
                TMap<TId, TValue>* operator()(const std::vector<std::string>& /*config_string*/) {
                    return new TMap<TId, TValue>();
                }
            };

        } // namespace map

        template <typename TId, typename TValue, template <typename, typename> class TMap>
        inline bool register_map(const std::string& name) {
            return osmium::index::MapFactory<TId, TValue>::instance().register_map(name, [](const std::vector<std::string>& config) {
                return map::create_map<TId, TValue, TMap>()(config);
            });
        }

#define OSMIUM_CONCATENATE_DETAIL_(x, y) x##y
#define OSMIUM_CONCATENATE_(x, y) OSMIUM_CONCATENATE_DETAIL_(x, y)

#define REGISTER_MAP(id, value, klass, name) \
namespace osmium { namespace index { namespace detail { \
    namespace OSMIUM_CONCATENATE_(register_map_, __COUNTER__) { \
    const bool registered = osmium::index::register_map<id, value, klass>(#name); \
    inline bool get_registered() noexcept { \
        return registered; \
    } } \
} } }

    } // namespace index

} // namespace osmium

#endif // OSMIUM_INDEX_MAP_HPP
