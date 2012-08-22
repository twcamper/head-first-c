#! /usr/bin/env sh
# GNU or BSD find:
#       "-perm +111" == any write bits of file mode are set
#       "-type f"    == regular file
#
# "grep -v" == invert result, i.e., filter out files under '.git'
# "sed 's/^\.\///g')`" == trim initial ./ from all paths
for path in `find . -perm +111 -type f | grep -v \.git | sed 's/^\.\///g')`
do
    # Is the path NOT listed?
    # (i.e does grep return null or empty string?)
		if test -z `grep -E ^$path$ .gitignore`
    then
		  echo adding \'$path\' to .gitignore
      echo $path >> .gitignore
    fi
done
