#pragma once

//sfml includes
# include "..\Object.hpp"
#include "..\Physics\Collision\Collidable.hpp"
#include "..\Physics\Collision\Hitboxes\AAHitbox.hpp"
#include "..\..\MenuStuff\AppSprite.hpp"


namespace objects
{

	class Platform : public Object, public Collidable
	{

	public:

		Platform();
		Platform(const sf::Vector2f& pos, const double& width, const double& height, sf::Texture* tex);
		Platform(const sf::Vector2f& TL, const sf::Vector2f& BR, sf::Texture* tex);

		~Platform();

		void setup(const sf::Vector2f& pos, const double& width, const double& height, sf::Texture* tex);
		void setup(const sf::Vector2f& TL, const sf::Vector2f& BR, sf::Texture*);

		void draw(Layer& renderTarget);		//renders object to given sf::RenderTexture&

		void update(InputData& inpData) {}


		void load(boost::property_tree::ptree& dataTree, ResourceManager&);	//defined in children to load from (INI?) file
		boost::property_tree::ptree write();

	private:
		sf::Vector2f getTlCorner();
		sf::Vector2f getBRCorner();

		sf::Texture* platformTexture;
		sf::VertexArray texCoords;
		sf::Vector2f position;
		sf::Vector2f size;

		std::string textureName;


	};

}