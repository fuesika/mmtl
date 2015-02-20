/****************************************************************************\
*                                                                            *
*  ROUTINE NAME                 electro_gendata_netlist.h        *
*                                                                            *
*  ABSTRACT                                                                  *
*       Definitions for the GENDATA to read the icon section of the      *
* graphic file and generate a netilist.            *
*                                                                            *
*  CALLING FORMAT                                                            *
*       #include "electro_gendata_netlist.h"             *
*                                                                            *
*  CALLED BY                                                                 *
*    electro_gendata_2dlf.c                *
*    electro_gendata_2dly.c                *
*                                                                            *
*  AUTHOR               Jeff Prentice                                        *
*                                                                            *
*  CREATION DATE        21-Feb-1991              *
*                                                                            *
*       Copyright (C) 1989 by Mayo Foundation.  All rights reserved.         *
*                                                                            *
\****************************************************************************/

#ifndef electro_gendata_netlist_h
#define electro_gendata_netlist_h

/************************************************
*           *
* Netlist data structure      *
*           *
************************************************/
typedef struct netlist {
    struct attribute  *attributes;      /* list of icon attributes      */
    struct pin    *pins;        /* list of icon pins      */
    int     exists;       /* indicates if the icon exists */
    int     attribute_count;    /* # of icon attributes     */
    int     pin_count;      /* # of pins in the icon      */
} NETLIST_REC;

#endif



