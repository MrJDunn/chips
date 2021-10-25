/*
  ==============================================================================

    FileManager.h
    Created: 24 Oct 2021 11:37:40am
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FileManager
{
public:
	FileManager();
	~FileManager();

	StringArray getPresets();
	void loadPresetFile(String presetName, MemoryBlock& memoryBlock);
	void savePresetFile(String presetName, MemoryBlock& memoryBlock);

private:
};
