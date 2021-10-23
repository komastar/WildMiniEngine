#pragma once
class CGameObject : public IGameObject
{
public:
    CGameObject();
    ~CGameObject();

    // IGameObject을(를) 통해 상속됨
    virtual BOOL Awake() override;
    virtual BOOL Start() override;
    virtual BOOL Update() override;
    virtual BOOL FixedUpdate() override;
    virtual BOOL LateUpdate() override;
    virtual BOOL Render() override;
    virtual BOOL Release() override;
};

