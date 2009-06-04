/***********************************************************************
* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
* This library is free software; you can redistribute it and/or modify
* it under the terms of the LGPL v2.1 or latter at your option
* http://www.gnu.org/copyleft/lesser.html
************************************************************************/
#include "libconfiserie.h"

void confiserie::tata(void)
{
        for(int i=0; i<1000; i++)
        {
                this->toto(i);
        }
}

void confiserie::toto(int i)
{
        j=j^i;
}
