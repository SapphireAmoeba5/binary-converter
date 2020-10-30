#pragma once
#include <string>
#include "wx/wx.h"
#include <vector>
#include <lmcons.h>

bool find(int find, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (find == arr[i])
		{
			return true;
		}
	}
	return false;
}

std::string ConvertToBinary(std::string input, bool addSpaces)
{
	const int pwrsTwoSize = 8;
	int pwrsTwo[pwrsTwoSize] = { 128, 64, 32, 16, 8, 4, 2, 1 };

	int secondNum;

	std::string ConvertedText = "";
	std::vector<int> foundPowers;

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') { ConvertedText += "00100000"; }

		else
		{
			for (int y = 0; y < pwrsTwoSize; y++)
			{
				if (pwrsTwo[y] <= input[i])
				{
					foundPowers.push_back(pwrsTwo[y]);
					secondNum = input[i] - pwrsTwo[y];
					break;
				}
			}
			if (find(secondNum, pwrsTwo, pwrsTwoSize))
			{
				foundPowers.push_back(secondNum);
			}
			else
			{
				if (secondNum != 0)
				{
					bool foundAll = false;

					while (!foundAll)
					{
						for (int i = 0; i < pwrsTwoSize; i++)
						{
							if (pwrsTwo[i] <= secondNum)
							{
								foundPowers.push_back(pwrsTwo[i]);
								secondNum = secondNum - pwrsTwo[i];
								break;
							}
						}
						if (find(secondNum, pwrsTwo, pwrsTwoSize))
						{
							foundPowers.push_back(secondNum);
							foundAll = true;
						}
					}
				}
			}

			int index = 0;
			for (int y = 0; y < 8; y++)
			{
				if (index != foundPowers.size() && foundPowers[index] == pwrsTwo[y])
				{
					ConvertedText.push_back('1');
					index++;
				}
				else
				{
					ConvertedText.push_back('0');
				}
			}
			foundPowers.clear();
		}
		if (addSpaces)
		{
			ConvertedText += " ";
		}
	}

	//TEST
	/*std::string ConvertedText;
	
	for (int i = 0; i < input.size(); i++)
	{
		int c = input[i];
		for (int j = 7; j + 1 > 0; j--)
		{
			if (c >= (1 << j))
			{
				c = c - (1 << j);
				ConvertedText.push_back('1');
			}
			else
			{
				ConvertedText.push_back('0');
			}
		}
		if (addSpaces)
			ConvertedText.push_back(' ');
	}*/

	return ConvertedText;
}

std::string ConvertToAscii(std::string input)
{
	std::string formatInput = "";
	std::string convertedInput = "";

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '1' || input[i] == '0')
		{
 			formatInput.push_back(input[i]);
		}
	}

	if (formatInput.size() % 8 != 0)
	{
		while (formatInput.size() % 8 != 0)
		{
			formatInput.pop_back();
		}
	}


	int numOfBytes = formatInput.size() / 8;
	int substrLength = 8;
	for (int i = 0; i < numOfBytes; i++)
	{
		char letter = 0;
		std::string binaryInput = formatInput.substr(substrLength - 8, substrLength);
		if (binaryInput[0] == '1') 
		{ letter += 128; }
		if (binaryInput[1] == '1') 
		{ letter += 64; }
		if (binaryInput[2] == '1') 
		{ letter += 32; }
		if (binaryInput[3] == '1') 
		{ letter += 16; }
		if (binaryInput[4] == '1') 
		{ letter += 8; }
		if (binaryInput[5] == '1') 
		{ letter += 4; }
		if (binaryInput[6] == '1') 
		{ letter += 2; }
		if (binaryInput[7] == '1') 
		{ letter += 1; }
		convertedInput += letter;
		substrLength += 8;
	}
		
	
	return convertedInput;
}



std::string AsciiToCustom(std::string input)
{
	if (input.size() > 0)
	{
		input = ConvertToBinary(input, false);
		std::string ConvertedText = "";
	
		for (int i = 0; i < input.size(); i++)
		{
			if (i % 4 == 3)
			{
				int numOfOnes = 0;
				std::string pos = "";
				int loops = 0;
				for (int y = i - 3; y <= i; y++)
				{
					if (input[y] == '1') { numOfOnes++; pos += std::to_string(loops); };
					loops++;
				}
				ConvertedText += std::to_string(numOfOnes);
				ConvertedText += pos;
				ConvertedText.push_back('-');
			}
		}
		ConvertedText.pop_back();
		return ConvertedText;
	}
	else
	{
		return "";
	}
}

std::string CustomToBinary(std::string input)
{
	try
	{
		if (input.size() > 0)
		{
			if (input[input.size() - 1] == ' ' && input[(input.size() - 1) - 1] == ' ')
			{
				if (input[input.size() - 1] == ' ')
				{
					input.pop_back();
				}
				input.push_back(' ');
			}
			else if (input[input.size() - 1] != ' ') { input.push_back(' '); }
			

			std::string segmentCode = "";
			std::string convertedText = "";
			for (int i = 0; i < input.size(); i++)
			{
				if (input[i] != '-' && i != input.size() - 1)
				{
					segmentCode.push_back(input[i]);
				}
				else if (input[i] == '-' || i == input.size() - 1)
				{
					int numOfOnes = std::stoi(std::string(1, segmentCode[0]));
					std::string fourBits = "";
					int prevPos = -1;
					if (numOfOnes > 0)
					{
						for (int y = 0; y < numOfOnes; y++)
						{
							int pos = std::stoi(std::string(1, segmentCode[y + 1]));
							for (int x = prevPos + 1; x <= pos; x++)
							{
								if (x != pos)
								{
									fourBits.push_back('0');
								}
								else
								{
									fourBits.push_back('1');
								}
							}
							prevPos = pos;
						}
						if (fourBits.size() != 4)
						{
							int size = fourBits.size();
							for (int x = 0; x < 4 - size; x++)
							{
								fourBits.push_back('0');
							}
						}
						convertedText += fourBits;
						segmentCode.clear();
					}
					else
					{
						convertedText = convertedText + (fourBits += "0000");
						segmentCode.clear();
					}
				}
			}
			return convertedText;
		}
		return "";
	}
	catch (std::invalid_argument)
	{
		return "";
	}
}

std::string RetrieveUsername()
{
	std::string username = "";
	TCHAR name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(name, &username_len);

	for (int i = 0; name[i] != '\0'; i++)
	{
		username.push_back(name[i]);
	}
	return username;
}