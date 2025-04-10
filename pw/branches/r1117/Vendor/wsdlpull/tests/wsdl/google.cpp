#include <wsdlparser/WsdlInvoker.h>

 //This example demonstrates how to use the Google search web service using wsdlpull
 //
int
main(int argc, char** argv) {

  WsdlPull::WsdlInvoker invoker;
  std::string name;


   invoker.setWSDLUri("GoogleSearch.wsdl");
   //set the operation
   invoker.setOperation("doGoogleSearch");
   //set the parameters
   invoker.setInputValue(0, "uWAU8ddQFHJVD/rZKNIBm4hJmmloQP4W");
   invoker.setInputValue(1, "wsdlpull");
   invoker.setInputValue(2, "0");
   invoker.setInputValue(3, "1");
   invoker.setInputValue(4, "0");
   invoker.setInputValue(5, "1");
   invoker.setInputValue(6, "1");
   invoker.setInputValue(7, "1");
   invoker.setInputValue(8, "utf-8");
   invoker.setInputValue(9, "utf-8");

   invoker.invoke();
   
   //this is the short form , quick access way to get elements from the web service response
   int start = invoker.getValue<int>("startIndex");
   int endIndex = invoker.getValue<int>("endIndex");
   
   
   Schema::TypeContainer* tc = 0;


    invoker.getNextOutput(name, tc);

  std::cerr << "Output : " << name << std::endl;
  // tc->print(std::cerr);
  Schema::Type type;
  double* t = (double *)tc->getValue("searchTime", type);
  std::cerr << "*** Time : " << *t << std::endl;
  tc->rewind();
  Schema::TypeContainer *res;

  res = tc->getChildContainer("resultElements");

 std::cerr << "*** New container" << std::endl;
 if (res)
   res->print(std::cerr);
 else
   std::cerr << "*** No such container !" << std::endl;

  return 0;
 }
