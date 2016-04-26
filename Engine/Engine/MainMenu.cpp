#include "MainMenu.hpp"


MainMenu::MainMenu()
{

}

void MainMenu::initialize(ResourceManager* resources, const sf::Vector2f& windowSize)
{
	size = windowSize;

	recMan = resources;

	MenuElement* background;
	background = new MenuSprite(recMan->getTexturePointerByName("MenuBackground"), sf::Vector2f(size.x/2, size.y/2), sf::Vector2f(size.x, size.y));

	MenuElement* startButton;
	startButton = new BasicButton(sf::Vector2f(size.x * .37, size.y *.85), recMan->getResourceGroupByName("StartButton"), "Start", sf::Color::Black, sf::Vector2f(400, 200), 10, 10);

	MenuElement* optionsButton;
	optionsButton = new BasicButton(sf::Vector2f(size.x * .8 , size.y * .3), recMan->getResourceGroupByName("OptionsButton"), "Options", sf::Color::Black, sf::Vector2f(300, 100), 10, 10);
	
	MenuElement* quitButton;
	quitButton = new BasicButton(sf::Vector2f(size.x * .617, size.y * .5), recMan->getResourceGroupByName("QuitButton"), "Quit", sf::Color::Black, sf::Vector2f(100, 100), 10, 10);

	Menu mainMenu;

	mainMenu.addMenuElement(background, "background");
	mainMenu.addMenuElement(startButton, "startButton");
	mainMenu.addMenuElement(optionsButton, "optionsButton");
	mainMenu.addMenuElement(quitButton, "quitButton");

	mainMenu.activate();


	///////////////////////////HIGHLY UNSTABLE OPTIONS MENU BELOW//////////////////////////////////

	
	
	MenuElement* backButton;
	backButton = new BasicButton(sf::Vector2f(size.x * .5 - 500, size.y * .3 - 500), recMan->getResourceGroupByName("StartButton"), "Back", sf::Color::Black, sf::Vector2f(300, 100), 10, 10);

	MenuElement* volumeSlider;
	volumeSlider = new Slider(sf::Vector2f(size.x * .5 - 500, size.y * .5 - 500), recMan->getTexturePointerByName("SliderBackground"), recMan->getTexturePointerByName("OptionsSlider"), recMan->getFontPointerByName("MainMenuFont"), 100, 0, 50, "Volume", 30);

	MenuElement* brightnessSlider;
	brightnessSlider = new Slider(sf::Vector2f(size.x * .5 - 500, size.y * .75 - 500), recMan->getTexturePointerByName("SliderBackground"), recMan->getTexturePointerByName("OptionsSlider"), recMan->getFontPointerByName("MainMenuFont"), 100, 0, 50, "Brightness", 30);

	Menu optionsMenu;

	optionsMenu.addMenuElement(backButton, "backButton");
	optionsMenu.addMenuElement(volumeSlider, "volumeSlider");
	optionsMenu.addMenuElement(brightnessSlider, "brightnessSlider");

	optionsMenu.deactivate();
	

	

	this->addMenu(mainMenu, "mainMenu", sf::Vector2f(0, 0));
	this->addMenu(optionsMenu, "optionsMenu", sf::Vector2f(500, 500));

	/*
	boost::function<void()> boundFxn = boost::bind(&Game::unpause, this);			 //goes in game
	mainMenu.setButtonCallback("mainMenu", "startButton", boundFxn, 12);

	boundFxn = boost::bind(&Game::pause, this);
	mainMenu.setButtonCallback("pauseMenu", "pauseButton")
	*/

	boost::function<void()> boundFxn = boost::bind(&Menu::deactivate, this->getMenuPtr("mainMenu"));						 //MainMenu
	setButtonCallback("mainMenu", "optionsButton", boundFxn, 12);

	boundFxn = boost::bind(&Menu::activate, this->getMenuPtr("optionsMenu"));						 //OptionsMenu
	setButtonCallback("mainMenu", "optionsButton", boundFxn, 12);

	boundFxn = boost::bind(&Menu::deactivate, this->getMenuPtr("optionsMenu"));
	setButtonCallback("optionsMenu", "backButton", boundFxn, 12);

	boundFxn = boost::bind(&Menu::activate,	this->getMenuPtr("mainMenu"));
	setButtonCallback("optionsMenu", "backButton", boundFxn, 12);
	
	
	

}

void MainMenu::setButtonCallback(const std::string menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonState)
{
	Menu* menu = this->getMenuPtr(menuName);
	BasicButton* but = static_cast<BasicButton*>(menu->getPointerToElementByName(buttonName).get());
	but->addFunctionOnButtonState(fxn, buttonState);
}


MainMenu::~MainMenu()
{
}
