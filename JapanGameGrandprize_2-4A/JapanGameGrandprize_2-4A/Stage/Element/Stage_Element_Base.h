#pragma once
#include "../Define.h"
#include <memory>
#include <chrono>
#include <functional>
#include <vector>
#include <thread>
#include <unordered_map>
#include "../MapChip.h"
#include <tuple>

class Player;

//struct RECT
//{
//	float x;
//	float y;
//	float width;
//	float height;
//};

enum class HIT_DIRECTION
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Stage_Element_Base : public MapChip
{
protected:
	
	MapChip* mapchip;
	short type;

	//LoopImages�̊J�n����
	std::chrono::steady_clock::time_point start_time;

	//�O���t�B�b�N�n���h���pVector
	std::vector<int> images;
	
	//���s������
	int count;

	//�etime�l�ɑΉ�����J�n�������i�[����}�b�v
	std::unordered_map<float, std::chrono::steady_clock::time_point> start_time_map;

	//�etime�l�ɑΉ�����~���b�P�ʂ̌o�ߎ��Ԃ��i�[����}�b�v
	std::unordered_map<float, float> elapsed_time_map;

	//�`�悵�Ă���摜�J�E���g
	int current_image;
public:
	
	//�f�t�H���g�R���X�g���N�^
	Stage_Element_Base();

	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//�R���X�g���N�^
	//Stage_Element(const int* p_image, Location location, Area area);
	//�f�X�g���N�^
	virtual ~Stage_Element_Base();
	virtual void Update(Player* player) {};
	////�`��
	//virtual void Draw() const {};

	short GetType() const { return type; };

	/// <summary>
	/// �A�j���[�V�����p���[�v�^�C�}�[
	/// </summary>
	/// <param name = "*images">�摜��|�C���^</param>
	/// <param name = "time">�b��</param>
	/// <param name = "total_images">�摜����</param>
	/// <param name = "std::function* callback">time�Ŏw�肵���b�����ɌĂԊ֐�
	/// <para>�@�@�@�@�@�@�@�@�@�Ăяo�������֐����Ȃ��ꍇ��nullptr</para></param>
	void LoopImages(std::vector<int>& images, float time, int total_images, std::function<void()>* callback);

	/// <summary>
	/// �v���C���[�ƃu���b�N���������Ă��邩��Getter
	/// </summary>
	/// <returns>false:�������Ă��Ȃ�
	/// <para>true:�������Ă���</para></returns>	
	//bool HitPlayer(Player* player) const;

	/// <summary>
	/// �v���C���[�ƃu���b�N���������Ă��邩
	/// <para>�Ɠ������Ă��������Getter</para>
	/// </summary>
	/// <returns>tuple(bool�^, HITDIRECTION�\���̌^)
	// <para>false:�������Ă��Ȃ�</para>
	/// <para>true:�������Ă���</para>
	/// <para>HITDIRECTION::NONE:�������Ă��Ȃ�</para>
	/// <para>HITDIRECTION::UP:��</para>
	/// <para>HITDIRECTION::DOWN;��</para>
	/// <para>HITDIRECTION::LEFT:��</para>
	/// <para>HITDIRECTION::RIGHT:�E</para></returns>	
	std::tuple<bool, HIT_DIRECTION> HitPlayer(Player* player) const;

	/// <summary>
	/// ���[�v�^�C�}�[		Setter
	/// </summary>
	/// <param name = "time">�b��</param>
	/// <param name = "std::function* callback">time�Ŏw�肵���b�����ɌĂԊ֐�
	/// <para>�@�@�@�@�@�@�@�@�@�Ăяo�������֐����Ȃ��ꍇ��nullptr</para></param>
	void LoopTimer(float time, std::function<void()>* callback);

	/// <summary>
	/// ���[���^�C�}�[	�̌o�ߎ���	Getter
	/// </summary>
	/// <param name = "time">�擾�������^�C�}�[�̕b��</param>
	/// <returns>�o�ߎ���</returns>	
	float GetElapsedTime(float time) const;

	/// <summary>
	/// ���[���^�C�}�[	�̌o�ߎ��ԃ��Z�b�g
	/// </summary>
	/// <param name = "time">���Z�b�g�������^�C�}�[�̕b��</param>
	void ResetElapsedTime(float time);
};