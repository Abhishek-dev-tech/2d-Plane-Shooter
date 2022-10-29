#pragma once
#include <SDL_mixer.h>

class AudioManager
{
public:
	AudioManager();

	static AudioManager& GetInstance();

	void Init();
	void LoadSoundEffectsAndMusic();
	void PlaySoundEffect(Mix_Chunk p_SoundEffect);

	Mix_Chunk* m_Button;
};
