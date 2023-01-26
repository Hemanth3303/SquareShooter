#include "pch.hpp"
#include "AudioManager.hpp"

Sound AudioManager::s_Sounds[3];
Music AudioManager::s_BgMusic;

void AudioManager::Init() {
	InitAudioDevice();

	s_BgMusic = LoadMusicStream("res/CriticalTheme.wav");
	SetMusicVolume(s_BgMusic, 0.5f);

	s_Sounds[Shoot] = LoadSound("res/shoot.wav");
	s_Sounds[Hit] = LoadSound("res/hit.wav");
	s_Sounds[Die] = LoadSound("res/die.wav");
}

void AudioManager::PlayBgMusic() {
	PlayMusicStream(s_BgMusic);
}

void AudioManager::UpdateBgMusic() {
	UpdateMusicStream(s_BgMusic);
}

void AudioManager::PlayShootSound() {
	PlaySound(s_Sounds[Shoot]);
}

void AudioManager::PlayHitSound() {
	PlaySound(s_Sounds[Hit]);
}

void AudioManager::PlayDieSound() {
	PlaySound(s_Sounds[Die]);
}

void AudioManager::ShutDown() {
	UnloadMusicStream(s_BgMusic);
	UnloadSound(s_Sounds[Shoot]);
	UnloadSound(s_Sounds[Hit]);
	UnloadSound(s_Sounds[Die]);
	CloseAudioDevice();
}
