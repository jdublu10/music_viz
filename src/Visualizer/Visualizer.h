#pragma once
/***
* @Author Joseph Cutler
* @Date June 17, 2016
* @Copyright WTFPL
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <cassert>

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <boost/format.hpp>

#include "Graphics.h"
#include "Audio.h"
#include "Color.h"

#define UPDATE_CODE		0xF1

class Visualizer {
public:
	Visualizer(Graphics *_g, const char* fname);
	~Visualizer();

	bool WaitingForWindowUpdate(void);
	void UpdateWindow(void);
	void HandleEvent(SDL_Event e);
	void ChangeSong(const char* fname);

	std::string FormattedSongTime();
	
private:
	Graphics *g;

	bool request_draw;
	bool request_update;
	bool paused;
	static constexpr unsigned int frequency = 44100;
	static constexpr unsigned int channels = 2;
	static constexpr unsigned int chunksize = 1024;
	static constexpr unsigned int anim_frame_delay = 20;

	unsigned int box_width;
	unsigned int box_height;
	unsigned int box_x;
	unsigned int box_y;

	unsigned int volume;
	unsigned int song_pos;

	Mix_Music *song;
	const char *fname;
	std::string song_name;
	std::string artist;

	SDL_TimerID callback_timer;

//	TTF_Font *text_font_30;
	TTF_Font *text_font_24;
//	TTF_Font *text_font_14;
//	TTF_Font *text_font_12;

	static uint32_t ScreenUpdateRequestCallback(uint32_t interval, void* param);
	static void 	AudioDrawRequestCallback(void *udata, uint8_t *dstream, int len);

	void RenderGui(void);
	void Text(TTF_Font *font, const char *strbuf, unsigned int x, unsigned int y, const Color &c);
};
