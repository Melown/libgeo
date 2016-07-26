#ifndef geo_heightcoding_hpp_included_
#define geo_heightcoding_hpp_included_

#include <iostream>
#include <vector>
#include <string>

#include <boost/optional.hpp>

#include "./geodataset.hpp"
#include "./vectorformat.hpp"

namespace geo {

/** Height coding.
 */
struct HeightCodingConfig {
    typedef std::vector<std::string> LayerNames;

    /** Working spatial reference system. Input data in vector dataset) are
     * expected to be in this dataset. Vector Dataset should have vertical
     * component the same as the data in input raster (although GDAL dataset
     * lacks any notion of vertical system).
     *
     * Raster datasets's SRS is used if invalid.
     */
    boost::optional<SrsDefinition> workingSrs;

    /** Spatial reference system of generated output. No conversion is performed
     *  if invalid.
     */
    boost::optional<SrsDefinition> outputSrs;

    /** Perform vertical adjustment of output data.
     */
    bool outputVerticalAdjust;

    /** List of layer names; none -> all layers present in input dataset
     */
    boost::optional<LayerNames> layers;

    /** Output format.
     */
    VectorFormat format;

    HeightCodingConfig()
        : outputVerticalAdjust(false), format(VectorFormat::geodataJson)
    {}
};

/** Height code vector data from vectorDs using height information from
 *  raster dataset rasterDs.
 *
 *  \param vectorDs input vector dataset
 *  \param rasterDs raster dataset used to height code vector data
 *  \param os output stream result is written to
 *  \param config work configuration
 */
void heightCode(::GDALDataset &vectorDs, const GeoDataset &rasterDs
                , std::ostream &os
                , const HeightCodingConfig &config = HeightCodingConfig());


} // namespace geo

#endif // geo_heightcoding_hpp_included_