use 5.24.1;
use utf8;

sub urlify {
  my ($str0) = @_;
  $str0 =~ s/^\s+|\s+$//g;
  my @strs = split(/\s+/, $str0);
  my $str1 = join("%20", @strs);
  return $str1;
}

my @examplePairs = (
  ("", ""),
  ("blah%20ka%20fa%20ma", "blah   ka fa ma   "),
  ("with%20tabs", "     with  tabs    "),
  ("trim%20front", "   trim front"),
  ("tim%20back", "trim back    "),
  ("lots%20of%20middle%20spaces", "lots of                  middle spaces"),
);

for (my $i = 0; $i < $#examplePairs; $i += 2) {
  my $expected = @examplePairs[$i];
  my $input = @examplePairs[$i+1];
  my $output = urlify($input);
  say $expected == $output ? "True" : "False";
  say $output;
}
