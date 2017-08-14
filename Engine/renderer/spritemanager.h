#pragma once

#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include"renderer_definitions_pc.h"

// TODO: replace
#include<vector>

typedef unsigned int Sprite;

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();
	void RenderSprites();
	Sprite RegisterSprite();


private:
	struct s_sprite
	{
		// TODO: vector class maybe? We won't need a ton of vector math here..
		int m_position[3];  // x y z
		int m_dimension[2]; // height width
		texture* m_texture;
	};

	std::vector<s_sprite> m_active_sprites;
	std::vector<s_sprite> m_inactive_sprites;
	buffer* m_vertex_buffer;
};

#endif