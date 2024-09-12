#include <iostream>
#include <fstream>
#include <string>

// It is a very simple utility to convert binary dump of unsigned 
// short values to CSV format for further statistical manipulations.
// Expand it if you need other types or formats.

int main(int argc, char * argv[])
{
  using namespace std;

  if (argc < 2)
  {
    cout << "Usage: bintocsv <input file> [<output file>]" << endl;
    return 1;
  }

  std::ifstream fIn(argv[1], ios::in | ios::binary);
  if (!fIn)
  {
    cout << "Failed to open input file: " << argv[1] << endl;
    exit(1);
  }

  std::string outputFile;
  if (argc == 2)
  {
    outputFile = argv[1];
    outputFile.append(".csv");
  }
  else
  {
    outputFile = argv[2];
  }

  std::ofstream fOut(outputFile.c_str());
  if (!fOut)
  {
    cout << "Failed to open output file: " << outputFile << endl;
    exit(1);
  }

  fOut << "Step number;Step lenght" << endl;

  int stepNumber;
  fIn.read(reinterpret_cast<char*>(&stepNumber), sizeof(stepNumber));

  while (!fIn.eof())
  {
    unsigned short stepLenght;
    fIn.read(reinterpret_cast<char*>(&stepLenght), sizeof(stepLenght));
    fOut << stepNumber << ";" << stepLenght << endl;
    ++stepNumber;
  }

  return 0;
}