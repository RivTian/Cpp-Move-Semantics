//********************************************************
// The following code example is taken from the book
//  C++ Move Semantics - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppmove.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#include <iostream>
#include <fstream>
#include <stream>

std::ofstream openToWrite(const std::string& name)
{
  std::ofstream file(name);           // open a file to write to
  if (!file) {
    std::cerr << "can't open file '" << name << "'\n";
    std::exit(EXIT_FAILURE);
  }
  return file;                        // return ownership (open file)
}

void storeData(std::ofstream fstrm)   // takes ownership of file (but this might change)
{
  fstrm << 42 << '\n';
}                                     // closes the file

int main()
{ 
  auto outFile{openToWrite("iostream.tmp")};  // open file
  storeData(std::move(outFile));              // store data

  // better ensure that the file is closed:
  if (outFile.is_open()) {
    outFile.close();
  }
}

