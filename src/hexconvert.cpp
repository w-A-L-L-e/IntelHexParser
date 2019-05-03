#include "../include/IntelHexFile.h"

#include <iostream>
#include <assert.h>

using namespace std;

void usage(string name);


//todo make this cmd line arg!
#define PAGE_SIZE 16

int main(int argc, char* argv[])
{
  bool programOutput = false;
	if(argc < 2)
	{
		usage(argv[0]);
		return 1;
	}

	/*
	 * Parse file
	 */
	IntelHexFile file(argv[1]);
	cout << "File: " << file << endl;

	/*
	 * Get the program
	 */
	Program program = file.getProgram();	

  if( programOutput ){
	  cout << "Program: " << program << endl;
  }

	/*
	 * Get the program in a vector of pages
	 */
	vector<ProgramPage> programPages = program.getPages(PAGE_SIZE);

	for(vector<ProgramPage>::iterator it = programPages.begin(); it != programPages.end(); ++it)
	{
		ProgramPage page = (*it);
		cout << page << endl;
	}

	return 0;
}

void usage(string name)
{
	cout << name << ": [*.hex]" << endl;
}
