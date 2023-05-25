#include "DxLib.h"
#include "Define.h"
#include "Scene/SceneManager.h"
#include "Scene/GameMain.h"
#include "PadInput.h"
#include "Scene/Title.h"
#include "EnemySE.h"
#include "EnemyBase.h"
#include "Pouch.h"

#define FRAMERATE 60.0 //�t���[�����[�g

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	double dNextTime = GetNowCount();

	SetMainWindowText("Science Revenge");

	SetWindowIconID(01);

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetAlwaysRunFlag(true);		//��ɃA�N�e�B�u�ɂ���

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;

	try
	{
		unsigned int a[7];
		
		sceneMng = new SceneManager((AbstractScene*)new Title());
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	EnemyBase::LoadWeakness();
	EnemySE::LoadSound();
	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr))
	{

		ClearDrawScreen();		// ��ʂ̏�����
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();

		//�����I��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK))
		{
			break;
		}
#ifdef _DEBUG
		//���C�A�E�g�݌v�p
		if (PAD_INPUT::OnPressed(XINPUT_BUTTON_X))
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			for (int x = 0; x < 1280; x += 40)
			{
				DrawLineAA(x, 0, x, 720, 0x000000, 0.01F);
				for (int y = 0; y < 720; y += 40) 
				{
					DrawLineAA(0, y, 1280, y, 0x000000, 0.01F);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
#endif

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

		//�t���[�����[�g�̐ݒ�
		dNextTime += 1.0 / 60.0 * 1000.0;

		if (dNextTime > GetNowCount()) 
		{
			WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
		}
		else { dNextTime = GetNowCount(); }		//�␳
	}

	EnemySE::DeleteSound();
	EnemyBase::DeleteWeakness();

	return 0;
}