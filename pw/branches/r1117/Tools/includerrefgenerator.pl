#!/usr/bin/perl -w

# (c) Earnol

# command line example: perl includerrefgenerator.pl D:\Projects\pf\src\_Debug

#This script will extract all objects for static linkage for pragma
use IO::Dir;
use IO::File;

# ================PARAMETERS AREA =================== CHANGE ONLY THESE SETTINGS!!!
$selfname         = "includerrefgenerator.pl";  #we do not need to process ourself :)
$outputFName      = "ForceLink.cpp";
# ================ END OF PARAMETERS AREA =================== 



$processedCounter = 0;

if(defined($ARGV[1]))
{
  $outputFName = $ARGV[1];
}

my $fhw  = new IO::File $outputFName, "w";
$fhw->print("#include \"stdafx.h\"\n\n");

&traverseDir($ARGV[0]);

undef $fhw;

print "$processedCounter files had been processed.";

sub traverseDir 
{
  my $localdir = $_[0];
  my (@all, @files, @dirs, $newdir);

  print "Entering: $localdir\n";
  opendir(DIR, $localdir) || (print "\n ** can't open $localdir?? **\n") && return 0;

  @all = readdir(DIR);
  closedir(DIR);

  @files = grep { -f "$localdir/$_" } @all;
  @dirs  = grep { -d "$localdir/$_" } @all;

  #----- work on files first -----
  foreach $file (@files) 
  {
    if($file =~ /$selfname/)
    {
      next;
    } 

    processfile($file, $localdir);
  }

  #----- work on dirs -----
  my $mydir;
  foreach $mydir (@dirs) 
  {
    if(!($mydir eq "." || $mydir eq "..")) 
    {
      $newdir = "$localdir/$mydir"; 
      &traverseDir($newdir);
    }
  }
  print "Leaving: $localdir\n";
  return 1;
}

sub processfile
{
  my ($ffname, $dirprefix) = @_;
  if($ffname =~ /(?:.*?)\.lib$/i)
  {
    processlibfile($ffname, $dirprefix);
  }
}

sub processlibfile 
{
  my ($ffname, $dirprefix) = @_;
  print "Processing $ffname\n";
  my $fh = new IO::File "$dirprefix/$ffname", "r";
  my $inpsep = $/;
  undef $/;
  $fh->binmode();
  $multiline = <$fh>;
  $fh->close();
  $/ = $inpsep;
  undef $fh;

  @CONSTRUCTS = $multiline =~ /\x00(\?\?0\w(?:[A-Z]|[a-z]|\@|\_|\$|\d)*?\@\@QAE\@XZ)\x00/g;

  foreach $line (@CONSTRUCTS)
  {
    if(($line =~ /SRegister\_/) && !($line =~ /PF_Tests/))
    {
      $fhw->print("#pragma comment(linker, \"/include:".$line."\")\n");                                              
    }
  }

 
  #??__E?SRegister_ti@LCChatJoinChannel@@1UTypeInfo@CommandFactory@@A@@YAXXZ
  @CONSTRUCTS = $multiline =~ /\x00(\?SRegister\_\@\_nam\_(?:[A-Z]|[a-z]|\@|\_|\$|\d)*?\@\@A)\x00/g;

  foreach $line (@CONSTRUCTS)
  {
    print $line;
    if(!($line =~ /PF_Tests/))
    {
      $fhw->print("#pragma comment(linker, \"/include:".$line."\")\n");                                              
    }
  }

  $processedCounter++;
}

#$(SolutionDir)Vendor\BuildUtils\includerrefgenerator.exe $(OutDir) $(InputDir)\ForceLink.cpp

