#!/usr/bin/perl -w

# (c) Earnol

open(STACKDMP, "<stackdump.txt"); # file with memory below esp register
@STACK = <STACKDMP>;
close(STACKDMP);

open(MODULELIST, "<modulelist.txt");  #file with copy from visual studio modules window
@MODULELISTL = <MODULELIST>;
close(MODULELIST); 
foreach $stackl (@STACK)
{
  @ADDRS = $stackl =~ /\s((?:[a-f]|\d){8})/g;
  foreach $addr (@ADDRS)
  {
    foreach $moduleline (@MODULELISTL)
    {
      if($moduleline =~ /((?:.*?)\.dll)(?:.*?)((?:[A-F]|\d){8}\-(?:[A-F]|\d){8})/)
      {
        $module = $1;
        $addrRange = $2;
        if($addrRange =~ /((?:[A-F]|\d){8})\-((?:[A-F]|\d){8})/)
        {
          $addrFrom = $1;
          $addrTo   = $2; 
          if((hex($addrFrom) <= hex($addr)) && (hex($addr) <= hex($addrTo)))
          {
            print "$module: $addr at $stackl";
          }
        }
      }
    }
  }
}