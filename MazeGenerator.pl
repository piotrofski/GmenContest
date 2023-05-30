#!/usr/bin/perl
use warnings;
use strict;
die "input format error, type it this way: perl programName.pl Width Height\n" unless (scalar(@ARGV) == 2);
my ($W, $H) = @ARGV;
my @a = ([(1)x(3+2*$W)], map({ [1, (0)x(1+2*$W), 1] } 1 .. 1+2*$H), [(
+1)x(3+2*$W)]);
for my $u (0 .. $H-1) {
    for my $v (0 .. $W-1) {
        $a[2+2*$u][2+2*$v] = 1;
    }
}
my @y = (-1)x($W*$H);
my $C; $C = sub {
    no warnings "recursion";
    my($v) = @_;
    my $w = $y[$v];
    if ($w < 0) {
        return $v;
    } else {
        my $z = &$C($w);
        $y[$v] = $z;
        return $z;
    }
};
my $U = sub {
    my($u, $v) = @_;
    my($c, $d) = (&$C($u), &$C($v));
    $c != $d and
        $y[$c] = $d;
};
while (&$C(0) != &$C($W*$H-1)) {
    my $a = 1 < rand(2);
    my $x = int(rand($H));
    my $y = int(rand($W));
    $a ? $y < $W - 1 : $x < $H - 1 or next;
    my ($u, $v) = (($x+!$a)*$W+($y+$a), $x*$W+$y);
    &$C($u) != &$C($v) || rand(5) < 1 or next; # here's the magic
    &$U($u, $v);
    $a[2+!$a+2*$x][2+$a+2*$y] = 1;
}
for my $r (1 .. 1+2*$H) {
    for my $c (1 .. 1+2*$W) {
        my $o = $a[$r][$c];
        my $v = $a[$r-1][$c] && $a[$r+1][$c];
        my $h = $a[$r][$c-1] && $a[$r][$c+1];
        print(
            2 == $r && 2 == $c ? "@" :
            2*$H == $r && 1+2*$W == $c ? ">" :
            $o ? " " :
            $v ? ($h ? " " : "-") :
            ($h ? "|" : "+")
        );
    }
    print "\n";
}
