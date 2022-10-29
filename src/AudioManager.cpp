#include "AudioManager.h"
#include <iostream>


AudioManager::AudioManager()
{

}

AudioManager& AudioManager::GetInstance()
{
	static AudioManager* instance = new AudioManager;

	return *instance;
}

void AudioManager::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "SDL_mixer could not initialize!";

	LoadSoundEffectsAndMusic();
}

void AudioManager::LoadSoundEffectsAndMusic()
{
	m_Button = Mix_LoadWAV("res/Sounds/Button.wav");
}

void AudioManager::PlaySoundEffect(Mix_Chunk p_SoundEffect)
{
	Mix_PlayChannel(-1, &p_SoundEffect, 0);
	std::cout << "Sound Played\n";
}