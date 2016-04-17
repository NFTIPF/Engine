#include "EditorGUI.hpp"

EditorGUI::EditorGUI()
{
	popData = false;
}

EditorGUI::~EditorGUI()
{

}

void EditorGUI::initialize(ResourceManager* resources)
{
	recMan = resources;	//set local resource manager


	MenuElement* selectedLayer;	//entry table
	selectedLayer = new EntryTable(25, 50, 20, sf::Vector2f(1200, 50), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);
	//selectedLayer = new EntryTextBox(recMan->getFontPointerByName("EditorFont"), 5, sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(300, 150), recMan->getTexturePointerByName("EditorEntryBar"), sf::Vector2f(100, 200), 20);

	MenuElement* selectedObject;	//entry table
	selectedObject = new EntryTable(25, 50, 20, sf::Vector2f(1500, 50), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);

	MenuElement* selectedResource;	//entry table
	selectedResource = new EntryTable(25, 50, 20, sf::Vector2f(50, 400), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);

	MenuElement* attributeEditor;	//entry table
	attributeEditor = new EntryTable(50, 75, 20, sf::Vector2f(1400, 250), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(200, 50), recMan->getTexturePointerByName("EditorEntryBar"), 40);

	MenuElement* updateButton;
	updateButton = new BasicButton(sf::Vector2f(1450, 800), recMan->getResourceGroupByName("EditorButton"), "Update Selection", sf::Color::Black, sf::Vector2f(100, 100), 10, 10);

	MenuElement* newObject;	//button
	newObject = new BasicButton(sf::Vector2f(1750, 800), recMan->getResourceGroupByName("EditorButton"), "New Object", sf::Color::Black, sf::Vector2f(100, 100), 12, 10);

	MenuElement* newResource;	//button
	newResource = new BasicButton(sf::Vector2f(1300, 800), recMan->getResourceGroupByName("EditorButton"), "New Resource", sf::Color::Black, sf::Vector2f(100, 100), 12, 10);

	MenuElement* removeButton;
	removeButton = new BasicButton(sf::Vector2f(1150, 800), recMan->getResourceGroupByName("EditorButton"), "Remove Object", sf::Color::Black, sf::Vector2f(100, 100), 10, 10);

	MenuElement* save;	//button
	save = new BasicButton(sf::Vector2f(1600, 800), recMan->getResourceGroupByName("EditorButton"), "Save", sf::Color::Black, sf::Vector2f(100, 100), 14, 10);

	MenuElement* selectLayer;	//button
	selectLayer = new BasicButton(sf::Vector2f(1600, 150), recMan->getResourceGroupByName("EditorButton"), "selectL", sf::Color::Black, sf::Vector2f(150, 75), 14, 10);

	MenuElement* selectObject;	//button
	selectObject = new BasicButton(sf::Vector2f(1300, 150), recMan->getResourceGroupByName("EditorButton"), "selectO", sf::Color::Black, sf::Vector2f(150, 75), 14, 10);


	Menu editorMenu;

	editorMenu.addMenuElement(selectedLayer, "selectedLayer");
	editorMenu.addMenuElement(selectedObject, "selectedObject");
	editorMenu.addMenuElement(selectedResource, "selectedResource");
	editorMenu.addMenuElement(attributeEditor, "attributeEditor");
	editorMenu.addMenuElement(updateButton, "updateButton");
	editorMenu.addMenuElement(newObject, "newObject");
	editorMenu.addMenuElement(newResource, "newResource");
	editorMenu.addMenuElement(selectLayer, "selectLayer");
	editorMenu.addMenuElement(selectObject, "selectObject");
	editorMenu.addMenuElement(removeButton, "removeButton");
	editorMenu.addMenuElement(save, "save");
	
	MenuElement* input;
	input = new EntryTable(50, 50, 20, sf::Vector2f(0, 0), recMan->getFontPointerByName("EditorFont"), sf::Color::Black, recMan->getTexturePointerByName("EditorEntryBG"), sf::Vector2f(150, 75), recMan->getTexturePointerByName("EditorEntryBar"), 20);

	MenuElement* okButton;
	okButton = new BasicButton(sf::Vector2f(0, 100), recMan->getResourceGroupByName("EditorButton"), "OK", sf::Color::Black, sf::Vector2f(100, 100), 10, 10);

	MenuElement* cancelButton;
	cancelButton = new BasicButton(sf::Vector2f(200, 100), recMan->getResourceGroupByName("EditorButton"), "CANCEL", sf::Color::Black, sf::Vector2f(100, 100), 10, 10);

	Menu popup;

	popup.addMenuElement(input, "input");
	popup.addMenuElement(okButton, "okButton");
	popup.addMenuElement(cancelButton, "cancelButton");

	this->addMenu(editorMenu, "editorMenu", sf::Vector2f(0, 0));
	this->addMenu(popup, "popup", sf::Vector2f(950, 540));

	this->getMenuPtr("popup")->deactivate();

	boost::function<void()> boundFxn = boost::bind(&EditorGUI::popup_OK, this);
	setButtonCallback("popup", "okButton", boundFxn, 12);

	boundFxn = boost::bind(&EditorGUI::popup_CANCEL, this);
	setButtonCallback("popup", "cancelButton", boundFxn, 12);

}

void EditorGUI::popup(std::map<std::string, std::string>& input)
{
	Menu* popup = this->getMenuPtr("popup");
	popup->activate();
	setMap("popup", "input", input, 1);
}

void EditorGUI::popdown(bool which)
{
	this->getMenuPtr("popup")->deactivate();
	popData = which;
}

void EditorGUI::setMap(const std::string& menuName, const std::string& tableName, std::map<std::string, std::string>& newAttributes, const unsigned int& dispAmt)
{
	Menu* editor = this->getMenuPtr(menuName);
	EntryTable* attributes = static_cast<EntryTable*>(editor->getPointerToElementByName(tableName).get());
	attributes->setMap(newAttributes, dispAmt);
}

void EditorGUI::setButtonCallback(const std::string menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonState)
{
	Menu* menu = this->getMenuPtr(menuName);
	BasicButton* but = static_cast<BasicButton*>(menu->getPointerToElementByName(buttonName).get());
	but->addFunctionOnButtonState(fxn, buttonState);
}

bool EditorGUI::getPopData()
{
	return popData;
}

void EditorGUI::setPopData(const bool& newData)
{
	popData = newData;
}

//PRIVATE FUNCTIONS

void EditorGUI::popup_OK()
{
	popdown(1);
}

void EditorGUI::popup_CANCEL()
{
	popdown(0);
}

