#pragma once
#include "ResourceGroup.h"




class ResourceManager : public NameSearchable								/*This class will basically hold all textures, fonts, and soundBufs.*/
{																			/*Part of this is unimpressive -- IT DOES NOT CURRENTLY
																			load all files from a directory.*/

/*---------------------------------------------------------------------------------------------------------

NOTES: SoundBuffer doesnt work yet, so elements that pertain to them are likely commented out for now.

----------------------------------------------------------------------------------------------------------*/


public:

	ResourceManager();														//Constructor


	void addFile(std::string fileName, std::string name);					//Adds a generic file



	sf::Texture* getTexturePointerByName(std::string name);					//retrieves a pointer to a texture
	sf::Font* getFontPointerByName(std::string name);						//Retrieves a pointer to a font
	sf::SoundBuffer* getSoundBufPointerByName(std::string name);



	void addEmptyResourceGroup(std::string name);								//sets a new empty resourceGroup to ResourceGroup
	void addResourceGroup(ResourceGroup fResourceGroup, std::string name);		//sets a currently filled resourceGroup to ResourceGroup


	void addTexturetoResourceGroup(std::string rsName, std::string texName);	//adds a Texture to a ResourceGroup
	void addFonttoResourceGroup(std::string rsName, std::string fontName);		//adds a Font to a ResourceGroup
	void addSoundBuftoResourceGroup(std::string rsName, std::string sbName);
	
	ResourceGroup* getResourceGroupByName(std::string fname); 
	


private:




	void addTexture(std::string fileName);									//adds a Texture
	void addFont(std::string fileName);										//adds a Font
	void addSoundBuf(std::string fileName);									//adds a SoundBuf




	std::vector<sf::Texture> textureVector;									//vector of Textures that will be used in the program

	std::vector<sf::Font> fontVector;										//vector of Fonts that will be used in the whole program
	
	std::vector<sf::SoundBuffer> soundBufVector;



	std::vector<ResourceGroup> resourceGroups;								/*presets for certain things like BasicButton. BasicButton will use
																			the preset Textures, Fonts, and SoundBuffers for BasicButton*/


	
	enum nameVectorIndeces {Texture_Names = 0, Font_Names = 1, SoundBuf_Names = 2, ResourceGroup_Names = 3}; 
																			//enum for accessing vectors more intuitively


	
};

