#pragma once
#include "../../LineCollider.h"
#include <vector>

using namespace std;

//�{���n�_�����ԋ߂��I�u�W�F�N�g��F���������Ƃ��낪�A
//�����PolyLine�ȊO�Ɏg���\�肪�Ȃ����߁A�������Ă�����̂̒���
//PolyLine���܂܂�Ă��邩���f�ł���Ηǂ��Ƃ���

class Ray :
    public LineCollider
{
private:
    std::vector<ColliderBase*>hit_colliders;
    const Location* base_location;
    COLLIDER hit_collider_type;
    Location shift = {};

public:
    Ray();
    Ray(const Location* location, float shift_x = 0, float shift_y = 0);
    ~Ray();

    void Update();
    void Draw()const;

    void UpdateLocation();
    void HitFunction(ColliderBase* collider);

    const ColliderBase* SearchCollider(COLLIDER collider_type)const;
};

