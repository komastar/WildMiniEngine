#pragma once
#include "stdafx.h"

interface IGameObject
{
protected:
    BOOL isRender;
    BOOL isStart;

public:
    virtual BOOL Awake() PURE;          //  �����ڿ��� ����� ��.
    virtual BOOL Start() PURE;          //  ������ ������Ʈ.
    virtual BOOL Update() PURE;         //  �ݺ��Ǵ� �⺻ ������Ʈ �Լ�.
    virtual BOOL FixedUpdate() PURE;    //  ������ �����Ӹ��� ����Ǵ� ������Ʈ �Լ�.
    virtual BOOL LateUpdate() PURE;     //  �⺻ ������Ʈ ���Ŀ� ����Ǵ� ������Ʈ �Լ�.
    virtual BOOL Render() PURE;         //  ȭ�鿡 �׸��� �Լ�.
    virtual BOOL Release() PURE;        //  �޸� ���� �Լ�.
};

interface IGameScene : public IGameObject
{
private:

public:
};