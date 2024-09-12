#!/usr/bin/perl -w

# This script will guess and reconstruct values down from CRC32 check sums
# (c) Earnol

use IO::Dir;
use IO::File;
use Win32::API;

my $adler = new Win32::API('zlib1.dll', 'adler32', 'NSN', 'N', '_cdecl');
die if (!defined($adler));

Win32::API::Struct->typedef('DATASTRUCT', 'LONG', 'd');
$Guess = 0;

doIt();

sub doIt
{
 my $datastr = Win32::API::Struct->new('DATASTRUCT');
 $datastr->align('auto');
 $line = 0;
 $prev = 0;
 while(<>)
 {
  $line++;
  #Item checksum: 0xDBD790F7, chunk ID: 4 size: 12
  if(/checksum\:\s0x((?:[A-F]|\d){8})\,\schunk\sID\:\s(\d+)\ssize\:\s(\d+)/)
  {
    $curr = hex($1);
    $id   = $2 + 0;
    $size = $3 + 0;
    if($size == 1 || $size == 4)
    {
      $rec = GuessValue($prev, $curr, $id, $size, $datastr);
      print "Item checksum: 0x".$1.", chunk ID: $2 size: $3 value $rec\n";
    }
    else
    {
      print "$_";
    }
    $prev = $curr;
  }
  else
  {
    print $_;
  }
 }
}

sub adlerProc
{
my ($prevChekSum, $chunkID, $data, $size, $datastr) = @_;
$datastr->{d} = $chunkID;
my $nRet = $adler->Call($prevChekSum, $datastr, 1);
   $datastr->{d} = $data;
   $nRet = $adler->Call($nRet, $datastr, $size);
   if($nRet < 0)
   {
    $nRet = hex("ffffffff") + $nRet + 1;
   }
   return $nRet;
}

sub GuessValue
{
  my ($prevChekSum, $resSum, $chunkID, $size,$datastr) = @_;
  my $i = 0; 
  my $nGuess = 0;
  my $nEnd   = 102;
  my $nStart = -10;
  $Guess += 1;
  print "$Guess\n";
  for($i = $nStart; $i < $nEnd; $i++)
  {
    $nGuess = adlerProc($prevChekSum, $chunkID, $i, $size, $datastr);
    return $i if($nGuess == $resSum);
  }

  my $real = 0;
  for($i = 0; $i < 10;)
  {
    $i += 0.1;
    $real = unpack("I", pack("f", $i));
    $nGuess = adlerProc($prevChekSum, $chunkID, $real, $size, $datastr);
    return unpack("f",pack("I", $real)) if($nGuess == $resSum);
  } 
  return -1000;
}

