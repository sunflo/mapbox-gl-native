#pragma once

#include <mbgl/renderer/bucket.hpp>
#include <mbgl/tile/geometry_tile_data.hpp>
#include <mbgl/gl/vertex_buffer.hpp>
#include <mbgl/gl/index_buffer.hpp>
#include <mbgl/programs/segment.hpp>
#include <mbgl/programs/fill_program.hpp>
#include <mbgl/style/layers/fill_layer_properties.hpp>

#include <vector>

namespace mbgl {

class BucketParameters;
class RenderFillLayer;

class FillBucket final : public Bucket {
public:
    ~FillBucket() override;
    // These aliases are used by the PatternLayout template
    using RenderLayerType = RenderFillLayer;
    using PossiblyEvaluatedPaintProperties = style::FillPaintProperties::PossiblyEvaluated;
    using PossiblyEvaluatedLayoutProperties = style::Properties<>::PossiblyEvaluated;

    FillBucket(const PossiblyEvaluatedLayoutProperties layout,
               std::map<std::string, PossiblyEvaluatedPaintProperties> layerPaintProperties,
               const float zoom,
               const uint32_t overscaling);

    void addFeature(const GeometryTileFeature&,
                    const GeometryCollection&,
                    const mbgl::ImagePositions&,
                    const PatternLayerMap&) override;

    bool hasData() const override;

    void upload(gl::Context&) override;

    float getQueryRadius(const RenderLayer&) const override;
    bool supportsLayer(const style::Layer::Impl&) const override;

    gl::VertexVector<FillLayoutVertex> vertices;
    gl::IndexVector<gfx::Lines> lines;
    gl::IndexVector<gfx::Triangles> triangles;
    SegmentVector<FillAttributes> lineSegments;
    SegmentVector<FillAttributes> triangleSegments;

    optional<gl::VertexBuffer<FillLayoutVertex>> vertexBuffer;
    optional<gl::IndexBuffer<gfx::Lines>> lineIndexBuffer;
    optional<gl::IndexBuffer<gfx::Triangles>> triangleIndexBuffer;

    std::map<std::string, FillProgram::Binders> paintPropertyBinders;
};

} // namespace mbgl
