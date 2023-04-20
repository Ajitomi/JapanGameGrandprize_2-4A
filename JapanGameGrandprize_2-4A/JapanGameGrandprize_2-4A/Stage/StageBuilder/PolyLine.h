#pragma once
#include "../Define.h"
#include "../LineCollider.h"
#include "../SphereCollider.h"
#include "../BoxCollider.h"
#include "../../ColliderBase.h"
#include <vector>


using namespace std;
class PolyLine 
    :public ColliderBase
{
private:

    vector<SphereCollider*>bend_points;   //�܂�
    vector<LineCollider*>lines;          //��
public:
    PolyLine();
    PolyLine(Location bend_points[], unsigned int size);
    PolyLine(const vector<SphereCollider*>spheres);
    PolyLine(const PolyLine &poly_line);
    ~PolyLine();

    void Update();
    virtual void Draw()const;

    //SphereCollider�Ƃ̓����蔻��
    virtual bool HitSphere(const class SphereCollider* sphere_collider) const;

    //BoxCollider�Ƃ̓����蔻��
    virtual bool HitBox(const class BoxCollider* box_collider) const;

    //LineCollider�Ƃ̓����蔻��
    virtual bool HitLine(const class LineCollider* line_collider)const;

    //PolyLine�Ƃ̓����蔻��
    virtual bool HitPolyLine(const class PolyLine* poly_line)const;

    ColliderBase* Copy()const override { return new PolyLine(*this); }

    bool HitCheck(ColliderBase* collider)const;

    //�_�̍폜
    void DeleteBendPoint(int index);

    //���S���W�̌v�Z�A�Čv�Z
    void MakeLocation();

    vector<SphereCollider*> GetPoints()const{return bend_points;}
    const vector<LineCollider*>*GetLines()const { return &lines; }

    //�Q�[���v���C���ɓ����蔻����Ƃ镪�ɂ͕K�v�̂Ȃ�����
    //�c�[����Ń}�E�X�Ƃ̓����蔻����Ƃ邽�߂Ɏg�p���Ă��܂�
#ifdef _STAGE_BUILDER
private:
    SphereCollider pivot;
    vector<Location> vector_to_line;

    Location old_location;
    vector<Location> vector_to_bend_point;

public:
    SphereCollider* GetPivot() { return &pivot; }
    
#endif

};