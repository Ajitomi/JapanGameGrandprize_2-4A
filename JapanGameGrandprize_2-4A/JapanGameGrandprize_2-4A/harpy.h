//#pragma once
//#include "EnemyBase.h"
//#include"BoxCollider.h"
//
//enum class HARPY_STATE
//{
//	NORMAL,   //�ʏ�ړ� ���Ɉړ�
//	NORMAL_RIGHT, //�ʏ�ړ� �E�Ɉړ�
//	LEFT_lOWER,   //�����Ɉړ�
//	LEFT_UPPER,   //����Ɉړ�
//	RIGHT_LOWER,  //�E���Ɉړ�
//	RIGHT_UPPER,  //�E��Ɉړ�
//};
//
//enum class HARPY_ATTACK
//{
//	PHYSICAL_ATTACK = 0, //�����U��
//	MAGIC_ATTACK, //���@�U��
//	NONE //�U�������Ă��Ȃ��B
//};
//
//class Harpy :public EnemyBase,public BoxCollider
//{
//private:
//	int harpy_images; //�n�[�s�B�̉摜
//	bool magic_attack; //���@�U��
//	bool physical_attack; //�����U���ɓ���itrue)�Ȃ�
//	HARPY_STATE action; //�s��
//	HARPY_ATTACK attack; //�U��
//public:
//
//	//�R���X�g���N�^
//	Harpy(); 
//
//	//�f�X�g���N�^
//	~Harpy();
//
//	//�`��ȊO�̍X�V�����s
//	void Update()override;
//
//	//�`��
//	void Draw()const override;
//
//	//�n�[�s�B�̓���
//	void Move(const Location player_location) override;
//	
//	//�v���C���[�̋������擾��n�[�s�B�̓��������߂�B
//	void Distance(const Location player_location);
//
//	////�A�C�h�����
//	//void Idol() override;
//
//	////�U��
//	//void  Attack(Location) override;
//
//	////�U�����������Ă��邩
//	//AttackResource HitCheck(const BoxCollider* collider) override;
//
//	////���S
//	//void Death() override;
//	//
//	////�v���C���[�̒e�ۂƂ̓����蔻��
//	//bool HitBullet(const BulletBase* bullet) override;
//
//	////���W�̎擾
//	//Location GetLocation() const override;
//	
//};