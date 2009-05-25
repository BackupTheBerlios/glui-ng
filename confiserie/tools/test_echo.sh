#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/


#testing echo towards POSIX wanted behaviour
mytest() {
  if 	test $(echo "hello\thella") = "hello\thella" &&
    test $(echo -n "hello"; echo "hella") = "hellohella" &&
    test "$(echo -e 'hello\thella')" != "hello\thella"; then
    echo "echo seems to be Posix compliant" >&2
    return 0
  else
    echo "echo isn't Posix compliant. use GNU echo or ask your OS maintainer" >&2
    return 1
  fi
}

mytest
