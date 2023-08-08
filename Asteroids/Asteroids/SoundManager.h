#pragma once

#include <SFML/Audio.hpp>

enum soundType
{
	SHOT,
	DEATH,
	EXPLOSION
};

class SoundManager
{
private:
	static SoundManager* sound_instance;
	SoundManager() {}
	~SoundManager();
	sf::SoundBuffer shotBuffer;
	sf::SoundBuffer deathBuffer;
	sf::SoundBuffer explosionBuffer;
	sf::Sound shotSound;
	sf::Sound deathSound;
	sf::Sound explosionSound;
public:
	static SoundManager* Instance()
	{
		if (sound_instance == nullptr)
			sound_instance = new SoundManager;

		return sound_instance;
	}
	void createSounds();
	void dispose();
	void play(soundType type);
};

typedef SoundManager TheSoundManager;