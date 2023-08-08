#include "SoundManager.h"

SoundManager* SoundManager::sound_instance = nullptr;

void SoundManager::createSounds()
{
	shotBuffer.loadFromFile("../sounds/shot.wav");
	deathBuffer.loadFromFile("../sounds/death.wav");
	explosionBuffer.loadFromFile("../sounds/explosion.wav");

	shotSound = sf::Sound(shotBuffer);
	deathSound = sf::Sound(deathBuffer);
	explosionSound = sf::Sound(explosionBuffer);
}

void SoundManager::dispose()
{
	shotSound.~Sound();
	deathSound.~Sound();
	explosionSound.~Sound();

	shotBuffer.~SoundBuffer();
	deathBuffer.~SoundBuffer();
	explosionBuffer.~SoundBuffer();
}

void SoundManager::play(soundType type)
{
	if (type == SHOT)
		shotSound.play();
	else if (type == DEATH)
		deathSound.play();
	else
		explosionSound.play();
}

SoundManager::~SoundManager()
{
	delete sound_instance;
}