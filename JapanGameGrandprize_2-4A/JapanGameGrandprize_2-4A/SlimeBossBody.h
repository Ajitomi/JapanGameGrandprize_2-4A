//#pragma once
//#include"EnemyBase.h"
//#include"CameraWork.h"
//
//enum class BODY_TYPE
//{
//	head,
//	body
//};
//
//class SlimeBossBody: public EnemyBase
//{
//private:
//
//	bool attack; //�U��������������
//
//	int slimeboss_image;
//	BODY_TYPE body_type;
//public:
//
//	SlimeBossBody(int x, int y, int speed, int hp, int slime_min_drop, int slime_drop, BODY_TYPE body_type);
//	~SlimeBossBody();
//
//	//�`��ȊO�̍X�V�����s
//	virtual void Update(const class Player* player, const class Stage* stage)override;
//	//�`��
//	virtual void Draw()const override;
//
//	//�ړ�
//	void Move(const Location player_location) override;
//
//	//����
//	void Fall() override;
//	
//	void Idol() override;
//
//	//�U��
//	void  Attack(Location) override;
//
//	//�U�����������Ă��邩
//	AttackResource Hit() override;
//
//	//���S
//	void Death() override;
//
//	virtual void HitBullet(const BulletBase* bullet)override;
//
//	//���W�̎擾
//	Location GetLocation() const override;
//
//	void SetLocation(Location location);
//
//	BODY_TYPE GetBodyType() const { return body_type; }
//};