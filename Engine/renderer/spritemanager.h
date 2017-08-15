#pragma once

#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include"renderer_definitions_pc.h"
#include"renderer.h"
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

	// indexed draw is not defensible for a single quad
	buffer* m_vertex_buffer = nullptr;
	const int m_vertex_count = 4;
};
extern Renderer* g_Renderer;
#endif