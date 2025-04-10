package  trbtransform;

use strict;
use vars qw (@ISA @EXPORT @EXPORT_OK $VERSION);

require    Exporter;

our @ISA       = qw(Exporter);
our @EXPORT    = qw(&copy_files 
                    &move_files
                    &read_file 
                    &write_file
                    &write_line
                    &do_replace
                    &process_dir
                    &process_dir_cpp
                    &print_array
                    &print_hash_table);   # Symbols to be exported by default
our @EXPORT_OK = qw();               # Symbols to be exported on request
our $VERSION   = 1.00;               # Version number


use Cwd;
use File::Basename;
use File::Copy;

# ************************************************************
#
# ************************************************************
sub copy_files
{
    my $srcdir     = $_[0];     # source      root dir
    my $dstdir     = $_[1];     # destination root dir
    my $list_files = $_[2];     # list of file names

    foreach my $z ( @$list_files )    # copy files
    {
        copy  ( "${srcdir}$z" , "${dstdir}$z" );
        print ("Copied : ${srcdir}$z to ${dstdir}$z\n");
    }

    my $num = @{$list_files};
    print ("Copied  $num files\n" );

}

sub move_files
{
    my $srcdir     = $_[0];     # source      root dir
    my $dstdir     = $_[1];     # destination root dir
    my $list_files = $_[2];     # list of file names

    foreach my $z ( @$list_files )    # copy files
    {
        move  ( "${srcdir}$z" , "${dstdir}$z" );
        print ("Moved : ${srcdir}$z to ${dstdir}$z\n");
    }

    my $num = @{$list_files};
    print ("Moved  $num files\n" );

}

sub print_array  
{
    my $text  = $_[0];
    my $arr   = $_[1];
    
    print "${text}\n";
    foreach  my $x ( @{$arr} )
    {
        print "    $x\n";
    }

}

sub print_hash_table 
{
    my $table = $_[0];
    my $text  = $_[1];
    
    print "====== Hash Table $text ======\n";
    foreach my $x (keys %{$table} )
    {
        print "$x => ${$table}{$x}\n";
    }

}

sub read_file
{
    my $filename  = $_[0];
    my $ref_array = $_[1];

    print "Read  file ${filename} ...\n";

    open (FH, "<" , $filename ) || die "can not open $filename : $!" ;

    @{$ref_array} = <FH>;

    close FH;
}

sub write_line
{
    my $filename  = $_[0];
    my $line = $_[1];

    print "Write file ${filename} ...\n";

    open (FH, ">" , $filename ) || die "can not open $filename : $!" ;

    print FH "${line}\n";
    
    truncate  (FH, tell(FH));
    close FH;
}

sub write_file
{
    my $filename  = $_[0];
    my $ref_array = $_[1];

    print "Write file ${filename} ...\n";

    open (FH, ">" , $filename ) || die "can not open $filename : $!" ;

    print FH @{$ref_array};

    truncate  (FH, tell(FH));
    close FH;
}

sub do_replace 
{
    my $ref_array = $_[0];

    shift;

    while (defined ($_[0]))
    {
        my $ref_map   = $_[0];
        shift;
        foreach  my $v1 ( keys % {$ref_map} )
        {
              my $v2= ${$ref_map}{$v1};
              my $line;

              foreach $line ( @{$ref_array} )
              {
                  $line =~ s/$v1/$v2/g;
              }
        }
  
    }

}

# ************************************************************
#
# ************************************************************

sub process_files 
{
    my $inpfiles  = $_[0];   
    my $outdir    = $_[1];
    
    my @files = glob ( $inpfiles );
    my @lines;
    my $file;

    mkdir (${outdir});

    shift;
    shift;

    foreach $file ( @files )
    {    
        if ( $file =~ m/_export.h$/ig)
        {
            print  ("Skip  file ${file} ...\n");
            next;
        }
        read_file  ($file ,  \@lines);

        do_replace (\@lines, @_);
        
        $file =~ s/\.i$/.inl/;

        write_file ("$outdir/".basename($file), \@lines);
    }
}

sub process_dir_cpp
{
    my $indir  = $_[0];   
    my $outdir = $_[1];
    my $mapCPP = $_[2];
    
    process_files  ("${indir}/*.cpp", $outdir ,  $mapCPP) ;
    process_files  ("${indir}/*.h",   $outdir ,  $mapCPP) ;
    process_files  ("${indir}/*.i*",  $outdir ,  $mapCPP) ;
}
 
sub process_dir 
{
    my $indir  = $_[0];   
    my $outdir = $_[1];
    my $mapCPP = $_[2];
    my $mapMPC = $_[3];
    
    process_files  ("${indir}/*.cpp", $outdir ,  $mapCPP) ;
    process_files  ("${indir}/*.h",   $outdir ,  $mapCPP) ;
    process_files  ("${indir}/*.i*",  $outdir ,  $mapCPP) ;
    
    process_files  ("${indir}/*.mpc", $outdir ,  $mapMPC) ;
    process_files  ("${indir}/*.mwc", $outdir ,  $mapMPC) ;
    process_files  ("${indir}/*.mpb", $outdir ,  $mapMPC) ;
} 
