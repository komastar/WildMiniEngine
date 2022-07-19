//
//  File:   WMGeometryFactory.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMGeometryFactory.h"
#include "Object/WMObject.h"
#include "WMVertex.h"
#include "Graphics/Primitive/WMColor.h"
#include "Graphics/WMGPUBuffer.h"
#include "Math/WMVector3.h"

using namespace WildMini::Object;
using namespace WildMini::Graphics::Geometry;
using namespace WildMini::Graphics::Primitive;
using namespace WildMini::Math;

WMMesh* WMGeometryFactory::MakeBox(WildMini::Graphics::WMGraphicsDevice* device)
{
    static WMMesh* mesh = nullptr;
    if (nullptr == mesh)
    {
        float size = 1.5f;
        mesh = new WMMesh();
        std::vector<WMVector3> positions =
        {
            WMVector3   { -size,  size,  size } //  0
            , WMVector3 {  size,  size,  size } //  1
            , WMVector3 {  size,  size, -size } //  2
            , WMVector3 { -size,  size, -size } //  3
            , WMVector3 { -size, -size,  size } //  4
            , WMVector3 {  size, -size,  size } //  5
            , WMVector3 {  size, -size, -size } //  6
            , WMVector3 { -size, -size, -size } //  7
        };

        std::vector<uint32_t> indicies =
        {
            //  top
            0, 1, 2,
            0, 2, 3,
            //  front
            1, 0, 5,
            0, 4, 5,
            //  back
            3, 2, 6,
            3, 6, 7,
            //  right
            2, 1, 5,
            2, 5, 6,
            //  left
            0, 3, 7,
            0, 7, 4,
            //  bottom
            5, 4, 7,
            5, 7, 6
        };

        std::vector<WMVertex> verticies;
        for (size_t i = 0; i < indicies.size(); ++i)
        {
            WMVector3 p1 = positions[indicies[i]];
            WMVector3 p2 = positions[indicies[++i]];
            WMVector3 p3 = positions[indicies[++i]];
            WMVector3 n = WMVector3::Cross(p2 - p1, p3 - p1).Normalize();
            WMVertex v1 = { p1, n, WMColor::white };
            WMVertex v2 = { p2, n, WMColor::white };
            WMVertex v3 = { p3, n, WMColor::white };
            verticies.push_back(v1);
            verticies.push_back(v2);
            verticies.push_back(v3);
        }

        mesh->vertices = verticies;

        WMObject<WMGPUBuffer> vertexBuffer;
        vertexBuffer = device->CreateGPUBuffer(mesh->vertices.size() * sizeof(WMVertex), WMGPUBuffer::CPUCacheMode::WRITABLE);
        vertexBuffer->WriteData(mesh->vertices.data(), mesh->vertices.size() * sizeof(WMVertex));
        mesh->vertexBuffer = vertexBuffer;
    }

    return mesh;
}
