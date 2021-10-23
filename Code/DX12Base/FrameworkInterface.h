#pragma once
#include "stdafx.h"

interface IGameObject
{
protected:
    BOOL isRender;
    BOOL isStart;

public:
    virtual BOOL Awake() PURE;          //  생성자에서 사용할 것.
    virtual BOOL Start() PURE;          //  최초의 업데이트.
    virtual BOOL Update() PURE;         //  반복되는 기본 업데이트 함수.
    virtual BOOL FixedUpdate() PURE;    //  일정한 프레임마다 실행되는 업데이트 함수.
    virtual BOOL LateUpdate() PURE;     //  기본 업데이트 이후에 실행되는 업데이트 함수.
    virtual BOOL Render() PURE;         //  화면에 그리는 함수.
    virtual BOOL Release() PURE;        //  메모리 해제 함수.
};

interface IGameScene : public IGameObject
{
private:

public:
};