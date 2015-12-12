#include "ResourceManager.h"
#include <iostream>



//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PUBLIC-----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************



/*------------------------------------------------------------------------------------
-------------------------------Constructor--------------------------------------------
------------------------------------------------------------------------------------*/
ResourceManager::ResourceManager()											//Constructor
{
	setVectorSize(4);
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addFile------------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addFile(std::string fileName, std::string name)		//adds a generic file
{



	std::string reverseExt = "";											//will be a reversed file extension
	std::string ext = "";													//will be the actual file extension

	for (int i = fileName.size() - 1; i >= 0; i--)							/*cycles from the back of the file name
																			and records the reversed file extension*/
	{
		if (fileName[i] == '.')												//goes to the dot
		{
			break;
		}
		else
		{
			reverseExt += fileName[i];										//otherwise, record the letter -- will be backwards when done in succession
		}
	}


	for (int i = reverseExt.size() - 1; i >= 0; i--)						//reverses the file extension
	{
		ext += reverseExt[i];
	}



	//---------------------------------------------
	//Now we interpret the file extension.
	//----------------------------------------------

	if (ext == "ttf")														//.ttf is a font
	{
		addFont(fileName);													//add the font

		addName(name, Font_Names, fontVector.size() - 1);				//add the name
	}



	else if (	ext == "png" || 
				ext == "jpg" || 
				ext == "jpeg" ||	
				ext == "bmp")												//these extensions are textures
	{
		addTexture(fileName);												//add the texture

		addName(name, Texture_Names, textureVector.size() - 1);				//add the name
	}


	else if (	ext == "wav" ||
				ext == "aif" ||
				ext == "mp3" ||
				ext == "mp2" ||
				ext == "ogg" ||
				ext == "raw")
	{
		addSoundBuf(fileName);
		addName(name, SoundBuf_Names);
	}


}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------getTexturePointer--------------------------------------
------------------------------------------------------------------------------------*/
sf::Texture* ResourceManager::getTexturePointerByName(std::string fname)					//returns a pointer to a Texture
{
	sf::Texture* returnMe;																//make a temporary pointer to a texture

	returnMe = &textureVector[ntoi(fname, Texture_Names)];							//set it to the texture with the desired name  

	return returnMe;																	//return it
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------getFontPointer-----------------------------------------
------------------------------------------------------------------------------------*/
sf::Font* ResourceManager::getFontPointerByName(std::string fname)						//returns a pointer to a Font
{

	sf::Font* returnMe;																	//make a temporary pointer to a font

	returnMe = &fontVector[ntoi(fname, Font_Names)];									//set it to the font with the desired name

	return returnMe;																	//return it
	
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------getsbpointer-------------------------------------------
------------------------------------------------------------------------------------*/
sf::SoundBuffer* ResourceManager::getSoundBufPointerByName(std::string fname)			//returns a pointer to a soundbuf
{

	sf::SoundBuffer* returnMe;																	//make a temporary pointer to a font

	returnMe = &soundBufVector[ntoi(fname, SoundBuf_Names)];									//set it to the font with the desired name

	return returnMe;																	//return it

}


//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addEmptyRS---------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addEmptyResourceGroup(std::string fname)								//adds an empty resourceGroup and give it a name
{
	ResourceGroup empt;																		//make an empty resource group

	resourceGroups.push_back(empt);															//add it
	
	addName(fname, ResourceGroup_Names, resourceGroups.size() - 1);							//add the name
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addRS--------------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addResourceGroup(ResourceGroup fResourceGroup, std::string fname)		//adds an already created resourceGroup and name it
{

	resourceGroups.push_back(fResourceGroup);												//add the resourceGroup

	addName(fname, ResourceGroup_Names, resourceGroups.size() - 1);
	
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addTexturetoRS-----------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addTexturetoResourceGroup(std::string rsName, std::string texName)	//adds a Texture to a ResourceGroup by name
{
	
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName));
																						//literally just add the texture
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addFontoRS---------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addFonttoResourceGroup(std::string rsName, std::string fontName)	//adds a Font to a ResourceGroup by name
{
	
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName));
																						//literally just add the font
	
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addSoundBuftoRS----------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addSoundBuftoResourceGroup(std::string rsName, std::string sbName)					//adds a SoundBuf to a ResourceGroup by name
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuf(getSoundBufPointerByName(sbName));
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------getResourceGroupByName-----------------------------------
------------------------------------------------------------------------------------*/
ResourceGroup* ResourceManager::getResourceGroupByName(std::string fname)					//retrives a resourceGroup by name
{

	return &resourceGroups[ntoi(fname, ResourceGroup_Names)];							//returns the resource set with the desired name
	
}






//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PRIVATE----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************



/*------------------------------------------------------------------------------------
-------------------------------addTexture---------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addTexture(std::string fileName)									//private function; adds a Texture to the TextureVector
{
	sf::Texture texture;																//make a temporary texture

	if (!texture.loadFromFile(fileName))												//try to make it load from the file
	{
		std::cout << fileName << " (Texture) failed to load." << std::endl;				// if it doesn't, there is an error
	}

	textureVector.push_back(texture);													//add the texture

}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addFont------------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addFont(std::string fileName)										//private function; adds a font to the FontVector
{
	sf::Font font;																		//make a temporary font

	if (!font.loadFromFile(fileName))													//try to make it load from the file
	{
		std::cout << fileName << " (Font) failed to load." << std::endl;				// if it doesn't, there is an error
	}

	fontVector.push_back(font);															//add the font
}



//----------------------------------------------------------------------------------------------------------------------------***************************


/*------------------------------------------------------------------------------------
-------------------------------addSoundBuf-------------------------------------------
------------------------------------------------------------------------------------*/
void ResourceManager::addSoundBuf(std::string fileName)								//private function; adds a soundBuf to the soundBufVector
{

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(fileName))
	{
		std::cout << fileName << " (SoundBuffer) failed to load." << std::endl;
	}
	soundBufVector.push_back(buffer);

}



//----------------------------------------------------------------------------------------------------------------------------***************************