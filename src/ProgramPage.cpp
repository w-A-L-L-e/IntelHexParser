#include <ProgramPage.h>
#include <iomanip>
#include <iostream>

ProgramPage::ProgramPage(size_t address, size_t pageSize, const vector<uint8_t>& pageData)
{
	this->address = address;
	this->pageSize = pageSize;
	data.resize(pageData.size());
 
  this->verbose=false;
	
	size_t startAddress = address % pageSize;

	for(size_t i = startAddress; i < (startAddress + pageData.size()); i++)
	{
		data[i] = pageData[i - startAddress];
	}
}

ProgramPage::~ProgramPage()
{
}

size_t ProgramPage::getAddress()
{
	return address;
}

size_t ProgramPage::getSize()
{
	return data.size();
}

size_t ProgramPage::getPageSize()
{
	return pageSize;
}

size_t ProgramPage::getEndAddress()
{
	return address + data.size();
}

vector<uint8_t> ProgramPage::getData()
{
	return data;
}

/*
A record's checksum byte is the two's complement (negative) of the least significant byte (LSB) of the sum of all decoded byte values in the record preceding the checksum. It is computed by summing the decoded byte values and extracting the LSB of the sum (i.e., the data checksum), and then calculating the two's complement of the LSB (e.g., by inverting its bits and adding one).

For example, in the case of the record :0300300002337A1E, the sum of the decoded byte values is 03 + 00 + 30 + 00 + 02 + 33 + 7A = E2. The two's complement of E2 is 1E, which is the checksum byte appearing at the end of the record.

TODO: fix this after work tonight ... used a shortcut instead o fthis method below that seems to work for now...
*/  
int ProgramPage::getChecksum(uint8_t dataByteSum ) const
{
  uint8_t record_type = 0x00; //todo this->type
  uint8_t checksum = data.size()+address+record_type;
  checksum+=dataByteSum;

  // 2s complement shortcut
  uint8_t result = -(unsigned int) checksum;
  cout << "  checksum = "<<(int)checksum<<" complement="<<(int)result<<" result we want should be E1 : "<<flush;

  return result;
}

ostream& operator<<(ostream& os, const ProgramPage& rhs)
{
  string delim="";
  uint8_t dataSum = 0;
  if(rhs.verbose){
    os << "Page: [Start Address: 0x" << hex << rhs.address;
    os << ", End Address: 0x" << hex << (rhs.address+rhs.data.size());
    os << ", Size: " << rhs.data.size();
    os << ", Page Size: " << dec << rhs.pageSize;
    os << ", Data: ";
  }
  else{
    os<< ":"<<uppercase;
    os<< delim << hex << setfill('0') << setw(2) << rhs.data.size();
    dataSum+=rhs.data.size();
    os<< delim << hex << setfill('0') << setw(4) << rhs.address;
    //dataSum+=rhs.address;
    dataSum+=(uint8_t)(rhs.address>>8); //first high byte
    dataSum+=(uint8_t)((rhs.address<<24)>>24); //low byte
	
    os<< delim << hex << setfill('0') << setw(2) << 0; //rhs.type, right now always do type 00
    dataSum+=0;
    os<< delim;
  }

	for(vector<uint8_t>::const_iterator it = rhs.data.begin(); it != rhs.data.end(); ++it)
	{
		uint8_t v = *it;
    dataSum+=v;
		os << hex << setfill('0') << setw(2) << (size_t)v;
	} 

	if(rhs.verbose){
    os << dec << "]";
  }
  else{
    //shortcut for 2s complement
    uint8_t checksum = (((int)(-dataSum)<<24)>>24) ;
    os << delim << hex << setfill('0') << setw(2) << (int)checksum;   ///(int)-dataSum ;//rhs.getChecksum(dataSum); 
  }

  return os;
}

