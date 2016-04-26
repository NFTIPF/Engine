#pragma once

#include "Object.hpp"
#include <SFML\Graphics.hpp>
#include "Physics/Movement/PhysicsObject.hpp"
#include "Graphics\Texture.hpp"
#include "../Utility/INIParser.hpp"

namespace objects
{
	class ParticleSystem : public Object
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		void draw(Layer& renderTarget);
		void update(InputData& inpData);
		void load(boost::property_tree::ptree& dataTree, ResourceManager& rMan);
		boost::property_tree::ptree write();

		void setPosition(sf::Vector2f& position);
	private:
		typedef std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f, double, double> particle;

		void generateParticles();
		double getSinusoidalValue(const double& bound, const double& offset);
		sf::Vector2f randomVector(const sf::Vector2f& min, const sf::Vector2f& max);
		

		int sign(const float& d);

		float randomNum(const float& min, const float& max);

		std::string systemType;	//tag to load data from ini with
		bool moving;			//wether or not the origin of the system changes

		Texture drawing;

		std::vector<particle> particles;	//pos, vel, acc

		std::string textureName;

		sf::Vector2f* position;
		sf::Vector2f particleSize;				//average particle size
		sf::Vector2f particleSizeVariation;		//posible variation in size

		double lifeSpan;	//lifespan in frames or seconds
		double gravityEffect;
		sf::Vector2f wind;	//constant application of wind of range or random move
		double particleWindVariance;
		double upwardWindPreference;

		bool randomSpawn;	//spawning at top or random
		bool randomMove;
		sf::Vector2f spawnArea;
		int numParticles;

		sf::Clock timer; // allows sinusoidal motion based on time
		double frameTime;
		double lastFrameElapsedTime;
		double genFrameTime;
		int newParticleNumber;
		float speed;
	};
}
