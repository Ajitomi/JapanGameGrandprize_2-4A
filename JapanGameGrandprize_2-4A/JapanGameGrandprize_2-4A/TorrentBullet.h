#pragma once
#include "EnemyBulletBase.h"

class TorrentBullet :
    public EnemyBulletBase
{
private:

    int* images; //�摜
    int image; //�`��p�̉摜
    int x_speed; //X�̃X�s�[�h
    int y_speed; //Y�̃X�s�[�h
    int angle;
public:

    //�R���X�g���N�^
    TorrentBullet(const Location, const Location);

    //�f�X�g���N�^
    ~TorrentBullet();

    //�X�V
    void Update() override;

    //�`��
    void Draw() const override;
};