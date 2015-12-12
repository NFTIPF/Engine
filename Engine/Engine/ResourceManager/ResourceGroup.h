#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Namesearchable/NameSearchable.h"



class ResourceGroup : public NameSearchable								//essentially just a group of Textures, Fonts, and soundBuffers
{

/*---------------------------------------------------------------------------------------------------------

NOTES: SoundBuffer doesnt work yet, lots of other commented functions will probably not be used

----------------------------------------------------------------------------------------------------------*/


public:

	ResourceGroup();													//Constructor -- empty

	void addTexture(sf::Texture* ftexture);								//adds a texture

	void addTexture(sf::Texture* ftexture, std::string fname);			//adds a texture


	void addFont(sf::Font* ffont);										//adds a font

	void addFont(sf::Font* ffont, std::string name);					//adds a font


	void addSoundBuf(sf::SoundBuffer* fsoundbuf);						//adds a soundBuf

	void addSoundBuf(sf::SoundBuffer* fsoundbuf, std::string name);		//adds a soundBuf




	std::vector<sf::Texture*> getTextureVector();						//returns the entire textureVector

	std::vector<sf::Font*> getFontVector();								//returns the entire fontVector

	std::vector<sf::SoundBuffer*> getSoundBufVector();					//returns the entire SoundBufVector





	sf::Texture* getTexturePointer(int findex);							//returns an element of textureVector

	sf::Texture* getTexturePointer(std::string name);					//returns an element of textureVector


	sf::Font* getFontPointer(int findex);								//returns an element of fontVector

	sf::Font* getFontPointer(std::string name);							//returns an element of fontVector


	sf::SoundBuffer* getSoundBufPointer(int findex);					//returns an element of soundBufVector

	sf::SoundBuffer* getSoundBufPointer(std::string findex);					//returns an element of soundBufVector



private:


	std::vector<sf::Texture*> textureVector;							//vector of Textures

	std::vector<sf::Font*> fontVector;									//vector of Fonts

	std::vector<sf::SoundBuffer*> soundBufVector;						//vector of SoundBuffers



	enum VectorNames { Texture_Vector = 0, Font_Vector = 1, SoundBuf_Vector = 2 };
};

