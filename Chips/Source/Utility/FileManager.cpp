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
}

FileManager::~FileManager()
{
}

StringArray FileManager::getPresets()
{

	Array<File> files = File::getSpecialLocation(File::SpecialLocationType::commonDocumentsDirectory).findChildFiles(File::TypesOfFileToFind::findFiles, false, "*.chp");
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
	File newPresetFile(File::getSpecialLocation(File::SpecialLocationType::commonDocumentsDirectory).getFullPathName() + "\\" + presetName + ".chp");
	FileOutputStream fos(newPresetFile);
	fos.write(memoryBlock.getData(), memoryBlock.getSize());
}

void FileManager::loadPresetFile(String presetName, MemoryBlock& memoryBlock)
{
	 File presetFile(File::getSpecialLocation(File::SpecialLocationType::commonDocumentsDirectory).getFullPathName() + "\\" + presetName + ".chp");
	 FileInputStream fis(presetFile);
	 fis.read(memoryBlock.getData(), memoryBlock.getSize());
}
