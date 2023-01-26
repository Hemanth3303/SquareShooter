#pragma once

#include "pch.hpp"

class AudioManager {
public:
	static void Init();
	static void PlayBgMusic();
	static void UpdateBgMusic();
	static void PlayShootSound();
	static void PlayHitSound();
	static void PlayDieSound();
	static void ShutDown();
private:
	static Sound s_Sounds[3];
	static Music s_BgMusic;
	enum SoundNames {
		Shoot = 0,
		Hit,
		Die,
	};
};