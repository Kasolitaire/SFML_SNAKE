#pragma once
#include<SFML/Graphics.hpp>;
#include<SFML/Audio.hpp>;
#include<unordered_map>;
#include<string>;
using namespace sf;
using namespace std;

class AssetManager
{
public:
	AssetManager(const AssetManager&) = delete; // insures that they instance cannot be copied
	static AssetManager& Get(); // return reference to instance
	static SoundBuffer& GetSoundBuffer(const string& filename);
	static Texture& GetTexture(const string& filename);
	static Font& GetFont(const string& filename);
private:	
	AssetManager();
	static AssetManager s_assetManager;
	unordered_map<string, SoundBuffer> m_soundBuffers;
	unordered_map<string, Font> m_fonts;
	unordered_map<string, Texture> m_textures;

};

