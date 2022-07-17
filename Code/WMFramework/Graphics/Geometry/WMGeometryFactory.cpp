//
//  File:   WMGeometryFactory.cpp
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#include "WMGeometryFactory.h"
#include "WMMesh.h"
#include "Math/WMVector3.h"

using namespace WildMini::Graphics::Geometry;
using namespace WildMini::Math;
//
//WMMesh* WMGeometryFactory::MakeBox()
//{
//    static WMMesh* mesh = new WMMesh(
//        std::vector<WMVector3>
//        {
//            WMVector3   { -1.0f,  1.0f,  1.0f }
//            , WMVector3 {  1.0f,  1.0f,  1.0f }
//            , WMVector3 {  1.0f,  1.0f, -1.0f }
//            , WMVector3 { -1.0f,  1.0f, -1.0f }
//            , WMVector3 { -1.0f, -1.0f,  1.0f }
//            , WMVector3 {  1.0f, -1.0f,  1.0f }
//            , WMVector3 {  1.0f, -1.0f, -1.0f }
//            , WMVector3 { -1.0f, -1.0f, -1.0f }
//        },
//        std::vector<uint32_t>
//        {
//            //  top
//            0, 1, 2,
//            0, 2, 3,
//            //  front
//            1, 0, 5,
//            0, 4, 5,
//            //  back
//            3, 2, 6,
//            3, 6, 7,
//            //  right
//            2, 1, 5,
//            2, 5, 6,
//            //  left
//            0, 3, 7,
//            0, 7, 4,
//            //  bottom
//            5, 4, 7,
//            5, 7, 6
//        }
//    );
//
//    return mesh;
//}
