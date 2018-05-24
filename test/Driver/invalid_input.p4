! RUN: not %ppf a.p4 b.p4 c.p4 2>&1 | %file_check %s -check-prefix=MULTIPLE
! RUN: not %ppf abcdefghxyz.p4 2>&1 | %file_check %s -check-prefix=NONEXITENT

! MULTIPLE: Can only have one input
! NONEXISTENT: Could not open input file 'abcdefghxyz.p4': No such file or directory

