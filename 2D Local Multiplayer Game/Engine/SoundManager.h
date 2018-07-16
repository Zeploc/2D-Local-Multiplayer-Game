
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    SoundManager.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <memory>
#include <string>
#include <vector>

// OpenGL Library Includes //
#include <fmod.hpp>

#pragma once
class SoundManager
{
public:

	bool InitFMod();

	FMOD::System* audioMgr;


	struct SoundObject
	{
		FMOD::Sound* Sound;
		std::string sName;
	};
	struct ChannelObject
	{
		FMOD::Channel* channel;
		std::string sName;
	};
	
	const bool AddAudio(const char* Path, bool bLoop, std::string sName);
	FMOD::Sound* GetAudio(std::string sName);
	void AddChannel(std::string sName);
	bool PlayAudio(std::string sName, std::string sChannel);
	bool PauseAudio(std::string sChannel);
	bool StopAudio(std::string sChannel);
	bool SetChannelVolume(std::string sChannel, float _fVolume);

private:
	std::vector<SoundObject> Sounds;
	std::vector<ChannelObject> Channels;

	bool ChannelExists(std::string sName);
	int GetChannelID(std::string sName);

	// Singleton
public:
	static std::shared_ptr<SoundManager> GetInstance();
	static void DestoryInstance();
	~SoundManager(); // Shared pointer has to be able to call destructor so can't be private

private:
	static std::shared_ptr<SoundManager> m_pSoundManager;
	SoundManager();
	SoundManager(SoundManager const&);              // Don't Implement
	void operator=(SoundManager const&); // Don't implement
};

