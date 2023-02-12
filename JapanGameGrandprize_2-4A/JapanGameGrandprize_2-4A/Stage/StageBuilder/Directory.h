#pragma once
#include <direct.h>
#include <string>
using namespace std;
class Directory
{
private:
	static string main_dir; //main�֐�������f�B���N�g��
	static string current_dir; //���݂̃f�B���N�g��

public:
	//�J�����g�f�B���N�g���̍X�V
	static void Update()
	{
		char* buffer = nullptr;
		const char* get_current = _getcwd(buffer, 256);
		current_dir = get_current;

	}

	//������ �����main�f�B���N�g��������Ă���A����ȍ~��main�f�B���N�g�����J��
	static bool Init()
	{
		bool isSuccess = false;
		if (main_dir.empty())
		{
			char* buffer = nullptr;
			buffer = _getcwd(buffer, 256);
			main_dir = buffer;
			current_dir = buffer;
			isSuccess = true;
		}
		else
		{
			if (OpenMain())
			{
				Update();
				isSuccess = true;
			}
		}

		return isSuccess;
	}

	//�J�����g�f�B���N�g������̑��΃p�X�Ńf�B���N�g�����ړ�����
	static bool Open(const char* path);

	//main�֐�������f�B���N�g�����J��
	static bool OpenMain()
	{
		bool isSuccess = false;
		if (!main_dir.empty())
		{
			if (_chdir(main_dir.c_str()) != -1)isSuccess = true;

			Update();
		}
		return isSuccess;
	}

	static const char* GetCurrent() { return current_dir.c_str(); }
};

