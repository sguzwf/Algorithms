#!/usr/bin/perl 
use strict;
use warnings;
# use 5.014;

# purpose: scan src/ and generate makefile
my $srcPath = "./src";
my $objPath = "./obj";
my $srcDh   = undef;
my $flags   = "-O3 -std=c++11 -Wall -Wextra -Weffc++";
my @src     = ();
my @obj     = ();
my $exe     = "stamp";
if($ARGV[0])
{
    $exe    = $ARGV[0];
}
mkdir $srcPath if(not -e $srcPath);
mkdir $objPath if(not -e $objPath);
if(opendir $srcDh,$srcPath)
{
    print "open src dir successfully";
    print "\n";
    for my $srcFile (readdir $srcDh)
    {
        push @src,$srcFile if($srcFile ne "." and $srcFile ne "..");
    }
    closedir $srcDh;
}
for my $srcFile (@src)
{
    push @obj,"$1.o" if($srcFile =~/^(.*)\.cpp$/);
}

open my $makeFh,">","makefile" or die "can't creat makefile";
print $makeFh "CXX    = g++";
print $makeFh "\n";
print $makeFh "FLAGS  = $flags";
print $makeFh "\n";
print $makeFh "EXE    = $exe";
print $makeFh "\n";
print $makeFh "DEPS   = makefile";
print $makeFh "\n";
print $makeFh "SRCDIR = src";
print $makeFh "\n";
print $makeFh "OBJDIR = obj";
print $makeFh "\n";
src_obj($makeFh,"SRC_",\@src);
src_obj($makeFh,"OBJ_",\@obj);
print $makeFh "SRC    = \$(patsubst %,\$(SRCDIR)/%,\$(SRC_))";
print $makeFh "\n";
print $makeFh "OBJ    = \$(patsubst %,\$(OBJDIR)/%,\$(OBJ_))";
print $makeFh "\n";
print $makeFh "###################################################\n\n\n";
print $makeFh "\$(OBJDIR)/%.o:\$(SRCDIR)/%.cpp  \$(DEPS)";
print $makeFh "\n";
print $makeFh	"\t\$(CXX) -c \$< -o \$\@ \$(FLAGS)";
print $makeFh "\n";

print $makeFh "$exe:\$(OBJ) \$(SRC) \$(DEPS)";
print $makeFh "\n";
print $makeFh "\t\$(CXX) -o \$(EXE) \$(OBJ) \$(FLAGS)";
print $makeFh "\n";

print $makeFh ".PHONY:clean";
print $makeFh "\n";
print $makeFh "";
print $makeFh "\n";
print $makeFh "clean:";
print $makeFh "\n";
print $makeFh "\trm -rf \$(OBJDIR)/*.o";
print $makeFh "\n";
print $makeFh "\trm -rf \$(EXE)";
print $makeFh "\n";
print $makeFh "\trm -rf \$(EXE).exe";
print $makeFh "\n";
print $makeFh "";
print $makeFh "\n";
print $makeFh ".PHONY:tidy";
print $makeFh "\n";
print $makeFh "";
print $makeFh "\n";
print $makeFh "tidy:";
print $makeFh "\n";
print $makeFh "\trm -rf \$(OBJDIR)/*.o";
print $makeFh "\n";
	

close $makeFh;

sub src_obj
{
    my($makeFh,$name,$ra_list) = @_;
    my $str = join "\\\n\t     ",@{$ra_list};
    print $makeFh "$name   = $str";
    print $makeFh "\n";
}

