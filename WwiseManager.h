#pragma once
#include <cstdint>

constexpr auto WWISE_BANKS_PATH = L"D:/WwiseProjects/ITest/GeneratedSoundBanks/Windows/";


class WwiseManager 
{
public:
    bool initSoundEngine();
    void shutdownSoundEngine();
    void ProcessAudio();
    int RunWwise();
    void CustomPostEvent(const char* eventName);

private:
    //Game object reference for post event
    const uint64_t Listener = 100;
    
};