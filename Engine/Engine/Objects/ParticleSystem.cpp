#include "ParticleSystem.hpp"

using namespace objects;

ParticleSystem::ParticleSystem()
{
	randomMove = true;
	timer.restart();
	frameTime = .1;
	lastFrameElapsedTime = 0;
	newParticleNumber = 0;
	genFrameTime = 0;
	position = &sf::Vector2f(0, 0);
}

ParticleSystem::~ParticleSystem(){}

void ParticleSystem::draw(Layer& rendertarget)
{
	sf::RenderTexture& texture = *rendertarget.getRenderTexture();
	sf::Vector2f drawHelperPos;
	for (unsigned int partIt = 0; partIt < particles.size(); partIt++)
	{
		drawHelperPos = std::get<0>(particles[partIt]);
		drawing.setPosition(&drawHelperPos);
		drawing.setSize(&particleSize);
		drawing.draw(texture);
	}
}

void ParticleSystem::update(InputData& inputData)
{
	frameTime = timer.getElapsedTime().asSeconds() - lastFrameElapsedTime;
	genFrameTime += frameTime;
	newParticleNumber = numParticles / lifeSpan * genFrameTime;

	sf::Vector2f grav = sf::Vector2f(0, GRAVITY / gravityEffect);

	const double yWindMultiplier = .4;
	const double tmpGust = (1 - yWindMultiplier) / 2;
	const sf::Vector2f generalGust(getSinusoidalValue(1,0) * wind.x, (getSinusoidalValue(tmpGust, 10) + yWindMultiplier + tmpGust) * wind.y );

	for (unsigned int partIt = 0; partIt < particles.size(); partIt++)
	{
		particle& p = particles[partIt];
		if (std::get<3>(p) < 0)
		{
			particles.erase(particles.begin() + partIt);
			partIt--;
		}
		else
		{
			std::get<1>(p) += std::get<2>(p);	//vel += acc
			std::get<0>(p) += std::get<1>(p);	//pos += vel
			if (randomMove)
			{
				
				//std::get<2>(p) = sf::Vector2f(wind.x, wind.y) + grav;	//reset acceleration
				

				const double offset = std::get<4>(p);
				const double tmpInd = (particleWindVariance - upwardWindPreference) / 2;
				const sf::Vector2f smallWind(sf::Vector2f(getSinusoidalValue(particleWindVariance, offset) * wind.x,
														((getSinusoidalValue(tmpInd, offset + 25) + upwardWindPreference + tmpInd) * wind.y)));

				std::get<2>(p) = generalGust + smallWind;
			}
			else
			{
				std::get<2>(p) = sf::Vector2f(wind.x, wind.y) + grav;	//reset acceleration
			}
			std::get<3>(p) -= frameTime;

		}
		sf::Vector2f velocity = std::get<1>(p);
		sf::Vector2f s = sf::Vector2f(sign(velocity.x), sign(velocity.y));
		sf::Vector2f air = sf::Vector2f(s.x * velocity.x * velocity.x * AIR, s.y * velocity.y * (velocity.y/10) * AIR);	//calculating air resistance
		air += sf::Vector2f(0, speed);
		std::get<1>(p) -= air;

	}

	
	generateParticles();
	lastFrameElapsedTime = timer.getElapsedTime().asSeconds();
}

void ParticleSystem::load(boost::property_tree::ptree& dataTree, ResourceManager& rMan)
{
	XMLParser parser;
	parser.readValue<std::string>("systemType", systemType, dataTree);
	speed = 0;
	INIParser reader("ParticleSystems.ini");	//load configuration file for particle systems

	reader.setSection(systemType);
	reader.readValue<std::string>("TextureName", textureName);
	reader.readValue<float>("ParticleSize_X", particleSize.x);
	reader.readValue<float>("ParticleSize_Y", particleSize.y);
	reader.readValue<float>("ParticleVar_X", particleSizeVariation.x);
	reader.readValue<float>("ParticleVar_Y", particleSizeVariation.y);
	reader.readValue<double>("Lifespan", lifeSpan);
	reader.readValue<double>("GravityCut", gravityEffect);
	reader.readValue<double>("Floatiness", upwardWindPreference);
	reader.readValue<float>("Wind_X", wind.x);
	reader.readValue<float>("Wind_Y", wind.y);
	reader.readValue<double>("Particle_Wind_Variance", particleWindVariance);
	reader.readValue<bool>("RandomSpawn", randomSpawn);
	reader.readValue<float>("SpawnArea_X", spawnArea.x);
	reader.readValue<float>("SpawnArea_Y", spawnArea.y);
	reader.readValue<int>("NumParticles", numParticles);
	reader.readValue<bool>("Moving", moving);
	reader.readValue<float>("Speed", speed);

	sf::Texture* particleTexture = rMan.getTexturePointerByName(textureName);	//retrive particle texture name


	drawing = Texture(particleTexture, &wind, &particleSize);

	generateParticles();
}

boost::property_tree::ptree ParticleSystem::write()
{
	boost::property_tree::ptree tree;
	tree.put("systemType", systemType);
	tree.put("type", type);
	return tree;
}

void ParticleSystem::setPosition(sf::Vector2f& newPos)
{
	position = &newPos;
}

//private functions
void ParticleSystem::generateParticles()
{
	bool ranThrough = false;
	for (unsigned int gen = 0; gen <  newParticleNumber  && particles.size() < numParticles; gen++)
	{
		particle p = std::make_tuple(randomVector(sf::Vector2f(0, 0), sf::Vector2f(spawnArea.x, 100)),
			randomVector(sf::Vector2f(-1 * wind.x, -1 * wind.y), wind), sf::Vector2f(0, GRAVITY / gravityEffect), randomNum(lifeSpan / 3, lifeSpan), randomNum(0,100));

		particles.push_back(p);
		ranThrough = true;
	}
	if (ranThrough)
	{
		genFrameTime = 0;
	}
	
}

double ParticleSystem::getSinusoidalValue(const double& bound, const double& offset)
{
	//this is very arbitrary, btw

	double t = timer.getElapsedTime().asSeconds() + offset;

	const double peroidModifier = 40;
	const double ka = 2;
	const double pa = 41;
	const double kb = 5;
	const double pb = 23;
	const double kc = 4;
	const double pc = 7;

	const double ssa = ka * sin(pa * t / peroidModifier);
	const double ssb = kb * sin(pb * t / peroidModifier);
	const double ssc = kc * sin(pc * t / peroidModifier);

	const double sum = ssa + ssb + ssc;

	const double maxVal = 10.3; //it is what it is lol

	return sum * bound / 10.3;


	

}

sf::Vector2f ParticleSystem::randomVector(const sf::Vector2f& min, const sf::Vector2f& max)
{
	float xMult = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float yMult= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return min + (sf::Vector2f((max.x - min.x)*xMult, (max.y - min.y)*yMult));
}

float ParticleSystem::randomNum(const float& min, const float& max)
{
	return min + (max * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
}

int ParticleSystem::sign(const float& d)
{
	if (d >= 0){ return 1; }
	else{ return -1; }
}