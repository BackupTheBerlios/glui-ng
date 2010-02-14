#ifndef GLUI_QUATERNION_H
#define GLUI_QUATERNION_H
/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/

#include "algebra3.h"
#include <cstdio>
namespace GLUI
{
    /* this line defines a new type: pointer to a function which returns a */
    /* double and takes as argument a double */
    typedef double (*V_FCT_PTR)(double);

    /****************************************************************
     *                    Quaternion                                *
     ****************************************************************/

    class quat
    {
        /*protected: */
        public:

            vec3  v;  /* vector component */
            double s;  /* scalar component */

            /*public: */

            /* Constructors */

            quat();
            quat(double x, double y, double z, double w);
            quat(const vec3 &v, double s);
            quat(double   s, const vec3 &v);
            quat(const double  *d);     /* copy from four-element double array  */
            quat(const quat   &q);     /* copy from other quat                */

            /* Assignment operators */

            quat  &operator  = (const quat &v);      /* assignment of a quat            */
            quat  &operator += (const quat &v);      /* incrementation by a quat        */
            quat  &operator -= (const quat &v);      /* decrementation by a quat        */
            quat  &operator *= (double d);      /* multiplication by a constant    */
            quat  &operator /= (double d);      /* division by a constant          */

            /* special functions */

            double  length() const;                   /* length of a quat                */
            double  length2() const;                  /* squared length of a quat        */
            quat  &normalize();                      /* normalize a quat                */
            quat  &apply(V_FCT_PTR fct);             /* apply a func. to each component */
            vec3   xform(const vec3 &v );            /* q*v*q-1                         */
            mat4   to_mat4() const;
            void   set_angle(double f);               /* set rot angle (degrees)         */
            void   scale_angle(double f);             /* scale rot angle (degrees)       */
            double  get_angle() const;                /* set rot angle (degrees)         */
            vec3   get_axis()  const;                /* get axis                        */

            void   print( FILE *file, const char *name ) const;  /* print to a file     */

            double &operator [] (int i);        /* indexing                        */
            const double &operator [] (int i) const;  /* indexing                        */

            void   set(double x, double y, double z);   /* set quat                        */
            void   set(const vec3 &v, double s);      /* set quat                        */

            /* friends */

            friend quat operator - (const quat &v);                   /* -q1            */
            friend quat operator + (const quat &a, const quat &b);    /* q1 + q2        */
            friend quat operator - (const quat &a, const quat &b);    /* q1 - q2        */
            friend quat operator * (const quat &a, double d);          /* q1 * 3.0       */
            friend quat operator * (double d, const quat &a);          /* 3.0 * q1       */
            friend quat operator * (const quat &a, const quat &b);    /* q1 * q2        */
            friend quat operator / (const quat &a, double d);          /* q1 / 3.0       */
            friend int operator == (const quat &a, const quat &b);    /* q1 == q2 ?     */
            friend int operator != (const quat &a, const quat &b);    /* q1 != q2 ?     */
            friend void swap(quat &a, quat &b);                       /* swap q1  &q2   */
            /*friend quat min(const quat &a, const quat &b);          -- min(q1, q2)    */
            /*friend quat max(const quat &a, const quat &b);          -- max(q1, q2)    */
            friend quat prod(const quat &a, const quat &b);          /* term by term mult*/
    };

    /* Utility functions */

    quat quat_identity();        /* Returns quaternion identity element */
    quat quat_slerp(const quat &from, const quat &to, double t);
}
#endif
