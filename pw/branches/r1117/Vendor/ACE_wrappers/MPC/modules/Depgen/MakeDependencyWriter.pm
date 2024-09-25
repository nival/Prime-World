package MakeDependencyWriter;

# ************************************************************
# Description   : Generates generic Makefile dependencies.
# Author        : Chad Elliott
# Create Date   : 2/10/2002
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;
use DependencyWriter;

use vars qw(@ISA);
@ISA = qw(DependencyWriter);

# ************************************************************
# Subroutine Section
# ************************************************************

sub process {
  ## Sort the dependencies to make them reproducible
  return "@{$_[1]}: \\\n  " . join(" \\\n  ", sort @{$_[2]}) . "\n";
}


1;
