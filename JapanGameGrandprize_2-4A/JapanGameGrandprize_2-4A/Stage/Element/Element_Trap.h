#pragma once
#include "Stage_Element_Base.h"
#include "../EnemyBase.h"
#include "../BULLET.h"
#include "../Stage.h"

class Element_Trap : public Stage_Element_Base
{
private:

	Stage* stage;
	EnemyBase** enemy;
	BulletBase* bullet;
	ChemicalFormulaParameter explosion{};

	enum class STATE {
		NONE,		//�Ȃ�
		EXPLOSION,	//����
		EXTINGUISHMENT	//����
	}state;
public:

	//�R���X�g���N�^
	Element_Trap(short type,std::vector<std::shared_ptr<Stage_Element_Base>> element, Stage* stage,EnemyBase** enemy, std::vector<int> images, Location location, Area area);
	//�f�X�g���N�^
	~Element_Trap();
	//�X�V
	void Update(Player* player) override;

	void Draw()const override;
};