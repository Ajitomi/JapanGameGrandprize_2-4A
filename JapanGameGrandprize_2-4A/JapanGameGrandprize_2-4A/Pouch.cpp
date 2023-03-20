#include "Pouch.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"
#include <stdlib.h>

//コンストラクタ
Pouch::Pouch()
{
	x = 1080;
	y = 100;
	cursol = 0;
	on_bool = false;
	tab = ATTRIBUTE::EXPLOSION;

	//元素の初期化
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = nullptr;
	}

	InitChemicalParameter();
}

Pouch::~Pouch()
{

}


//爆発
void Pouch::ExplosionTabDraw() const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff99ff, TRUE);
	DrawString(x, y + 50, "EXPLOSION", 0x000000);

	if (cursol - 1 < 0)
	{
		DrawFormatString(x, y + 140, 0x000000, "%s", chemical_formula_explosion[cursol + (EXPLOSION_MAX_NUM - 1)].chemical_formula_name);
	}
	else
	{
		DrawFormatString(x, y + 140, 0x000000, "%s", chemical_formula_explosion[cursol - 1].chemical_formula_name);
	}

	if (cursol + 1 > EXPLOSION_MAX_NUM - 1)
	{
		DrawFormatString(x, y + 340, 0x000000, "%s", chemical_formula_explosion[cursol - (EXPLOSION_MAX_NUM - 1)].chemical_formula_name);
	}
	else
	{
		DrawFormatString(x, y + 340, 0x000000, "%s", chemical_formula_explosion[cursol + 1].chemical_formula_name);
	}

	DrawBox(x, y + 200, x + POUCH_WIDTH, y + 300, 0xffffff, FALSE);

	DrawFormatString(x, y + 240, 0x000000, "%s", chemical_formula_explosion[cursol].chemical_formula_name);
}

//溶解
void Pouch::MeltTabDraw() const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff55ff, TRUE);
	DrawString(x, y + 50, "MELT", 0x000000);
	for (int i = 0; i < 3; i++)
	{
		DrawFormatString(x, y + (100 * (i + 1)), 0x000000, "%s", chemical_formula_melt[i + cursol].chemical_formula_name);
	}
}

//麻痺
void Pouch::ParalysisTabDraw()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff0099, TRUE);
	DrawString(x, y + 50, "PARALYSIS", 0x000000);
	for (int i = 0; i < 3; i++)
	{
		DrawFormatString(x, y + (100 * (i + 1)), 0x000000, "%s", chemical_formula_pararysis[i + cursol].chemical_formula_name);
	}
}

//毒
void Pouch::PoisonTabDraw()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x5500ff, TRUE);
	DrawString(x, y + 50, "POISON", 0x000000);
	for (int i = 0; i < 3; i++)
	{
		DrawFormatString(x, y + (100 * (i + 1)), 0x000000, "%s", chemical_formula_poison[i + cursol].chemical_formula_name);
	}
}

//回復
void Pouch::HealTabDraw()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff1111, TRUE);
	DrawString(x, y + 50, "HEAL", 0x000000);
	for (int i = 0; i < 3; i++)
	{
		DrawFormatString(x, y + (100 * (i + 1)), 0x000000, "%s", chemical_formula_heal[i + cursol].chemical_formula_name);
	}
}

//描画
void Pouch::Draw() const
{
	switch (tab)
	{
	case ATTRIBUTE::EXPLOSION:
		ExplosionTabDraw();
		break;
	case ATTRIBUTE::MELT:
		MeltTabDraw();
		break;
	case ATTRIBUTE::POISON:
		PoisonTabDraw();
		break;
	case ATTRIBUTE::PARALYSIS:
		ParalysisTabDraw();
		break;
	case ATTRIBUTE::HEAL:
		HealTabDraw();
		break;
	default:
		break;
	}



	

	DrawBox(x, y + 400, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x0000ff, TRUE);

	for (int i = 0; i < 4; i++)
	{
		DrawBox(x + (50 * i), y + 400, (x + (50 * i)) + 50, y + 450, 0xffffff, FALSE);
		DrawFormatString(x + (50 * i), y + 400, 0x000000, "%d", element[i]->GetVolume());
	}

	for (int i = 0; i < 3; i++)
	{
		DrawBox(x + (50 * i) + 25, y + 450, (x + (50 * i) + 50) + 25, y + POUCH_HEIGHT, 0xffffff, FALSE);
		DrawFormatString(x + (50 * i) + 25, y + 450, 0xffffff, "%d", element[i + 4]->GetVolume());
	}
}

//アップデート
void Pouch::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		cursol = 0;
		switch (tab)
		{
		case ATTRIBUTE::EXPLOSION:
			tab = ATTRIBUTE::MELT;
			break;
		case ATTRIBUTE::MELT:
			tab = ATTRIBUTE::POISON;
			break;
		case ATTRIBUTE::POISON:
			tab = ATTRIBUTE::PARALYSIS;
			break;
		case ATTRIBUTE::PARALYSIS:
			tab = ATTRIBUTE::HEAL;
			break;
		case ATTRIBUTE::HEAL:
			tab = ATTRIBUTE::EXPLOSION;
			break;
		default:
			break;
		}
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		cursol = 0;
		switch (tab)
		{
		case ATTRIBUTE::EXPLOSION:
			tab = ATTRIBUTE::HEAL;
			break;
		case ATTRIBUTE::MELT:
			tab = ATTRIBUTE::EXPLOSION;
			break;
		case ATTRIBUTE::POISON:
			tab = ATTRIBUTE::MELT;
			break;
		case ATTRIBUTE::PARALYSIS:
			tab = ATTRIBUTE::POISON;
			break;
		case ATTRIBUTE::HEAL:
			tab = ATTRIBUTE::PARALYSIS;
			break;
		default:
			break;
		}
	}

	switch (tab)
	{
	case ATTRIBUTE::EXPLOSION:
		ExplosionTabUpdate();
		break;
	case ATTRIBUTE::MELT:
		MeltTabUpdate();
		break;
	case ATTRIBUTE::POISON:
		PoisonTabUpdate();
		break;
	case ATTRIBUTE::PARALYSIS:
		ParalysisTabUpdate();
		break;
	case ATTRIBUTE::HEAL:
		HealTabUpdate();
		break;
	default:
		break;
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		on_bool = true;
		switch (tab)
		{
		case ATTRIBUTE::EXPLOSION:
			select_explosion = chemical_formula_explosion[cursol];
			break;
		case ATTRIBUTE::MELT:
			select_melt = chemical_formula_melt[cursol];
			break;
		case ATTRIBUTE::POISON:
			select_poison = chemical_formula_poison[cursol];
			break;
		case ATTRIBUTE::PARALYSIS:
			select_pararysis = chemical_formula_pararysis[cursol];
			break;
		case ATTRIBUTE::HEAL:
			select_heal = chemical_formula_heal[cursol];
			break;
		default:
			break;
		}
	}

}

void Pouch::ExplosionTabUpdate()
{
	if (++count % CURSOL_SPEED == 0)
	{
		if (PAD_INPUT::GetRStick().y > 5000)
		{
			cursol--;
			if (cursol < 0)
			{
				cursol = EXPLOSION_MAX_NUM - 1;
			}
		}

		if (PAD_INPUT::GetRStick().y < -5000)
		{
			cursol++;
			if (cursol > EXPLOSION_MAX_NUM - 1)
			{
				cursol = 0;
			}
		}
	}
}

void Pouch::PoisonTabUpdate()
{

}

void Pouch::HealTabUpdate()
{

}

void Pouch::MeltTabUpdate()
{

}

void Pouch::ParalysisTabUpdate()
{

}


void Pouch::SetElement(ElementItem* item, int i)
{
	element[i] = item;
}

void Pouch::InitChemicalParameter()
{
	int count = EXPLOSION_MAX_NUM;
	FILE* fp; //FILE型構造体
	errno_t error;
	error = fopen_s(&fp, "Data/chemical_formula_data/ChemicalFormulaParameter.csv", "r");
	if (error != 0) //ファイルが開けてない
	{
		return;
	}
	else     //ファイルが開けた
	{
		int attribute;
		char line[100];
		for (int i = 0; i < EXPLOSION_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_explosion[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_explosion[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_explosion[i].material.carbon,
				&chemical_formula_explosion[i].material.hydrogen,
				&chemical_formula_explosion[i].material.nitrogen,
				&chemical_formula_explosion[i].material.oxygen,
				&chemical_formula_explosion[i].material.sulfur,
				&chemical_formula_explosion[i].material.chlorine,
				&chemical_formula_explosion[i].number_of_bullets,
				&chemical_formula_explosion[i].damage,
				&chemical_formula_explosion[i].damage_per_second,
				&chemical_formula_explosion[i].time,
				&attribute);
			chemical_formula_explosion[i].atribute = static_cast <ATTRIBUTE>(attribute);
		}
		for (int i = 0; i < POISON_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_poison[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_poison[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_poison[i].material.carbon,
				&chemical_formula_poison[i].material.hydrogen,
				&chemical_formula_poison[i].material.nitrogen,
				&chemical_formula_poison[i].material.oxygen,
				&chemical_formula_poison[i].material.sulfur,
				&chemical_formula_poison[i].material.chlorine,
				&chemical_formula_poison[i].number_of_bullets,
				&chemical_formula_poison[i].damage,
				&chemical_formula_poison[i].damage_per_second,
				&chemical_formula_poison[i].time,
				&attribute);
			chemical_formula_poison[i].atribute = static_cast <ATTRIBUTE>(attribute);
		}

		for (int i = 0; i < PARARYSIS_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_pararysis[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_pararysis[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_pararysis[i].material.carbon,
				&chemical_formula_pararysis[i].material.hydrogen,
				&chemical_formula_pararysis[i].material.nitrogen,
				&chemical_formula_pararysis[i].material.oxygen,
				&chemical_formula_pararysis[i].material.sulfur,
				&chemical_formula_pararysis[i].material.chlorine,
				&chemical_formula_pararysis[i].number_of_bullets,
				&chemical_formula_pararysis[i].damage,
				&chemical_formula_pararysis[i].damage_per_second,
				&chemical_formula_pararysis[i].time,
				&attribute);
			chemical_formula_pararysis[i].atribute = static_cast <ATTRIBUTE>(attribute);

		}


		for (int i = 0; i < HEAL_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_heal[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_heal[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_heal[i].material.carbon,
				&chemical_formula_heal[i].material.hydrogen,
				&chemical_formula_heal[i].material.nitrogen,
				&chemical_formula_heal[i].material.oxygen,
				&chemical_formula_heal[i].material.sulfur,
				&chemical_formula_heal[i].material.chlorine,
				&chemical_formula_heal[i].number_of_bullets,
				&chemical_formula_heal[i].damage,
				&chemical_formula_heal[i].damage_per_second,
				&chemical_formula_heal[i].time,
				&attribute);
			chemical_formula_heal[i].atribute = static_cast <ATTRIBUTE>(attribute);

		}

		for (int i = 0; i < MELT_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_melt[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_melt[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_melt[i].material.carbon,
				&chemical_formula_melt[i].material.hydrogen,
				&chemical_formula_melt[i].material.nitrogen,
				&chemical_formula_melt[i].material.oxygen,
				&chemical_formula_melt[i].material.sulfur,
				&chemical_formula_melt[i].material.chlorine,
				&chemical_formula_melt[i].number_of_bullets,
				&chemical_formula_melt[i].damage,
				&chemical_formula_melt[i].damage_per_second,
				&chemical_formula_melt[i].time,
				&attribute);
			chemical_formula_melt[i].atribute = static_cast <ATTRIBUTE>(attribute);
		}
		return;
	}
	fclose(fp); //ファイルを閉じる
}

ChemicalFormulaParameter Pouch::GetExplosion()
{
	return select_explosion;
}

ChemicalFormulaParameter Pouch::GetPoison()
{
	return select_poison;
}

ChemicalFormulaParameter Pouch::GetPararysis()
{
	return select_pararysis;
}

ChemicalFormulaParameter Pouch::GetHeal()
{
	return select_heal;
}

ChemicalFormulaParameter Pouch::GetMelt()
{
	return select_melt;
}

ATTRIBUTE Pouch::GetAttribute()
{
	return tab;
}

int Pouch::GetCursol()
{
	return cursol;
}

bool Pouch::GetOnBool()
{
	return on_bool;
}

void Pouch::SetOnBool(bool a)
{
	on_bool = a;
}