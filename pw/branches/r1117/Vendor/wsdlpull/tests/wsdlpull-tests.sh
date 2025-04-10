#!/bin/bash
test()
{
 params=$*
 echo $params >>./test.log
 echo $params && wsdl -t 20  $params >>./test.log
 res=$?
 echo $res
 if [ ! $res = "0" ]   
 then
     echo "wsdl" >>./err.log
     echo  $params >>./err.log
     wsdl -t 30 -v $params >>./err.log 2>&1 
     echo "REQUEST" >>./err.log
     cat request.log >> ./err.log
     echo "RESPONSE" >>./err.log
     cat response.log >>./err.log
     echo >> err.log
     echo "--------------------------------">>./err.log
     rm -f request.log;rm -f response.log
  fi
}
type wsdl
rm -Rf err.log 
rm -Rf test.log
test  http://saintbook.org/MightyMaxims/MightyMaxims.asmx?WSDL  ForToday
test  http://greg.froh.ca/fun/random_bushism/soap/?wsdl  getRandomBushism  
test  http://api.google.com/GoogleSearch.wsdl doGoogleSearch  "****license key**** " wsdlpull 1 5 0 1 1 1 1 1 
test  http://services.aonaware.com/CountCheatService/CountCheatService.asmx?WSDL LetterSolutions hleol 
test  http://services.aonaware.com/CountCheatService/CountCheatService.asmx?WSDL LetterSolutionsMin hleol 5  
test  http://services.aonaware.com/DictService/DictService.asmx?WSDL DefineInDict wn epiphany 
test http://services.aonaware.com/DictService/DictService.asmx?WSDL Define  epiphany 
test  http://services.aonaware.com/DictService/DictService.asmx?WSDL DictionaryList 
test  http://trial.serviceobjects.com/fw/FastWeather.asmx?WSDL GetWeatherByZip 90209 fds 
test   http://www.webservicex.net/WeatherForecast.asmx?WSDL GetWeatherByPlaceName Miami 
test http://www.webservicex.net/WeatherForecast.asmx?WSDL GetWeatherByZipCode 24312 
test http://swanandmokashi.com/HomePage/WebServices/QuoteOfTheDay.asmx?WSDL GetQuote 
test http://www.webservicex.net/BibleWebservice.asmx?wsdl GetBibleWordsByBookTitleAndChapter Jude 1 
test  http://developerdays.com/cgi-bin/tempconverter.exe/wsdl/ITempConverter CtoF 38 
test http://developerdays.com/cgi-bin/tempconverter.exe/wsdl/ITempConverter  FtoC 100  
test http://www.holidaywebservice.com/Holidays/US/USHolidayService.asmx?WSDL GetBlackFriday 2008 
test  http://www.ghettodriveby.com/soap/?wsdl getRandomGoogleSearch dilbert 
test  http://www.boyzoid.com/threat.cfc?wsdl threatLevel 
wsdl  http://www.abysal.com/soap/AbysalEmail.wsdl SendEmail "John Doe" tempemail@gmail.com "Jack The Ripper" jtr@evil.net "Hello World" "Hi how are you doing" 0 6 >/dev/null
test http://webservices.imacination.com/distance/Distance.jws?wsdl getDistance 90209 90209  
test  http://webservices.imacination.com/distance/Distance.jws?wsdl getCity 90209 
test http://webservices.imacination.com/distance/Distance.jws?wsdl getLocation 90209 
test http://webservices.imacination.com/distance/Distance.jws?wsdl  getLongitude 90209 
wsdl  http://www.bindingpoint.com/ws/imalert/imalert.asmx?wsdlSendYahoo "" "screen name"  myyahooid "Hello wassup!" >/dev/null 
test  http://www.ripedev.com/webservices/LocalTime.asmx?WSDL LocalTimeByZipCode 90209  
test  http://www.ripedev.com/webservices/ZipCode.asmx?WSDL CityToZipCode "Beverly Hills" 
test  http://www.abundanttech.com/webservices/population/population.wsdl getPopulation "India" 
test  http://www.abundanttech.com/webservices/population/population.wsdl getWorldPopulation 
test  http://www.abundanttech.com/webservices/population/population.wsdl getCountries 
test  http://mssoapinterop.org/asmx/simple.asmx?wsdl echoFloat 3.14
test  http://www.esynaps.com/WebServices/DailyDiblert.asmx?wsdl DailyDilbertImagePath
test  http://www.webservicex.net/country.asmx?wsdl GetISD India
test  http://www.doughughes.net/WebServices/fortune/fortune.cfc?wsdl getFortune goedel 0 1000
test  http://www.ignyte.com/webservices/ignyte.whatsshowing.webservice/moviefunctions.asmx?wsdl GetTheatersAndMovies 90209 3
wsdl -l -d  developer.ebay.com/webservices/latest/eBaySvc.wsdl >/dev/null && echo $?
#This web service is no longer available
#test  http://www.xmethods.net/sd/2001/CurrencyExchangeService.wsdl getRate  Singapore  India 
#wsdl  http://www.xmethods.net/sd/2001/CurrencyExchangeService.wsdl  getRate  "United States"  India >/dev/null && echo $?
#test  http://www.xmethods.net/sd/2001/CurrencyExchangeService.wsdl  getRate India UK  
#test  http://www.xmethods.net/sd/2001/CurrencyExchangeService.wsdl getCurrentExchangeRate INR  
wsdl -l -d http://violino.dsi.unifi.it:8080/AxcpNotificationWS/AxcpNotification?wsdl >/dev/null && echo $?
