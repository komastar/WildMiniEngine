//
//  File:   WMGeometryFactory.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMGeometryFactory.h"
#include "WMSharedPtr.h"
#include "Graphics/Geometry/WMVertex.h"
#include "Graphics/WMGPUBuffer.h"
#include "Math/WMVector3.h"
#include "WMContainer.h"

using namespace WildMini;

WMMesh* WMGeometryFactory::MakeDefaultBox(WMGraphicsDevice* device)
{
    static WMMesh* mesh = nullptr;
    if (nullptr == mesh)
    {
        mesh = MakeBox(device, 0.5f);
    }

    return mesh;
}

WMMesh* WMGeometryFactory::MakeBox(WMGraphicsDevice* device, float size)
{
    WMMesh* mesh = new WMMesh();
    Vector<WMVector3> positions =
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

    Vector<uint32_t> indicies =
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

    Vector<WMVertex> verticies;
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

    WMSharedPtr<WMGPUBuffer> vertexBuffer;
    vertexBuffer = device->CreateGPUBuffer(mesh->vertices.size() * sizeof(WMVertex), WMGPUBuffer::CPUCacheMode::WRITABLE);
    vertexBuffer->WriteData(mesh->vertices.data(), mesh->vertices.size() * sizeof(WMVertex));
    mesh->vertexBuffer = vertexBuffer;

    return mesh;
}

WMMesh* WMGeometryFactory::MakeQuad(WMGraphicsDevice* device, float size, const WMColor& color)
{
    WMMesh* mesh = new WMMesh();
    Vector<WMVector3> positions =
    {
        WMVector3   { -size,  size, 0.0f } //  0
        , WMVector3 {  size,  size, 0.0f } //  1
        , WMVector3 {  size, -size, 0.0f } //  2
        , WMVector3 { -size, -size, 0.0f } //  3
    };

    Vector<WMVector2> texcoords =
    {
        WMVector2   { 0.0f, 0.0f }
        , WMVector2 { 1.0f, 0.0f }
        , WMVector2 { 1.0f, 1.0f }
        , WMVector2 { 0.0f, 1.0f }
    };

    Vector<uint32_t> indicies =
    {
        0, 1, 2,
        0, 2, 3
    };

    Vector<WMVertex> verticies;
    for (size_t i = 0; i < indicies.size(); i += 3)
    {
        WMVector3 p1 = positions[indicies[i]];
        WMVector3 p2 = positions[indicies[i + 1]];
        WMVector3 p3 = positions[indicies[i + 2]];
        WMVertex v1 = { p1, texcoords[indicies[i]], color };
        WMVertex v2 = { p2, texcoords[indicies[i + 1]], color };
        WMVertex v3 = { p3, texcoords[indicies[i + 2]], color };
        verticies.push_back(v1);
        verticies.push_back(v2);
        verticies.push_back(v3);
    }

    mesh->vertices = verticies;

    WMSharedPtr<WMGPUBuffer> vertexBuffer;
    vertexBuffer = device->CreateGPUBuffer(
        mesh->vertices.size() * sizeof(WMVertex)
        , WMGPUBuffer::CPUCacheMode::WRITABLE);
    vertexBuffer->WriteData(mesh->vertices.data()
        , mesh->vertices.size() * sizeof(WMVertex));
    mesh->vertexBuffer = vertexBuffer;

    return mesh;
}

WMMesh* WMGeometryFactory::MakePlane(WMGraphicsDevice* device, float size, const WMColor& color)
{
    WMMesh* mesh = new WMMesh();

    uint32_t count = static_cast<uint32_t>(size);
    uint32_t faceCount = count * count;

    Vector<WMVertex> verticies;
    verticies.reserve(count);
    float invSize = 1.0f / size;
    for (uint32_t i = 0; i < count + 1; ++i)
    {
        for (uint32_t j = 0; j < count + 1; ++j)
        {
            float x = static_cast<float>(j);
            float z = static_cast<float>(i);
            WMVector3 p = { x, 0.0f, -z };
            float u = x * invSize;
            float v = z * invSize;
            WMVector2 t = { u, v };
            WMColor c = color;
            WMVertex vertex = { p, t, c };
            verticies.emplace_back(vertex);
        }
    }

    /*
    face = 1
    0 1
    2 3

    face = 2
    0 1 2
    3 4 5
    6 7 8

    face = 3
    0 1 2 3
    4 5 6 7
    8 9 1011
    12131415
    */
    Vector<uint32_t> indices;
    indices.reserve(faceCount * 6);
    for (uint32_t i = 0; i < count; ++i)
    {
        for (uint32_t j = 0; j < count; ++j)
        {
            uint32_t index = j + i * (count + 1);
            indices.emplace_back(index);
            indices.emplace_back(index + 1);
            indices.emplace_back(index + count + 2);
            indices.emplace_back(index);
            indices.emplace_back(index + count + 2);
            indices.emplace_back(index + count + 1);
        }
    }

    mesh->vertices = verticies;
    mesh->indices = indices;

    WMSharedPtr<WMGPUBuffer> vertexBuffer;
    vertexBuffer = device->CreateGPUBuffer(
        mesh->vertices.size() * sizeof(WMVertex)
        , WMGPUBuffer::CPUCacheMode::WRITABLE);
    vertexBuffer->WriteData(mesh->vertices.data()
        , mesh->vertices.size() * sizeof(WMVertex));

    WMSharedPtr<WMGPUBuffer> indexBuffer;
    indexBuffer = device->CreateGPUBuffer(
        mesh->indices.size() * sizeof(uint32_t)
        , WMGPUBuffer::CPUCacheMode::WRITABLE);
    indexBuffer->WriteData(mesh->indices.data()
        , mesh->indices.size() * sizeof(uint32_t));
    mesh->vertexBuffer = vertexBuffer;
    mesh->indexBuffer = indexBuffer;

    return mesh;
}
