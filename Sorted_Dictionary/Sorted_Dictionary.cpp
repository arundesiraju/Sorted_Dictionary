// Sorted_Disctionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// Read the passage
	FILE *fp;
	fopen_s(&fp, "passage.txt", "r");

	map<string, int> dictionary;

	if(fp != NULL)
	{
		string token;
		char *nextToken = NULL;
		char buffer[4096] = {'\0'};

		// Store contents in buffer
		fread((void*)buffer, 4096, 1, fp);
		
		while (true)
		{
			// Read word by word separated by space
			token = strtok_s(buffer, " ", &nextToken);

			if (dictionary.find(buffer) == dictionary.end())
			{
				// If it doesn't exist in dictionary, add it with count = 1
				dictionary.insert(pair<string, int>(buffer, 1)); 
			}
			else
			{
				// If it exists in dictionary, keep a backup of the count, then erase the entry, and re-add it with the count incremented
				int count = dictionary.find(buffer)->second;
				dictionary.erase(buffer);

				count++;
				dictionary.insert(pair<string, int>(buffer, count)); 
			}	

			// break when the last word is read
			if(!strcmp(nextToken, ""))
				break;

			//Copy nextToken into buffer
			sprintf_s(buffer, 4096, "%s", nextToken);
		}

		fclose(fp);
	}

	// Sort the map here by ascending order
	// Flip existing map to sort automatically
	multimap<int, string> sorted_dictionary_asc;
	for (map<string, int>::iterator iter = dictionary.begin(); iter!=dictionary.end(); iter++)
	{
		sorted_dictionary_asc.insert(pair<int, string>(iter->second, iter->first));
	}

	// Sort the map here by descending order
	multimap<int, string, greater<int>> sorted_dictionary_desc;	
	for (map<int, string>::iterator iter = sorted_dictionary_asc.begin(); iter!=sorted_dictionary_asc.end(); iter++)
	{
		sorted_dictionary_desc.insert(pair<int, string>(iter->first, iter->second));
	}

	return 0;
}






