#pragma once
#include "AbstractScene.h"
#include "Define.h"
#include "ColliderBase.h"


enum class CHARACTER
{
    Player,
    SLIME,	    //�X���C��
    UNDEAD,		//�A���f�b�g
    HARPY,		//�n�[�s�B
    MAGE,		//���C�W
    GHOST,		//�S�[�X�g
    WYVERN,		//���C�o�[��
    SLIME_BOSS, //�X���C���L���O
    TORRENT,	//�g�����g
    GARGOYLE,	//�K�[�S�C��
    DRAGON,		//�h���S��
    END_BOSS,	//���X�{�X
};

enum class BLOCK
{

};

//�h�b�g�o�C�h�b�g�p�̍\����
struct Character
{
    Location location;      //���W
    Area area;              //�����蔻��
    int* images;            //�摜
    CHARACTER type;         //�^�C�v
};

//�h�b�g�o�C�h�b�g�p�̍\����
struct Block
{
    Location location;      //���W
    Area area;              //�����蔻��
    int* images;            //�摜
    Character type;         //�^�C�v
};
//�h�b�g�o�C�h�b�g�p�̍\����
struct DebugBullet
{
    Location location;      //���W
    int radius;              //�����蔻��
    int* images;            //�摜
};

class DotByDot :
    public AbstractScene
{
private:
    //�L�����N�^�[�p
    Character* character;

    //�e�p
    DebugBullet* bullet;

    //�u���b�N�p
    Block* block;
public:
    //�R���X�g���N�^
    DotByDot();

    //�f�X�g���N�^
    ~DotByDot();

    //�X�V
    AbstractScene* Update() override;

    //�`��
    void Draw() const override;
};

