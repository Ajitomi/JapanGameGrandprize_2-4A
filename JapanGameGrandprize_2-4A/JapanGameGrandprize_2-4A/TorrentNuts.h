#pragma once
#include "EnemyBulletBase.h"
class TorrentNuts :
    public EnemyBulletBase
{
private:

    int images[3]; //�摜
    int argument; //�`��摜
public:

    //�R���X�g���N�^
    TorrentNuts(const ENEMY_TYPE, const Location);

    //�f�X�g���N�^
    ~TorrentNuts();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};