#pragma once
#include "EnemyBulletBase.h"
class TorrentNuts :
    public EnemyBulletBase
{
private:

    int image; //�摜
public:

    //�R���X�g���N�^
    TorrentNuts(ENEMY_TYPE, Location);

    //�f�X�g���N�^
    ~TorrentNuts();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};