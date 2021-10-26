/*
  ==============================================================================

    FileManager.cpp
    Created: 24 Oct 2021 11:37:40am
    Author:  Jeff

  ==============================================================================
*/

#include "FileManager.h"

FileManager::FileManager()
{
	File presetDirectory(getPresetDirectory());
	if(!presetDirectory.exists())
	{
		presetDirectory.createDirectory();
	}
}

FileManager::~FileManager()
{
}

StringArray FileManager::getPresets()
{

	Array<File> files = File(getPresetDirectory()).findChildFiles(File::TypesOfFileToFind::findFiles, false, "*.chp");
	StringArray presets;
	for(File file : files)
	{
		presets.add(file.getFileNameWithoutExtension());
	}

	// Read through a directory and find all the presets
	return presets;
}

void FileManager::savePresetFile(String presetName, MemoryBlock& memoryBlock)
{
	File newPresetFile(getPresetDirectory() + "\\" + presetName + ".chp");
	FileOutputStream fos(newPresetFile);
	fos.write(memoryBlock.getData(), memoryBlock.getSize());
}

String FileManager::getPresetDirectory()
{
	return File::getSpecialLocation(File::SpecialLocationType::commonDocumentsDirectory).getFullPathName() + "\\Chips";
}

void FileManager::loadPresetFile(String presetName, MemoryBlock& memoryBlock)
{
	 File presetFile(getPresetDirectory() + "\\" + presetName + ".chp");
	 FileInputStream fis(presetFile);
	 fis.read(memoryBlock.getData(), memoryBlock.getSize());
}
