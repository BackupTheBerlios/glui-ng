/***********************************************************************
* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
* This library is free software; you can redistribute it and/or modify
* it under the terms of the LGPL v2.1 or latter at your option
* http://www.gnu.org/copyleft/lesser.html
************************************************************************/


int do_nothing2(void)
{
  int i;
  int ff=0xFFFF;
  for (i=0; i<100; i++)
    {
      ff^=i;
    }
}
