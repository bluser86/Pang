#include "Include.h"
#include "SoundFileCache.h"

SoundFileCache::SoundFileCache(void) {}

SoundFileCache::~SoundFileCache(void)
{
	std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer*>());
	std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music*>());
}

sf::Sound SoundFileCache::GetSound(std::string soundName) const
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = _sounds.find(soundName);

	if (it == _sounds.end())
	{
		sf::SoundBuffer *soundBuffer = new sf::SoundBuffer;
		if (!soundBuffer->loadFromFile(soundName)) 
		{
			delete soundBuffer;
			throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSound");
		}

		std::map<std::string, sf::SoundBuffer*>::iterator res = _sounds.insert(
			std::pair<std::string, sf::SoundBuffer*>(soundName, soundBuffer)).first;

		sf::Sound sound;
		sound.setBuffer(*soundBuffer);
		return sound;
	}
	else 
	{
		sf::Sound sound;
		sound.setBuffer(*it->second);
		return sound;
	}

	throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSound");
}

sf::Music* SoundFileCache::GetSong(std::string musicName) const
{
	std::map<std::string, sf::Music*>::iterator it = _music.find(musicName);

	if (it == _music.end())
	{
		sf::Music *music = new sf::Music;
		if (!music->openFromFile(musicName)) 
		{
			delete music;
			throw SoundNotFoundException(musicName + " was not found in call to SoundFileCache::GetSound");
		}

		std::map<std::string, sf::Music*>::iterator res = _music.insert(
			std::pair<std::string, sf::Music*>(musicName, music)).first;

		return res->second;
	}
	else 
	{
		return it->second;
	}

	throw SoundNotFoundException(musicName + " was not found in call to SoundFileCache::GetSound");
}

std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;