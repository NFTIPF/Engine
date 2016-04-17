#include "MenuStuff\MenuManager.hpp"
#include "Input\KeyboardData.hpp"
#include "Input\MouseData.hpp"
#include "boost\function.hpp"
#include "boost\bind.hpp"

class EditorGUI : public MenuManager
{
public:
	EditorGUI();
	~EditorGUI();

	void initialize(ResourceManager* resources);

	void popup(std::map<std::string, std::string>& input);	//activates popup prompt with given EntryTable attributes
	void popdown(bool which);										//deactivates popup with given state

	void setMap(const std::string& menuName, const std::string& tableName, std::map<std::string, std::string>& newAttributes, const unsigned int& dispAmt);	//generalized functions for setting EntryTable map input
	void setButtonCallback(const std::string menuName, const std::string& buttonName, boost::function<void()> fxn, int buttonStates);

	bool getPopData();	//returns popup data
	void setPopData(const bool& newData);

private:
	ResourceManager* recMan;

	bool popData;	//indicates wether OK or cancel was pressed when popup was done

	//callback functions for popup menu
	void popup_OK();
	void popup_CANCEL();
	void clearTable();


};