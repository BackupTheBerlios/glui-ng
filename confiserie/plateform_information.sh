#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

cat >&2 <<EOF
## --------- ##
## Platform. ##
## --------- ##

uname -a = `(uname -m) 2>/dev/null || printf unknown`

/bin/arch              = `(/bin/arch) 2>/dev/null              || printf unknown`
/usr/bin/arch -k       = `(/usr/bin/arch -k) 2>/dev/null       || printf unknown`
/usr/convex/getsysinfo = `(/usr/convex/getsysinfo) 2>/dev/null || printf unknown`
hostinfo               = `(hostinfo) 2>/dev/null               || printf unknown`
/bin/machine           = `(/bin/machine) 2>/dev/null           || printf unknown`
/usr/bin/oslevel       = `(/usr/bin/oslevel) 2>/dev/null       || printf unknown`
/bin/universe          = `(/bin/universe) 2>/dev/null          || printf unknown`

$PATH
EOF
