#include <Program.h>
#include <iomanip>
#include <iostream>

Program::Program(const map<uint16_t, IntelHexFileEntry>& addressToFileEntries)
{
	size_t hAddress = ((addressToFileEntries.rbegin())->second).getEndAddress();
	data.resize(hAddress);

  //initialize entire firmware data block to FF
  for(int i=0;i<data.size();i++){
    data[i]=0xff;
  }

	for(map<uint16_t, IntelHexFileEntry>::const_iterator it = addressToFileEntries.begin(); it != addressToFileEntries.end(); ++it)
	{
		size_t address = (size_t)it->first;
		IntelHexFileEntry entry = it->second;
		vector<uint8_t> entryData = entry.getData();
   
    /*
    cout<<"entrydata on address"<<address<<"=";
    for(int i=0;i<entryData.size();i++){
      cout << hex << setw(2)<< (int)entryData[i] << " ";
    }
    cout<<endl<<endl;
    when for instance data is offset to 70 00 we see it on first data entry

    entrydata on address0= 0  0 70  0 

    but real data is here:
    entrydata on address7000=55 c0  0  0 6e c0  0  0 6c c0  0  0 6a c0  0  0 

    */

		for(size_t i = 0; i < entryData.size(); i++)
		{
			uint8_t v = entryData[i];
			data[address + i] = v;
		}
	}
}

Program::~Program()
{
}

vector<ProgramPage> Program::getPages(size_t pageSize)
{
	vector<ProgramPage> pages;

	for(size_t i = 0; i < data.size(); i+= pageSize)
	{
		size_t pageEndAddress = min(i + pageSize, data.size());

		vector<uint8_t> pageData(data.begin() +i, data.begin() + pageEndAddress);
		ProgramPage p(i, pageSize, pageData);
		pages.push_back(p);
	}

	return pages;
}

ostream& operator<<(ostream& os, const Program& rhs)
{
	os << "[Num Bytes: " << rhs.data.size() << ", Data: ";
	
	for(vector<uint8_t>::const_iterator it = rhs.data.begin(); it != rhs.data.end(); ++it)
	{
		uint8_t v = (*it);
		os << hex << setfill('0') << setw(2) << (size_t)v;
	}

	os << dec << "]";
  return os;
}

