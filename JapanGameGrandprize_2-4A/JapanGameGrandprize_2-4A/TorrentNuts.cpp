#include "TorrentNuts.h"
#include "CameraWork.h"

//�e�̑��x
#define TORRENT_NUTS_SPEED 5

//�e�̃_���[�W
#define TORRENT_NUTS_DAMAGE 10

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
TorrentNuts::TorrentNuts(const ENEMY_TYPE type, const Location spawn_location)
{

	location = spawn_location;
	radius = 20;
	speed = TORRENT_NUTS_SPEED;
	this->type = type;

	LoadDivGraph("Images/Enemy/Torrent/fruit.png", 3, 3, 1, 240, 240, images);

	argument = GetRand(2);
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

	draw_location = draw_location - camera;
	DrawRotaGraphF(draw_location.x, draw_location.y, 0.2, 0, images[argument], TRUE);

}