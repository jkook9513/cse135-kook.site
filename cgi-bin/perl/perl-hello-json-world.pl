#!/usr/bin/perl
# In Perl, you must first install the JSON package from CPAN (the Perl equivalent to npm)
use JSON;

print "Cache-Control: no-cache\n";
print "Content-type: application/json\n\n";

$date = localtime();
$address = $ENV{REMOTE_ADDR};

my %message = ('title' => 'Hello, Perl! - Jonathan Kook', 'heading' => 'Hello, Perl! - Jonathan Kook', 'message' => 'This page was generated with the Perl Programming language', 'time' => $date, 'IP' => $address);

my $json = encode_json \%message;
print "$json\n";
