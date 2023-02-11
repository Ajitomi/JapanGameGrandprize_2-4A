#pragma once
#include <direct.h>
class Directory
{
private:
	static char str[10];
	static char* main_dir; //main�֐�������f�B���N�g��
	static char* current_dir; //���݂̃f�B���N�g��

public:
	//�J�����g�f�B���N�g���̍X�V
	static void Update()
	{
		current_dir = _getcwd(current_dir, 256);
	}

	//������ �����main�f�B���N�g��������Ă���A����ȍ~��main�f�B���N�g�����J��
	static bool Init()
	{
		bool isSuccess = false;
		if (main_dir == nullptr)
		{
			main_dir = _getcwd(main_dir, 256);
			current_dir = _getcwd(current_dir, 256);
			isSuccess = true;
		}
		else
		{
			if (OpenMain())isSuccess = true;
		}

		return isSuccess;
	}

	//�J�����g�f�B���N�g������̑��΃p�X�Ńf�B���N�g�����ړ�����
	static bool Open(const char* path);

	//main�֐�������f�B���N�g�����J��
	static bool OpenMain()
	{
		bool isSuccess = false;
		if (_chdir(main_dir) != -1)isSuccess = true;
		return isSuccess;
	}

	static char* GetCurrent() { return current_dir; }
};

