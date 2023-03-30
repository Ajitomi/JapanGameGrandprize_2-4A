#pragma once
#include "../Define.h"
#include "../LineCollider.h"
#include "../SphereCollider.h"
#include <vector>

using namespace std;

class PolyLine 
    :public ColliderBase
{
private:

    vector<SphereCollider*>bend_points;   //折れ
    vector<LineCollider*>lines;          //線
public:
    PolyLine();
    PolyLine(Location bend_points[], unsigned int size);
    PolyLine(const vector<SphereCollider*>spheres);
    ~PolyLine();

    void Update();
    virtual void Draw()const;

    //SphereColliderとの当たり判定
    virtual bool HitSphere(const class SphereCollider* sphere_collider) const;

    //BoxColliderとの当たり判定
    virtual bool HitBox(const class BoxCollider* box_collider) const;

    //LineColliderとの当たり判定
    virtual bool HitLine(const class LineCollider* line_collider)const;

    //点の削除
    void DeleteBendPoint(int index);

    vector<SphereCollider*> GetPoints()const{return bend_points;}
};