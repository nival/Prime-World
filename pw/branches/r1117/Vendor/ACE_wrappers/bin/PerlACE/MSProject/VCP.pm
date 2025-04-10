# $Id: VCP.pm 80826 2008-03-04 14:51:23Z wotte $

package PerlACE::MSProject::VCP;

use strict;
use PerlACE::MSProject;

our @ISA = ("PerlACE::MSProject");

###############################################################################

# Constructor

sub new  
{
    my $proto = shift;
    my $class = ref ($proto) || $proto;
    my $self = $class->SUPER::new (@_);
    
    $self->{COMPILER} = "evc.com";

    bless ($self, $class);
    return $self;
}

###############################################################################

# Accessors

1;