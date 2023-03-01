//
//  File:   WMBlendState.h
//  Author: Eugene Kim (komastar.dev@gmail.com)
//
//  Copyright (c) 2022 komastar. All rights reserved.
//

#pragma once
namespace WildMini
{
    enum WMColorWriteMask
    {
        ColorWriteMaskNone = 0x0,
        ColorWriteMaskRed = 0x1,
        ColorWriteMaskGreen = 0x2,
        ColorWriteMaskBlue = 0x4,
        ColorWriteMaskAlpha = 0x8,
        ColorWriteMaskAll = 0xf
    };

    enum class WMBlendOperation
    {
        Add,
        Substract,
        ReserveSubtract,
        Min,
        Max
    };

    enum class WMLogicOperation
    {
        CLEAR
        , SET
        , COPY
        , COPY_INVERTED
        , NOOP
        , INVERT
        , AND
        , NAND
        , OR
        , NOR
        , XOR
        , EQUIV
        , AND_REVERSE
        , AND_INVERTED
        , OR_REVERSE
        , OR_INVERTED
        , MAX
    };

    enum class WMBlendFactor
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstColor,
        OneMinusDstColor,
        DstAlpha,
        OneMinusDstAlpha,
        SrcAlphaSaturated,
        BlendFactor,
        OneMinusBlendFactor
    };
}
