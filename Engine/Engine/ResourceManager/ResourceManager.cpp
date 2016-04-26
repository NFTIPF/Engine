#include "ResourceManager.hpp"



ResourceManager::ResourceManager()						//Constructor
{
	setVectorSize(4);									//set the vector of name maps to 4: Textures, Fonts, SoundBuffers, ResourceGroups
	textureVector.resize(100);
	fontVector.resize(100);
	soundBufferVector.resize(10);

	resourceManagerLogger = logger::getSLogger();		//setup the logger
}

ResourceManager::~ResourceManager()						//destructor
{

}



void ResourceManager::loadFileTree(const std::string& directory)
{
	std::vector<const std::string> files;			//make a vector of files
	fillFileNameVectorFromTree(directory, files);	//fill it

	if (!files.size())
	{
		BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "Tree " << directory << " did not produce any files";
		//Log a warning if files is empty
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG_SEV(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			loadFile(files[i], getFileName(files[i]));

			//otherwise, add the file and give a debug message
		}
	}

}

void ResourceManager::loadFileTree(const std::string& directory, const std::string& ext)
{

	bool extensionFound = false;
	std::vector<const std::string> files;
	fillFileNameVectorFromTree(directory, files);

	if (!files.size())
	{
		BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "Tree " << directory << " did not produce any files.";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			if ((getExtension(files[i]) == ext) || (("." + getExtension(files[i])) == ext))
				//treats "png" and ".png" as the extension the same
			{
				BOOST_LOG_SEV(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
				loadFile(files[i], getFileName(files[i]));

				extensionFound = true;
				//if the extension matched, add the file
			}
		}

		if (!extensionFound)
		{
			BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "No files with extension " << ext << " was found in directory tree " << directory;
			//if no files with that extension were found in the tree, logs a warning message
		}
	}
}

void ResourceManager::loadFileDirectory(const std::string& directory)
{
	std::vector<const std::string> files;				//make a vector of filenames
	fillFileNameVectorFromDirectory(directory, files);	//fill it

	if (!files.size())
	{
		BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files; maybe should have been a load from tree?";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG_SEV(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";

			loadFile(files[i], getFileName(files[i]));

			//add the files
		}
	}
}

void ResourceManager::loadFileDirectory(const std::string& directory, const std::string& ext)
{
	bool extensionFound = false;
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);

	if (!files.size())
	{
		BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files.";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			if ((getExtension(files[i]) == ext) || (("." + getExtension(files[i])) == ext))
				//treats "png" and ".png" the same
			{
				BOOST_LOG_SEV(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
				loadFile(files[i], getFileName(files[i]));
				extensionFound = true;
				//if the extension matches, add the file
			}
		}

		if (!extensionFound)
		{
			BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "No files with extension " << ext << " was found in directory " << directory;
			//give a warning if no files with that extension was found in the directory
		}
	}
}

void ResourceManager::addFilesResourceGroupFromDirectory(const std::string& directory)
{
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);


	if (!files.size())
	{
		BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files; maybe should have been a load from tree?";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG_SEV(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			loadFile(files[i], getFileName(files[i]));

		}
	}

	std::string directoryName = getDirectoryName(directory);
	addEmptyResourceGroup(directoryName);				//make an empty resourceGroup with the name of the directory

	for (unsigned int i = 0; i < files.size(); i++)
	{
		addResourcetoResourceGroup(directoryName, getFileName(files[i]), getExtension(files[i]), getFileName(files[i]));
		//add the files to the resourceGroup
	}

}

void ResourceManager::addFilesResourceGroupFromDirectory(const std::string& directory, const std::string& RGName)
{
	std::vector<const std::string> files;
	fillFileNameVectorFromDirectory(directory, files);

	if (!files.size())
	{
		BOOST_LOG_SEV(resourceManagerLogger, WARNING) << "Directory " << directory << " did not produce any files; maybe should have been a load from tree?";
	}
	else
	{
		for (unsigned int i = 0; i < files.size(); i++)
		{
			BOOST_LOG_SEV(resourceManagerLogger, DEBUG) << "Adding File: " << getFileName(files[i]) << " (" << files[i] << ")";
			loadFile(files[i], getFileName(files[i]));	//files i is a directory path
		}
	}


	addEmptyResourceGroup(RGName);						//make a new empty resourceGroup with the specified name

	for (unsigned int i = 0; i < files.size(); i++)
	{
		addResourcetoResourceGroup(RGName, getFileName(files[i]), getExtension(files[i]), getFileName(files[i]));
		//add the files	
	}

}



void ResourceManager::loadFile(const std::string& fileName, const std::string& name)
{
	std::string ext = getExtension(fileName);						//get the extension

	if (ext == "ttf")												//.ttf is a font
	{
		addFont(fileName);											//add the font

		addName(name, Font_Names, fontVector.size() - 1);			//add the name
	}
	else if (ext == "png" ||
		ext == "jpg" ||
		ext == "jpeg" ||
		ext == "bmp")										//these extensions are textures
	{
		addTexture(fileName);										//add the texture

		addName(name, Texture_Names, textureVector.size() - 1);		//add the name
	}
	else if (ext == "wav" ||
		ext == "aif" ||
		ext == "mp3" ||
		ext == "mp2" ||
		ext == "ogg" ||
		ext == "raw")										//these are soundBuffers
	{
		addSoundBuffer(fileName);

		addName(name, SoundBuffer_Names);
	}

	else
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << "Could not load file with extension " << ext << " extension type not supported";
	}

}

sf::Texture* ResourceManager::getTexturePointerByIndex(const int& index)
{
	return &(textureVector[index]);
}

sf::Texture* ResourceManager::getTexturePointerByName(const std::string& name)
{

	return &textureVector[ntoi(name, Texture_Names)];				//return the texture with the desired name  

}

sf::Font* ResourceManager::getFontPointerByName(const std::string& name)
{

	return &fontVector[ntoi(name, Font_Names)];					//return the desired font

}

sf::SoundBuffer* ResourceManager::getSoundBufferPointerByName(const std::string& name)
{

	return &soundBufferVector[ntoi(name, SoundBuffer_Names)];		//set it to the font with the desired name

}



void ResourceManager::addEmptyResourceGroup(const std::string& name)		//adds an empty resourceGroup and give it a name
{
	ResourceGroup empt;														//make an empty resource group

	resourceGroups.push_back(empt);											//add it

	addName(name, ResourceGroup_Names, resourceGroups.size() - 1);			//add the name
}

void ResourceManager::addResourceGroup(ResourceGroup fResourceGroup, const std::string& name)
//adds an already created resourceGroup and name it
{

	resourceGroups.push_back(fResourceGroup);								//add the resourceGroup

	addName(name, ResourceGroup_Names, resourceGroups.size() - 1);			//add the name

}



void ResourceManager::addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, const std::string& ext)
{
	addResourcetoResourceGroup(rsName, fileName, ext, "NO_NAME");			//adds the resource without any name
}

void ResourceManager::addResourcetoResourceGroup(const std::string& rsName, const std::string& fileName, std::string ext, const std::string& desName)
{
	bool nodesname = (desName == "NO_NAME");	//if the name was "NO_NAME" we dont add the name

	if (ext[0] == '.')
	{
		ext.erase(0, 1);						//kills the dot if passed by accident
	}


	if (ext == "ttf")							//interprets the extension...
	{
		if (nodesname)
		{
			addFonttoResourceGroup(rsName, fileName);
			//if there was no name, add it without a name
		}
		else
		{
			addFonttoResourceGroup(rsName, fileName, desName);
		}
	}
	else if (ext == "png" ||
		ext == "jpg" ||
		ext == "jpeg" ||
		ext == "bmp")
	{
		if (nodesname)
		{
			addTexturetoResourceGroup(rsName, fileName);
		}
		else
		{
			addTexturetoResourceGroup(rsName, fileName, desName);
		}
	}
	else if (ext == "wav" ||
		ext == "aif" ||
		ext == "mp3" ||
		ext == "mp2" ||
		ext == "ogg" ||
		ext == "raw")
	{
		if (nodesname)
		{
			addSoundBuffertoResourceGroup(rsName, fileName);
		}
		else
		{
			addSoundBuffertoResourceGroup(rsName, fileName, desName);
		}
	}
	else
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << "Could not add file to resource group \"" << ext << "\"extension type not supported";
	}
}

void ResourceManager::addTexturetoResourceGroup(const std::string& rsName, const std::string& texName)	//adds a Texture to a ResourceGroup by name
{

	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName));
	//literally just add the texture without a name
}

void ResourceManager::addTexturetoResourceGroup(const std::string& rsName, const std::string& texName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addTexture(getTexturePointerByName(texName), desName);
	//add the texture with the name
}

void ResourceManager::addFonttoResourceGroup(const std::string& rsName, const std::string& fontName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName));
}

void ResourceManager::addFonttoResourceGroup(const std::string& rsName, const std::string& fontName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addFont(getFontPointerByName(fontName), desName);
}

void ResourceManager::addSoundBuffertoResourceGroup(const std::string& rsName, const std::string& sbName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuffer(getSoundBufferPointerByName(sbName));
}

void ResourceManager::addSoundBuffertoResourceGroup(const std::string& rsName, const std::string& sbName, const std::string& desName)
{
	resourceGroups[ntoi(rsName, ResourceGroup_Names)].addSoundBuffer(getSoundBufferPointerByName(sbName), desName);
}



ResourceGroup* ResourceManager::getResourceGroupByName(const std::string& name)
{

	return &resourceGroups[ntoi(name, ResourceGroup_Names)];	//returns the resource set with the desired name

}

//----------------------------------------------------------------------------------------------------------------------------***************************
//-----------------------------------------PRIVATE----------------------------------------------------------------------------***************************
//----------------------------------------------------------------------------------------------------------------------------***************************

std::string ResourceManager::getExtension(const std::string& fpath)			//returns the extension of a file
{
	std::vector<std::string> returned = util::splitStrAtSubstr(fpath, ".");		//split string at "." and return the last string in the split vector
	return returned[returned.size() - 1];
}

std::string ResourceManager::getFileName(const std::string& fpath)
{
	std::vector<std::string> fileName = util::splitStrAtSubstr(fpath, "\\");
	std::vector<std::string> returned = util::splitStrAtSubstr(fileName[fileName.size() - 1], ".");
	return returned[0];
}

std::string ResourceManager::getDirectoryName(const std::string& fpath)		//kind of same as getFileName -- just assumes no extension
{
	std::vector<std::string> returned = util::splitStrAtSubstr(fpath, "\\");		//splits at slashes
	return returned[returned.size() - 1];
}



void ResourceManager::fillFileNameVectorFromTree(const std::string& directory, std::vector<const std::string>& namevec)
{

	boost::filesystem::path dir(directory);												//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))			//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);								//go through the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))
			{
				namevec.push_back(directory + "\\" + it->path().filename().string());						//if a file is a regular file, add it to files
			}
			else if (boost::filesystem::is_directory(it->status()))
			{
				fillFileNameVectorFromTree(directory + "\\" + it->path().filename().string(), namevec);		//if a "file" is actually a folder, recurse
				//using that folder as the directory
			}

		}

	}
	else
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistant";
	}
}

void ResourceManager::fillFileNameVectorFromDirectory(const std::string& directory, std::vector<const std::string>& namevec)
{

	boost::filesystem::path dir(directory);												//make a new path of the directory

	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))			//if the directory is valid
	{
		for (boost::filesystem::directory_iterator it(dir);								//go throught the directory
			it != boost::filesystem::directory_iterator(); ++it)
		{

			if (boost::filesystem::is_regular_file(it->status()))
			{
				namevec.push_back(directory + "\\" + it->path().filename().string());	//if a file is a regular file, add it to files
			}

		}

	}
	else
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << "Directory " << dir << " is either not a directory or nonexistent";
	}

}



void ResourceManager::addTexture(const std::string& fileName)
{
	sf::Texture texture;										//make a temporary texture

	if (!texture.loadFromFile(fileName))						//try to make it load from the file
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << fileName << " (Texture) failed to load.";
		// if it doesn't, there is an error
	}
	else
	{
		BOOST_LOG_SEV(resourceManagerLogger, INFO) << fileName << " (Texture) successfully added.";
	}

	textureVector.push_back(texture);							//add the texture

}

void ResourceManager::addFont(const std::string& fileName)
{
	sf::Font font;

	if (!font.loadFromFile(fileName))
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << fileName << " (Font) failed to load.";

	}
	else
	{
		fontVector.push_back(font);
		BOOST_LOG_SEV(resourceManagerLogger, INFO) << fileName << "(Font) successfully added.";
	}


}

void ResourceManager::addSoundBuffer(const std::string& fileName)
{

	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(fileName))
	{
		BOOST_LOG_SEV(resourceManagerLogger, ERROR) << fileName << " (SoundBuffer) failed to load.";
	}
	else
	{
		BOOST_LOG_SEV(resourceManagerLogger, INFO) << fileName << " (SoundBuffer) successfully added";
	}
	soundBufferVector.push_back(buffer);

}