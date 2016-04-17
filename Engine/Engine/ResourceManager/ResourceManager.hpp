#pragma once
#include "ResourceGroup.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp" 
#include "..\Utility\Utilities.hpp"


class ResourceManager : public NameSearchable								//This class will basically hold all textures, fonts, and soundBufs.
{
	//typedef const std::string& crstring;									//possible typedef to make code visually prettier -- turns "const std::string&"
	//into "crstring"
public:

	ResourceManager();														//Constructor
	~ResourceManager();														//Destructor

	void loadFileTree(const std::string& directory);												//loads all files from a directory tree

	void loadFileTree(const std::string& directory, const std::string& ext);					//loads all files of the same specified
	//extension from a directory tree


	void loadFileDirectory(const std::string& directory);											//loads all files from a directory

	void loadFileDirectory(const std::string& directory, const std::string& ext);			//loads all files of the same specified extension
	//from a directory


	void addFilesResourceGroupFromDirectory(const std::string& directory);								//adds files from a directory and makes a resource
	//group out of them (name of RG is invented)

	void addFilesResourceGroupFromDirectory(const std::string& directory, const std::string& RGName);	//adds files from a directory and makes a resource
	//group out of them (name of RG is specified)

	void loadFile(const std::string& fileName, const std::string& name);				//adds a generic file


	sf::Texture* getTexturePointerByIndex(const int& index);

	sf::Texture* getTexturePointerByName(const std::string& name);					//retrieves a pointer to a texture

	sf::Font* getFontPointerByName(const std::string& name);						//retrieves a pointer to a font

	sf::SoundBuffer* getSoundBufferPointerByName(const std::string& name);			//retrieves a pointer to a soundBuffer



	void addEmptyResourceGroup(const std::string& name);									//sets a new empty resourceGroup to ResourceGroups

	void addResourceGroup(ResourceGroup fResourceGroup, const std::string& name);			//sets a currently filled resourceGroup to ResourceGroups



	void addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, const std::string& ext);
	//adds a generic resource to a resourceGroup
	//(interprets type, no name)

	void addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, std::string ext, const std::string& desName);
	//adds a generic resource to a resourceGroup
	//(interprets type, specified name)


	void addTexturetoResourceGroup(const std::string& rsName, const std::string& texName);	//adds a texture to a resourceGroup (no name)

	void addTexturetoResourceGroup(const std::string& rsName, const std::string& texName, const std::string& desName);
	//adds a texture to a resourceGroup (specified name)


	void addFonttoResourceGroup(const std::string& rsName, const std::string& fontName);	//adds a font to a resourceGroup (no name)

	void addFonttoResourceGroup(const std::string& rsName, const std::string& fontName, const std::string& desName);
	//adds a font to a resourceGroup (specified name)


	void addSoundBuffertoResourceGroup(const std::string& rsName, const std::string& sbName);
	//adds a soundbuffer to a resourceGroup (no name)

	void addSoundBuffertoResourceGroup(const std::string& rsName, const std::string& sbName, const std::string& desName);
	//adds a soundbuffer to a resourceGroup (specified name)


	ResourceGroup* getResourceGroupByName(const std::string& fname);						//returns a pointer to a resourceGroup


private:

	void swapChars(char& a, char& b);						//swaps the values of two chars

	std::string reverseString(std::string str);				//returns the reverse of the string entered


	std::string getExtension(const std::string& fpath);		//returns the extension name ("REDTEXTURE.png" -> "png" [note not ".png"])

	std::string getFileName(const std::string& fpath);		//returns the file name ("DIRECTORY\\REDTEXTURE.png" -> "REDTEXTURE")

	std::string getDirectoryName(const std::string& fpath);	//returns the directory name ("DIRECTORY_1\\DIRECTORY_2" -> "DIRECTORY_2")


	void fillFileNameVectorFromTree(const std::string& directory, std::vector<const std::string>& namevec);
	//fills a vector of strings with all files from a directory tree

	void fillFileNameVectorFromDirectory(const std::string& directory, std::vector<const std::string>& namevec);
	//fills a vector of strings with all files from a directory


	void addTexture(const std::string& fileName);			//adds a Texture

	void addFont(const std::string& fileName);				//adds a Font

	void addSoundBuffer(const std::string& fileName);		//adds a SoundBuffer



	std::vector<const sf::Texture> textureVector;			//vector of textures

	std::vector<const sf::Font> fontVector;					//vector of fonts

	std::vector<const sf::SoundBuffer> soundBufferVector;	//vector of soundBuffers


	std::vector<ResourceGroup> resourceGroups;				//presets for graphical elements that may look the same


	const enum nameVectorIndeces { Texture_Names = 0, Font_Names = 1, SoundBuffer_Names = 2, ResourceGroup_Names = 3 };
	//enum for accessing vectors more intuitively

	src::severity_logger<severity_level> resourceManagerLogger;
	//logger for reporting errors, warnings, debug messages, etc.
};
