#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/


#testing printf towards POSIX wanted behaviour
mytest() {
  if [ "$(printf "hello\thella")" = "hello	hella" ] &&
    [ "$(printf "hello"; printf "hella")" = "hellohella" ]; then
    printf "printf seems to be Posix compliant\n"
    return 0
  else
    printf "printf isn't Posix compliant. use GNU printf or ask your OS maintainer\n" >&2
    return 1
  fi
}

mytest
