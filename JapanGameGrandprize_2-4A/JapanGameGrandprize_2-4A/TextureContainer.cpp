#include "TextureContainer.h"
#include <string.h>

TextureContainer* TextureContainer::instance = nullptr;

//---------------------------------
// �R���X�g���N�^
//---------------------------------
TextureContainer::TextureContainer()
{
	;
}

//---------------------------------
// �f�X�g���N�^
//---------------------------------
TextureContainer::~TextureContainer()
{

}

//---------------------------------
// �R���e�i�̍폜
//---------------------------------
void TextureContainer::Delete()
{
	delete instance;
	instance = nullptr;
}

//---------------------------------
// �摜�̎擾
//---------------------------------
 int TextureContainer::GetTexture(const char* texture_name)
{
	int image_handle = 0;
	decltype (texture)::iterator it = texture.find(texture_name);
	if (it == texture.end())
	{
		char path[100] = "images/Stage/";
		strcat_s(path, texture_name);
		strcat_s(path, ".png");
		if ((image_handle = LoadGraph(path)) == -1)
		{
			throw path;
			return 0;
		}
		else
		{
			texture.insert(std::make_pair(texture_name, image_handle));
		}
	}
	
	image_handle = texture.at(texture_name);
	
	return image_handle;
}

//---------------------------------
// 
//---------------------------------



//---------------------------------
// 
//---------------------------------

