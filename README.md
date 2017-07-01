# ft_ls: Reproducing the behavior of ls command with the following flags: 

-a      Include directory entries whose names begin with a dot (.).
-1      (The numeric digit ``one''.)  Force output to be one entry per line.  This is
        the default when output is not to a terminal.
-l      (The lowercase letter ``ell''.)  List in long format.  (See below.)  If the
        output is to a terminal, a total sum for all the file sizes is output on a
        line before the long listing.
-R      Recursively list subdirectories encountered
-S      Sort files by size
-r      Reverse the order of the sort to get reverse lexicographical order or the
        oldest entries first (or largest files last, if combined with sort by size
-t      Sort by time modified (most recently modified first) before sorting the oper-
        ands by lexicographical order.
