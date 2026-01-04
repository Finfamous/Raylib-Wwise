#include "WwiseManager.h"

#include <iostream>
//Memory Manager Includes
#include <Ak/SoundEngine/Common/AkMemoryMgr.h>
#include <Ak/SoundEngine/Common/AkMemoryMgrModule.h>
//Streaming Manager includes
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <AkFilePackageLowLevelIODeferred.h>

#include <Ak/SoundEngine/Common/AkSoundEngine.h>

//Wise info 
#include "D:/WwiseProjects/ITest/GeneratedSoundBanks/Wwise_IDs.h"

CAkFilePackageLowLevelIODeferred g_lowLevelIO;




bool WwiseManager::initSoundEngine()
{
    // Init Memory Manager 
    AkMemSettings memSettings;
    AK::MemoryMgr::GetDefaultSettings(memSettings);

    if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
    {
        std::cout << "Could not create the memory manager." << std::endl;
        return false;
    }

    // Init Streaming Manager
    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    // Customize the Stream Manager settings here.

    if (!AK::StreamMgr::Create(stmSettings)) 
    {
        std::cout << "Could not create the Streaming Manager" << std::endl;
        return false;
    }


    // Create a streaming device.
    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);


    if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {
        std::cout << "Could not create the streaming device and Low-Level I/O system" << std::endl;
        return false;
    }

    g_lowLevelIO.SetBasePath(WWISE_BANKS_PATH);

    //Create Sound Engine
    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        std::cout << "Could not initialize the Sound Engine." << std::endl;;
        return false;
    }



    return true;
}



void WwiseManager::shutdownSoundEngine()
{

    AK::SoundEngine::Term();

    g_lowLevelIO.Term();

    if (AK::IAkStreamMgr::Get()) AK::IAkStreamMgr::Get()->Destroy();

    AK::MemoryMgr::Term();
}

void WwiseManager::ProcessAudio()
 {
    AK::SoundEngine::RenderAudio();
 }

int WwiseManager::RunWwise()
{
    if (initSoundEngine() == true)
    {
        std::cout << "SUCCESS! initialised Wwise." << std::endl;
    }
    else
    {
        std::cout << "FAILED to initialise Wwise." << std::endl;
    }


    //Load init and custom soundbank
    AkBankID initBankID;
    AkBankID soundBankID;
    AKRESULT eResult = AK::SoundEngine::LoadBank(L"Init.bnk", initBankID);
    if (eResult == AK_Success)
    {
        eResult = AK::SoundEngine::LoadBank(L"Main.bnk", soundBankID);
        std::cout << "SUCCESS! Loaded banks" << std::endl;
    }
    else
    {
        std::cout << "FAILED to load banks" << std::endl;
    }




    return 0;
}



void WwiseManager::CustomPostEvent(const char* eventName)
{
    //Game object reference for post event

    AK::SoundEngine::RegisterGameObj(Listener);
    //Set the default Listener
    AK::SoundEngine::SetDefaultListeners(&Listener, 1);
    //post event
    AkPlayingID StunPlayingID = AK::SoundEngine::PostEvent(eventName, Listener);
    std::cout << (StunPlayingID != AK_INVALID_PLAYING_ID ? "Event posted\n" : "Event failed\n");
}

