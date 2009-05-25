#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/


int do_nothing(void);
int do_nothing2(void);

int main(int argc, char** argv)
{
        int err;
        err = do_nothing2();
        if (err) return err;
        return do_nothing();
}
