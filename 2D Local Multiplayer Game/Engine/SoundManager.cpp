//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    SoundManager.cpp
// Description    	:    main implementation for SoundManager
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//
// Library Includes //

// OpenGL Library Includes //

// Engine Includes //
#include "LogManager.h"

// Local Includes //

// This Includes //
#include "SoundManager.h"

// Static Variables //
std::shared_ptr<SoundManager> SoundManager::m_pSoundManager;

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
SoundManager::SoundManager()
{
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
SoundManager::~SoundManager()
{

}

/************************************************************
#--Description--#: 	Initialises FMOD
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		Returns false if failed to initialise
************************************************************/
bool SoundManager::InitFMod()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioMgr);
	if (result != FMOD_OK)
		return false;

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
		return false;

	return true;
}

/************************************************************
#--Description--#: 	Adds audio to vector and to sound manager
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Sound path, whether it loops and a name for the sound
#--Return--#: 		returns false if sound already created
************************************************************/
const bool SoundManager::AddAudio(const char * Path, bool bLoop, std::string sName)
{
	FMOD::Sound* CreatedSound;
	FMOD_RESULT result;
	result = audioMgr->createSound(Path, FMOD_DEFAULT, 0, &CreatedSound);
	if (!CreatedSound) return false;
	if (bLoop)
		CreatedSound->setMode(FMOD_LOOP_NORMAL);
	SoundObject NewSoundObj = { CreatedSound , sName };
	Sounds.push_back(NewSoundObj);
	LogManager::GetInstance()->DisplayLogMessage("Loading audio file at \"" + std::string(Path) + "\"");
	return true;
}

/************************************************************
#--Description--#:  Retrieve sound pointer
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in sound string name
#--Return--#: 		Pointer to sound object
************************************************************/
FMOD::Sound* SoundManager::GetAudio(std::string sName)
{
	for (auto sndobj : Sounds)
	{
		if (sndobj.sName == sName)
		{
			return sndobj.Sound;
		}
	}
	return nullptr;
}

/************************************************************
#--Description--#:  Add channel with new name
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes name for channel
#--Return--#: 		NA
************************************************************/
void SoundManager::AddChannel(std::string sName)
{
	if (ChannelExists(sName))
		return;
	FMOD::Channel* NewChannel = nullptr;
	ChannelObject newChannelObj = { NewChannel, sName };
	Channels.push_back(newChannelObj);
}

/************************************************************
#--Description--#:  Plays audio by name and channel
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes sound name and channel name
#--Return--#: 		Return false if audio doesn't exist
************************************************************/
bool SoundManager::PlayAudio(std::string sName, std::string sChannel)
{
	FMOD::Channel* newChannel;
	if (ChannelExists(sChannel))
		newChannel = Channels[GetChannelID(sChannel)].channel;
	if (GetAudio(sName) == nullptr)
		return false;
	audioMgr->playSound(GetAudio(sName), 0, false, &newChannel);
	Channels[GetChannelID(sChannel)].channel = newChannel;
	return true;
}

/************************************************************
#--Description--#:  Pauses audio channel
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes channel name
#--Return--#: 		Return false if channel doesn't exist
************************************************************/
bool SoundManager::PauseAudio(std::string sChannel)
{
	if (!ChannelExists(sChannel))
		return false;
	Channels[GetChannelID(sChannel)].channel->setPaused(true);
	return true;
}

/************************************************************
#--Description--#:  Stops audio channel
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes channel name
#--Return--#: 		Return false if channel doesn't exist
************************************************************/
bool SoundManager::StopAudio(std::string sChannel)
{
	if (!ChannelExists(sChannel))
		return false;
	Channels[GetChannelID(sChannel)].channel->stop();
	return true;
}

/************************************************************
#--Description--#:  Sets audio volume for channel
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes channel name and new volume
#--Return--#: 		Return false if channel doesn't exist
************************************************************/
bool SoundManager::SetChannelVolume(std::string sChannel, float _fVolume)
{
	if (!ChannelExists(sChannel))
		return false;
	Channels[GetChannelID(sChannel)].channel->setVolume(_fVolume);
	return true;
}

/************************************************************
#--Description--#:  Checks if channel exists
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes channel name
#--Return--#: 		Return false if channel doesn't exist
************************************************************/
bool SoundManager::ChannelExists(std::string sName)
{
	for (auto channelobj : Channels)
	{
		if (channelobj.sName == sName)
			return true;
	}
	return false;
}

/************************************************************
#--Description--#:  Finds channel ID
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes channel name
#--Return--#: 		Return channel id or -1 if invalid
************************************************************/
int SoundManager::GetChannelID(std::string sName)
{
	if (!ChannelExists(sName))
		AddChannel(sName);
	for (unsigned int i = 0; i < Channels.size(); i++)
	{
		if (Channels[i].sName == sName)
			return i;
	}
	return -1;
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
std::shared_ptr<SoundManager> SoundManager::GetInstance()
{
	if (!m_pSoundManager) // null or doesn't exist
	{
		m_pSoundManager = std::shared_ptr<SoundManager>(new SoundManager());
	}
	return m_pSoundManager;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void SoundManager::DestoryInstance()
{
	m_pSoundManager = nullptr;
}
