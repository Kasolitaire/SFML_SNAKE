#include "AssetManager.h";

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
    unordered_map<string, SoundBuffer>& r_bufferMap = s_assetManager.m_soundBuffers;
    if (r_bufferMap.find(filename) == r_bufferMap.end())
    {
        SoundBuffer& soundBuffer = r_bufferMap[filename];
        soundBuffer.loadFromFile(filename);
        return soundBuffer;
    }
    else return r_bufferMap.at(filename);
}

Texture& AssetManager::GetTexture(const string& filename)
{
    unordered_map<string, Texture>& r_textureMap = s_assetManager.m_textures;
    if (r_textureMap.find(filename) == r_textureMap.end())
    {
        Texture& texture = r_textureMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
    else return r_textureMap.at(filename); //returning reference of data member, still in scope!!!
}

Font& AssetManager::GetFont(const string& filename)
{
    unordered_map<string, Font>& r_fontMap = s_assetManager.m_fonts;
    if (r_fontMap.find(filename) == r_fontMap.end()) 
    {
        Font& font = r_fontMap[filename];
        font.loadFromFile(filename);
        return font;
    }
    else return r_fontMap.at(filename); //returning reference of data member, still in scope!!!
}


