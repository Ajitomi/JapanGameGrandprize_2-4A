#pragma once
class Stage
{
private:
	int background_images;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Stage();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Stage();
	/// <summary>
	/// �X�e�[�W�̍X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �X�e�[�W�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�e�[�W�̓ǂݍ���
	/// </summary>
	void LoadMap();
};

