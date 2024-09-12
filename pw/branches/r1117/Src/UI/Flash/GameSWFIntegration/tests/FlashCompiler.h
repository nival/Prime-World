#pragma once

//NOTE that this class only call compiler
class FlashCompiler
{
public:
  //returns path to the compiled abc file. or null in case of any errors
  static nstl::string CompileActionFile (const char * actionFile);
};