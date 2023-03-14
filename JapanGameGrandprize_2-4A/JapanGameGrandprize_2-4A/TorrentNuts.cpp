#include "TorrentNuts.h"
#include "CameraWork.h"

//�e�̑��x
#define TORRENT_NUTS_SPEED 5

//�e�̃_���[�W
#define TORRENT_NUTS_DAMAGE 5

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
TorrentNuts::TorrentNuts(ENEMY_TYPE type,
	Location spawn_location)
{
	location = spawn_location;
	radius = 20;
	speed = TORRENT_NUTS_SPEED;
	this->type = type;

	image = 0;
	damage = TORRENT_NUTS_DAMAGE;
	
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
TorrentNuts::~TorrentNuts()
{

}

//-----------------------------------
//�X�V
//-----------------------------------
void TorrentNuts::Update()
{
	location.y += speed;
}

//-----------------------------------
//�`��
//-----------------------------------
void TorrentNuts::Draw() const
{
	Location draw_location = location; //�`����W
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location + camera;

	DrawCircle(draw_location.x, draw_location.y, radius, 0xffffff, TRUE);

}