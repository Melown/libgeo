#ifndef geo_srsdef_hpp_included_
#define geo_srsdef_hpp_included_

#include <string>
#include "math/geometry.hpp"

#include "utility/enum-io.hpp"

// forward declaration
class OGRSpatialReference;

namespace geo {

struct SrsDefinition {
    enum class Type { proj4, wkt, epsg };

    std::string srs;
    Type type;

    SrsDefinition() : srs(), type(Type::proj4) {}
    SrsDefinition(const std::string &srs) : srs(srs), type(Type::proj4) {}
    SrsDefinition(const std::string &srs, Type type) : srs(srs), type(type) {}

    SrsDefinition as(Type type) const;

    const std::string& string() const { return srs; }
    const char* c_str() const { return srs.c_str(); }

    OGRSpatialReference reference() const;

    static SrsDefinition longlat();
    static SrsDefinition utm(uint zone, bool isNorth = true );
    static SrsDefinition utmFromLonglat(const math::Point2 & longlat );
};

enum class SrsEquivalence { both, geographic, vertical };

bool areSame(const SrsDefinition &def1, const SrsDefinition &def2
             , SrsEquivalence type = SrsEquivalence::both);


UTILITY_GENERATE_ENUM_IO(SrsDefinition::Type,
    ((proj4))
    ((wkt))
    ((epsg))
)

} // namespace geo

#endif // geo_srsdef_hpp_included_
