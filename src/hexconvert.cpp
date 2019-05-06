#include "../include/IntelHexFile.h"

#include <iostream>
#include <assert.h>

using namespace std;

void usage(string name);


//todo make this cmd line arg!
//#define PAGE_SIZE 16  
//juana:    32562 0x7F32
//leonardo: 32730 0x7FDA
#define PAGE_SIZE 32

int main(int argc, char* argv[])
{
  bool verbose = false;
	if(argc < 2)
	{
		usage(argv[0]);
		return 1;
	}

	/*
	 * Parse file
	 */
	IntelHexFile file(argv[1]);
  if(verbose)
	cout << "File: " << file << endl;

	/*
	 * Get the program
	 */
	Program program = file.getProgram();	

  if( verbose ){
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

  //patch for file (this is hackity style basically the
  //end of a firmware hex file ends with 2 special lines
  //the Start segment address and the end-of-file record
  //example:
  // :107F1C000008412336000100020100014A55414E80
  // :067F2C0049544120000051
  // :040000030000700089   -> this is the segment address record -> we can ignore this actually it basically states our bootloader starts at 0x7000 
  //                          the effect of our patch is that this now actually writes 7000 on adress 0000 (the first record) but we're not going to bother
  //                          with fixing this (to be proper we should implement the record type for all 5 types described here https://en.wikipedia.org/wiki/Intel_HEX
  // :00000001FF   -> this is the end of file marker always to be inserted, again as this is treated as a normal record this will write some 000 on first line
  // but we don't care about that as we will replace that first line with the inital 'core sketch' the program that runs from 0x0000 up to max 0x7000
  
  // we do need to have such an end-of-file marker though. so we just append that here
  cout << ":00000001FF" << endl; // end of file marker which is the same for all hex files

	return 0;
}

void usage(string name)
{
	cout << name << ": [*.hex]" << endl;
}
