#pragma once
#include "../Define.h"
#include <memory>
#include <chrono>
#include <functional>
#include <vector>
#include <thread>
#include "../MapChip.h"

class Player;


class Stage_Element_Base : public MapChip
{
protected:
	
	MapChip* mapchip;
	short type;

	//�Ԋu���Ԃ̊J�n����
	std::chrono::steady_clock::time_point start_time;
	//�~���b�P�ʂ̎��ԊԊu
	std::chrono::duration<long long, std::milli> elapsed;
	//���s������
	int count;


public:
	
	//�f�t�H���g�R���X�g���N�^
	Stage_Element_Base();

	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//�R���X�g���N�^
	//Stage_Element(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	~Stage_Element_Base();
	virtual void Update(Player* player) {};
	////�`��
	//virtual void Draw() const {};

	/// <summary>
	/// �v���C���[�ƃu���b�N���������Ă��邩��Getter
	/// </summary>
	bool HitPlayer(Player* player) const;

	/// <summary>
	/// �A�j���[�V����Setter
	/// </summary>
	void StartAnimation(float time, std::function<void()>* callback);

	/// <summary>
	/// �A�j���[�V����Setter
	/// </summary>
	float GetAnimationTime() { return elapsed.count() / 1000.0f; };
};