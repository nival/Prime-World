use trbtransform;
use Cwd;
use File::Basename;
use File::Copy;
use File::Find;
use File::Path;
use strict;


my $old_aio_dir = "TProactor";
my $new_aio_dir = "ace";

my $old_prefix = "TRB_";
my $new_prefix = "ACE_";

my $old_ssl_lib = "TProactor_SSL";
my $new_ssl_lib = "ACE_SSL";;

my $old_aio_export = uc ( ${old_aio_dir} );
my $new_aio_export = uc ( ${new_aio_dir} );


my $old_ssl_export = uc ( ${old_ssl_lib} );
my $new_ssl_export = uc ( ${new_ssl_lib} );

my %tableCPP = 
(
    quotemeta("${old_aio_dir}/")     => "${new_aio_dir}/",
    quotemeta("${old_prefix}")       => "${new_prefix}",
    quotemeta("/TPROACTOR_Export\.h")  => "/ACE_export.h",
    quotemeta("/SSL/TPROACTOR_SSL_Export\.h")  => "/SSL/SSL_Export.h",
    quotemeta(" TPROACTOR_")         =>  " ACE_",
    quotemeta(" TPROACTOR_SSL_")     =>  " ACE_SSL_",
    quotemeta("\.i\"")               =>  ".inl\"",
);
     
my %tableMPC = 
(
    quotemeta("${old_aio_dir}")          => "${new_aio_dir}",
    quotemeta("${old_prefix}")           => "${new_prefix}",
    quotemeta("${old_ssl_lib}")          => "${new_ssl_lib}",
    quotemeta("TPROACTOR_BUILD_DLL")     => "ACE_BUILD_DLL",
    quotemeta("TPROACTOR_SSL_BUILD_DLL") => "ACE_SSL_BUILD_DLL",
);
     

my @patternTemplatesCPP = ( 
    "Asynch_Acceptor\.cpp" ,
    "Asynch_Connector\.cpp" ,
    "POSIX_AIO_Allocator\.cpp"
);         

my @patternCPP = ( 
    "Asynch", 
    "WIN32_" , 
    "POSIX_" , 
    "SUN_" , 
    "Proactor", 
);

my @patternSSL = ( 
    "SSL_Asynch" ,
);

my @patternOBJ = ( 
    "\.obj\$", 
    "\.o\$"
);

my @patternMPC = ( 
   "^ace.mpc" ,
   "^ssl.mpc"
);

my @original_files;
my @new_cpp_files;
my @new_template_files;
# -------------------------------------------------
#
# -------------------------------------------------
sub build_original_list 
{
    my $srcdir  = $_[0];
    my $esrcdir = quotemeta (${srcdir});
    
    local * find_wanted = sub 
    {                                                      
        my $x = $_;                                       
                                                           
        my $curname = $File::Find::name;                      

        $curname =~ s/^${esrcdir}// ;                           

        foreach my $y ( @patternOBJ )               
        {                                                  
            if ( $x =~ m/$y/ )                             
            {                                              
                return;                                    
            }                                              
                                                           
        }                                                  
 
        foreach my $z ( @patternTemplatesCPP )               
        {                                                  
            if ( $x =~ m/^$z/ )                             
            {                                              
                push  ( @original_files, $curname );     
                return;                                    
            }                                              
        }
        
        foreach my $z ( @patternCPP )               
        {                                                  
            if ( $x =~ m/^$z/ )                             
            {                                              
                push  ( @original_files, $curname );     
                return;                                    
            }                                              
        }
        
        foreach my $z ( @patternSSL )               
        {                                                  
            if ( $x =~ m/^$z/ )                             
            {                                              
                push  ( @original_files, $curname );     
                return;                                    
            }                                              
        }
        
        foreach my $z ( @patternMPC )               
        {                                                  
            if ( $x =~ m/$z/ )                             
            {                                              
                push  ( @original_files, $curname );     
                #print "Added $curname   ==  $x\n";          
                return;                                    
            }                                              
        }
    };                                                      
                                                               
    my %find_options =                                     
    (                                                      
          "wanted"      => \&find_wanted ,                    
    );                                                     

    find (\%find_options,  ("${srcdir}") );
}

sub build_new_lists
{
    my $srcdir  = $_[0];
    
    my $esrcdir = quotemeta (${srcdir});
    
    local * find_wanted = sub 
    {                                                      
        my $x = $_;                                       
                                                           
        my $curname = $File::Find::name;                      
                                                           
        $curname =~ s/^${esrcdir}// ;  
        
        foreach my $y ( @patternSSL )               
        {                                                  
            if ( $x =~ m/^$y/ )                             
            {  
                return;
             }
         }
        
        foreach my $y ( @patternTemplatesCPP )               
        {                                                  
            if ( $x =~ /$y/ )                             
            {  
                push (@new_template_files, $x);                                            
                return;                                    
            }                                              
                                                           
        }                                                  

        if ( $x =~ m/\.cpp$/ )
        { 
            push  ( @new_cpp_files, $x );     
            return;                                    
        }
        
 
    };                                                      
                                                               
    my %find_options =                                     
    (                                                      
          "wanted"      => \&find_wanted ,                    
    );        
    
    find (\%find_options,  ("${srcdir}") );
                                             
}
     
sub modify_ace_mpc 
{
    my $ace_mpc = $_[0];
    
    my @lines1;
    my @lines2;
    my $flg1 = 0;
    my $flg2 = 0;
    
    read_file ($ace_mpc, \@lines1);

    print ("Remove from ace.mpc:\n");
    
    OUTER: foreach my $x (@lines1)
    {
        INNER1: foreach my $y (@patternTemplatesCPP)
        {
            if ( $x =~ m/$y/ )
            {
                print "$x";
                
                if ($flg1 != 0)
                {
                    next OUTER;
                }
            
                $flg1 = 1;      
                foreach my $z (@new_template_files)
                {
                    push (@lines2, "        $z\n");
                }
                    
                next OUTER;
            }
        }
        
        INNER2: foreach my $y (@patternCPP)
        {
            if ( $x =~ m/$y/ )
            {
                print "$x";
                
                if ($flg2 != 0)
                {
                    next OUTER;
                }
                
                $flg2 = 1;      
                foreach my $z (@new_cpp_files)
                {
                    push (@lines2, "        $z\n");
                }
                    
                next OUTER;
            }
        }
        push (@lines2, $x);
    }

    print_array ( "Added source files to ace.mpc:", \@new_cpp_files);
    print_array ( "Added template files to ace.mpc:", \@new_template_files);
    
    write_file ($ace_mpc, \@lines2);
}
              
sub make_ace_backup
{
    my $ace_root   = $_[0];
    my $src_dir    = "${ace_root}/ace";   
    my $backup_dir = "${ace_root}/ace.bak";
    
    if (-d "${backup_dir}"  )
    {
        die ("Directory ${backup_dir} already exists\n");
    }

    
    build_original_list ( "${src_dir}" );
    mkpath ("${backup_dir}/SSL", 1);
    
    copy_files ( $src_dir, $backup_dir, \@original_files);
}              

sub generate_demo_mpc 
{
    my $demo_dir = $_[0];
    my $ace_root = $_[1];
    
    write_line ( "${demo_dir}/aiodefaults.mpb", <<"EOL1");
project {
    staticflags += ACE_AS_STATIC_LIBS

    includes    += \$(ACE_ROOT)

    libpaths    += ${demo_dir}/lib
    libpaths    += \$(ACE_ROOT)/lib

    after       += ACE  
    libs        += ACE
}
EOL1
    
    write_line ("${demo_dir}/aiolib.mpb", <<"EOL2");
project: aiodefaults {
    libout       = ${demo_dir}/lib
    dllout       = ${demo_dir}/lib
}
EOL2

    write_line ( "${demo_dir}/aioexe.mpb", <<"EOL3");
project: aiodefaults {
    install = ${demo_dir}/bin
}
EOL3

    write_line ( "${demo_dir}/aiotests.mpb", <<"EOL31");
project: aiodefaults {
    install   = ${demo_dir}/bin
    includes += ${demo_dir}/tests/common
}
EOL31

    
    write_line ( "${demo_dir}/assl.mpb", <<"EOL4");
project: ssl {
}
EOL4

    write_line ( "${demo_dir}/build.mwc", <<"EOL5");
workspace (AIO_TEST) {
   ./tests  
}
EOL5

    write_line ( "${demo_dir}/linaio.mpb", <<"EOL6");
project {
  libs += aio
  libpaths += /usr/lib
}
EOL6

}

# ************************************************************
#   main entry point
# ************************************************************

sub do_main 
{
    my $ACE_ROOT = $ENV {"ACE_ROOT"};
 
    my $genexp   = "${ACE_ROOT}/bin/generate_export_file.pl" ; 
    my $curdir   = getcwd ();
    
    if (@ARGV < 1)
    {
        die ("usage : $0 output_dir_name \n");
    }
    my $FROM_ROOT  = getcwd() ;
    my $TO_ROOT    = $ARGV[0];

    mkpath ("${TO_ROOT}", 1);
    chdir $TO_ROOT;
    $TO_ROOT = getcwd ();
    chdir $curdir;
    
    print ("============= Doing ACE Proactor backup ===================\n");
    make_ace_backup (${ACE_ROOT});
    
    print ("============= Replacing ace.mpc file ============\n");
    build_new_lists ( "${FROM_ROOT}/${old_aio_dir}");
    modify_ace_mpc ( "${ACE_ROOT}/ace/ace.mpc");      
    
    print ("============= Replacing ACE Proactor (CPP,H,INL) files ======\n");
    process_dir_cpp ("${FROM_ROOT}/${old_aio_dir}",      "${ACE_ROOT}/ace" ,    \%tableCPP );
    process_dir_cpp ("${FROM_ROOT}/${old_aio_dir}/SSL",  "${ACE_ROOT}/ace/SSL" , \%tableCPP );
    
    
    print ("============= Copying Examples and tests ======\n");
    mkpath ("${TO_ROOT}/bin", 1);

    process_dir  ("$FROM_ROOT/tests", "${TO_ROOT}/tests" ,  \%tableCPP, \%tableMPC );

    foreach my $z ( glob ( "${FROM_ROOT}/tests/*" ) )
    {
        if (-d $z)
        {
            my $y = basename($z);
            process_dir  ( $z,  "${TO_ROOT}/tests/$y" ,  \%tableCPP, \%tableMPC );
        }
    }

    generate_demo_mpc (${TO_ROOT}, ${ACE_ROOT});


    foreach my $z (glob("${FROM_ROOT}/bin/*.pem"))
    {
       copy ( "$z", "${TO_ROOT}/bin/".basename($z));
    }
    

    print ("============= Generating Makefiles and projects ======\n");
    
    if ($^O =~ m/MSWin32/)
    {
        chdir "${ACE_ROOT}/ace";
        system ("perl ${ACE_ROOT}/bin/mwc.pl -type VC71 ace.mwc");
        chdir "${TO_ROOT}";
        system ("perl ${ACE_ROOT}/bin/mwc.pl -type VC71 -include ${TO_ROOT} build.mwc");    
    }
    elsif ($^O =~ m/linux/)
    {
        chdir "${ACE_ROOT}/ace";
        system ("perl ${ACE_ROOT}/bin/mwc.pl -type gnuace -global ${TO_ROOT}/linaio.mpb ace.mwc");
        chdir "${TO_ROOT}";
        system ("cd ${TO_ROOT}; perl ${ACE_ROOT}/bin/mwc.pl -type gnuace -include ${TO_ROOT} -global ${TO_ROOT}/linaio.mpb build.mwc");    
    }
    else
    {
        chdir "${ACE_ROOT}/ace";
        system ("perl ${ACE_ROOT}/bin/mwc.pl -type gnuace ace.mwc");
        chdir "${TO_ROOT}";
        system ("perl ${ACE_ROOT}/bin/mwc.pl -type gnuace -include ${TO_ROOT} build.mwc");    
    }
    
    #print_hash_table (\%tableCPP, "CPP");
    #print_hash_table (\%tableMPC, "MPC");
}

do_main ;



