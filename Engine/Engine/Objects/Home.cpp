#include "Home.hpp"

using namespace objects;

Home::Home()
{
	upgradePoints = 0;
}


Home::~Home()
{
}


void Home::initialize(ResourceManager* resources)
{
	MenuElement* doneButton;
	doneButton = new BasicButton(sf::Vector2f(800, 800), resources->getResourceGroupByName("HomeOKButton"), "Done", sf::Color::Black, sf::Vector2f(100, 100), 10, 10);
	
	MenuElement* background;
	background = new MenuSprite(resources->getTexturePointerByName("HomeMenuBackground"), sf::Vector2f(0, 0), sf::Vector2f(1000, 1000));

	Menu upgradeMenu;

	upgradeMenu.addMenuElement(background, "Background");
	upgradeMenu.addMenuElement(doneButton, "DoneButton");
	
	this->addMenu(upgradeMenu, "UpgradeMenu", sf::Vector2f(0,0));

	boost::function<void()> boundFxn = boost::bind(&Home::closeUpgradeMenu, this);
	setButtonCallback("UpgradeMenu", "DoneButton", boundFxn, 12);
}



void Home::setUpgradePoints(const int& up)
{
	upgradePoints = up;
}

void Home::closeUpgradeMenu()
{
	this->getMenuPtr("UpgradeMenu")->deactivate();
}

void Home::setButtonCallback(const std::string& menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonState)
{
	Menu* menu = this->getMenuPtr(menuName);
	BasicButton* but = static_cast<BasicButton*>(menu->getPointerToElementByName(buttonName).get());
	but->addFunctionOnButtonState(fxn, buttonState);
}