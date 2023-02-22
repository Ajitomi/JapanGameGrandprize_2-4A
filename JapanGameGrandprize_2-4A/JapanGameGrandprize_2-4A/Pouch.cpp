#include "Pouch.h"
#include "DxLib.h"
#include "PadInput.h"

//�R���X�g���N�^
Pouch::Pouch()
{
	x = 700;
	y = 50;
	tab = Tab::Explosion_Tab;
}

//�A�b�v�f�[�g
void Pouch::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		switch (tab)
		{
		case Tab::Explosion_Tab:
			tab = Tab::Melt_Tab;
			break;
		case Tab::Melt_Tab:
			tab = Tab::Poison_Tab;
			break;
		case Tab::Poison_Tab:
			tab = Tab::Paralysis_Tab;
			break;
		case Tab::Paralysis_Tab:
			tab = Tab::Heal_Tab;
			break;
		case Tab::Heal_Tab:
			tab = Tab::Explosion_Tab;
			break;
		default:
			break;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		switch (tab)
		{
		case Tab::Explosion_Tab:
			tab = Tab::Heal_Tab;
			break;
		case Tab::Melt_Tab:
			tab = Tab::Explosion_Tab;
			break;
		case Tab::Poison_Tab:
			tab = Tab::Melt_Tab;
			break;
		case Tab::Paralysis_Tab:
			tab = Tab::Poison_Tab;
			break;
		case Tab::Heal_Tab:
			tab = Tab::Paralysis_Tab;
			break;
		default:
			break;
		}
	}
}

//����
void Pouch::ExplosionTab () const 
{
	DrawBox(x, y, x + POUCH_SIZE, y + POUCH_SIZE, 0xff99ff, TRUE);
}

//�n��
void Pouch::MeltTab() const
{
	DrawBox(x, y, x + POUCH_SIZE, y + POUCH_SIZE, 0xff55ff, TRUE);
}

//���
void Pouch::ParalysisTab()const
{
	DrawBox(x, y, x + POUCH_SIZE, y + POUCH_SIZE, 0xff0099, TRUE);
}

//��
void Pouch::PoisonTab()const
{
	DrawBox(x, y, x + POUCH_SIZE, y + POUCH_SIZE, 0x5500ff, TRUE);
}

//��
void Pouch::HealTab()const
{
	DrawBox(x, y, x + POUCH_SIZE, y + POUCH_SIZE, 0xff1111, TRUE);
}

//�`��
void Pouch::Draw() const
{
	switch (tab)
	{
	case Tab::Explosion_Tab:
		ExplosionTab();
		break;
	case Tab::Melt_Tab:
		MeltTab();
		break;
	case Tab::Poison_Tab:
		PoisonTab();
		break;
	case Tab::Paralysis_Tab:
		ParalysisTab();
		break;
	case Tab::Heal_Tab:
		HealTab();
		break;
	default:
		break;
	}
}