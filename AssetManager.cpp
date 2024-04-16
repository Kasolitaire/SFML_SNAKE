#include "AssetManager.h"

AssetManager AssetManager::s_assetManager;
AssetManager::AssetManager()
{
}
AssetManager& AssetManager::Get()
{
    return s_assetManager;
}

SoundBuffer& AssetManager::GetSoundBuffer(const string& filename)
{
    unordered_map<string, SoundBuffer>& r_bufferMap = s_assetManager.m_SoundBuffers;
    if (r_bufferMap.find(filename) == r_bufferMap.end())
    {
        SoundBuffer& soundBuffer = r_bufferMap[filename];
        soundBuffer.loadFromFile(filename);
        return soundBuffer;
    }
    else return r_bufferMap.at(filename);
}


