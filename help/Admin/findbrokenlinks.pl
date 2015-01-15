#!/usr/local/ActivePerl-5.6/bin/perl -w
#this must be run from within the directory of the .pl file (AdminScripts)
use Cwd;
chdir("..");

use File::Find qw(find);

#$nrdone = 0;
sub findbrokenlinks {
	#print "$_  $File::Find::name\r\n";
	#print ((($_ =~/\.html/)+1) . ((-T $File::Find::name)+1) . (($_ ne $replacehtmlfilename)+1));
    if ($_ =~/\.html$/)
	{
		$filename = $_;
		$filePath = $File::Find::name;
		open(HTML, $filename);
		#print $filename . "\n";
		@alllines = <HTML>;
		close(HTML);
		$fullfile = join("",@alllines);
		$cursearchstr = $fullfile;
		while($cursearchstr =~ /(<a[^>]+>)/)
		{
			$curtag = $1;
			$cursearchstr = $';
			if($curtag =~ /href=\"([a-zA-Z0-9_ \.\/\\]+)((#[a-zA-Z0-9]+)?)\"/i)
			{
				$filepath = $1;
				$bookmark = $2;
				if(! -e $filepath)
				{
					print "\nFound broken hyperlink in $filePath:\n$curtag\n";
				}
				elsif($bookmark ne "")
				{
					$bookmark = substr($bookmark, 1);
					open(HTML, $filepath);
					@alllines = <HTML>;
					close(HTML);
					$fullotherfile = join("",@alllines);
					$tempsearchstr = $fullotherfile;
					$foundtag = 0;
					while($tempsearchstr =~ /(<a[^>]+>)/)
					{
						$temptag = $1;
						$tempsearchstr = $';
						if($temptag =~ /name=\"([a-zA-Z0-9_]+)\"/i)
						{
							if($1 eq $bookmark)
							{
								$foundtag = 1;
							}
						}
					}
					if(!$foundtag)
					{
						print "\nFound broken hyperlink in $filePath (could not find bookmark $bookmark):\n$curtag\n";
					}
				}
			}
		}

		$cursearchstr = $fullfile;
		while($cursearchstr =~ /(<img[^>]+>)/)
		{
			$curtag = $1;
			$cursearchstr = $';
			if($curtag =~ /src=\"([a-zA-Z0-9_ \.\/\\]+)\"/i)
			{
				$filepath = $1;
				if(! -e $filepath)
				{
					print "\nFound broken image link in $filePath:\n$curtag\n";
				}
			}
		}
	}
}

find(\&findbrokenlinks, ".");
