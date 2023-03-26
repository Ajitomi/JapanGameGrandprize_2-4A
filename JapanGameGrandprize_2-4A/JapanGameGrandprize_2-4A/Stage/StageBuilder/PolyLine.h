#pragma once
#include "../Define.h"
#include "../LineCollider.h"
#include "../SphereCollider.h"
#include <vector>

using namespace std;

class PolyLine 
{
private:

    vector<SphereCollider*>bend_points;   //�܂�
    vector<LineCollider*>lines;          //��
public:
    PolyLine();
    PolyLine(Location bend_points[], unsigned int size);
    PolyLine(const vector<SphereCollider*>spheres);
    ~PolyLine();

    void Update();
    virtual void Draw()const;

    //SphereCollider�Ƃ̓����蔻��
    virtual bool HitSphere(const class SphereCollider* sphere_collider) const;

    //BoxCollider�Ƃ̓����蔻��
    virtual bool HitBox(const class BoxCollider* box_collider) const;

    //LineCollider�Ƃ̓����蔻��
    virtual bool HitLine(const class LineCollider* line_collider)const;

    //�_�̍폜
    void DeleteBendPoint(int index);

    vector<SphereCollider*> GetPoints()const{return bend_points;}
};