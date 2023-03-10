//#include "Harpy.h"
//#include "CameraWork.h"
//
////�n�[�s�B�̉摜�T�C�Y(����A�摜���o�����撲���j
//#define HARPY_SIZE_X 40
//#define HARPY_SIZE_Y 80
//
////�v���C���[��������
//#define HARPY_DETECTION_DISTANCE 500
//
////�����U���͈�
//#define HARPY_ATTACK_RANGE 20
//
////���@�U���͈�	
//#define HARPY_ATTACK_MAGIC 400
//
////���@�U���������̍d������
//#define HARPY_MAGIC_STANDBY 60
//
////�ߐڍU���������̍d������
//#define HARPY_PHYSICAL_STANDBY 100
//
////�ړ��X�s�[�h
//#define HARPY_SPEED 2.5
//
////�U���X�s�[�h
//#define ATTACK_SPEED 5
//
////�h���b�v��(�ŏ�)
//#define HARPY_MIN_DROP 0u
//
////�h���b�v��(�ő�)
//#define HARPY_MAX_DROP 4u
//
//
////-----------------------------------
//// �R���X�g���N�^
////-----------------------------------
//Harpy::Harpy()
//{
//	location.x = 1500;
//	location.y = 1200;
//	hp = 20;
//	can_delete = false;
//
//	// �h���b�v�A�C�e���̐ݒ�
//		drop_element = new ElementItem * [WIND_DROP];
//	drop_type_volume = WIND_DROP;
//
//	int volume = 0;
//	for (int i = 0; i < WIND_DROP; i++)
//	{
//		volume = HARPY_MIN_DROP + GetRand(HARPY_MAX_DROP);
//		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
//		drop_element[i]->SetVolume(volume);
//		drop_volume += volume;
//	}
//	
//	//�����@�i���j
//	type = new ENEMY_TYPE;
//	*type = ENEMY_TYPE::WIND;
//
//}
//
//
////-----------------------------------
//// �f�X�g���N�^
////-----------------------------------
//Harpy::~Harpy()
//{
//
//}
//
//
////-----------------------------------
//// �X�V
////-----------------------------------
//void Harpy::Update()
//{
//
//}
//
//
//
////-----------------------------------
//// �`��
////-----------------------------------
//void Harpy::Draw() const
//{
//	//�X�N���[���ɍ��킹�ĕ`��
//	float x = location.x - CameraWork::GetCamera().x;
//	float y = location.y - CameraWork::GetCamera().y;
//
//	DrawBox(x, y, x + HARPY_SIZE_X, y + HARPY_SIZE_Y, GetColor(255, 255, 0), TRUE);
//	
//}
//
////-----------------------------------
//// �n�[�s�B�̓���
////-----------------------------------
//void Harpy::Move(const Location player_location)
//{
//	//����
//	Distance(player_location);
//
//	switch (action)
//	{
//	case HARPY_STATE::NORMAL:
//		location.x -= HARPY_SPEED;
//		break;
//	case HARPY_STATE::NORMAL_RIGHT:
//		location.x += HARPY_SPEED;
//		break;
//	case HARPY_STATE::LEFT_lOWER:
//		location.x -= HARPY_SPEED;
//		location.y -= HARPY_SPEED;
//		break;
//	case HARPY_STATE::LEFT_UPPER:
//		location.x -= HARPY_SPEED;
//		location.y+= HARPY_SPEED;
//		break;
//	case HARPY_STATE::RIGHT_LOWER:
//		location.x+= HARPY_SPEED;
//		location.y-= HARPY_SPEED;
//		break;
//	case HARPY_STATE::RIGHT_UPPER:
//		location.x+= HARPY_SPEED;
//		location.y+= HARPY_SPEED;
//		break;
//	default:
//		break;
//	}
//
//}
//
//
////------------------------------------------
//// �v���C���[�̋����𑪂�����ɍs�������߂�
////------------------------------------------
//void Harpy::Distance(const Location player_location)
//{
//	float range; //�v���C���[�Ƃ̋���	
//
//	range = fabsf(location.x - player_location.x);
//
//	//�v���C���[�������������ɂ�����
//	if (range <= HARPY_DETECTION_DISTANCE && range >= -HARPY_DETECTION_DISTANCE)
//	{
//		if (location.x > player_location.x) //���Ɉړ�
//		{
//			if (location.y + 10 >= player_location.y && location.y - 10 <= player_location.y)
//			{
//				action = HARPY_STATE::NORMAL;
//			}
//			else if (player_location.y > location.y)
//			{
//				action = HARPY_STATE::LEFT_lOWER;
//			}
//			else
//			{
//				action = HARPY_STATE::LEFT_UPPER;
//			}
//		}
//		else //�E�Ɉړ�
//		{
//			if (location.y + 10 >= player_location.y && location.y - 10 <= player_location.y)
//			{
//				action = HARPY_STATE::NORMAL_RIGHT;
//			}
//			else if (player_location.y > location.y)
//			{
//				action = HARPY_STATE::RIGHT_LOWER;
//			}
//			else
//			{
//				action = HARPY_STATE::RIGHT_UPPER;
//			}
//		}
//	}
//	else //�ʏ�ړ�
//	{
//		action = HARPY_STATE::NORMAL;
//		magic_attack = false;
//		physical_attack = false;
//	}
//}
//
////void Harpy::Idol()
////{
////
////}
////
////void Harpy::Attack(Location)
////{
////
////}
////
////AttackResource Harpy::HitCheck(const BoxCollider* collider)
////{
////	return AttackResource();
////}
////
////void Harpy::Death()
////{
////
////}
////
////bool Harpy::HitBullet(const BulletBase* bullet)
////{
////	return false;
////}
////
////Location Harpy::GetLocation() const
////{
////	return Location();
////}
//