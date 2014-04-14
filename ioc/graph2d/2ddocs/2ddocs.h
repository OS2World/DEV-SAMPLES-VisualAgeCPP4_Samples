/* Revision: 57 1.5.1.2 samples/graph2d/2ddocs/2ddocs.h, ocsamples-L1, ioc.v400, 981111  */
/*
--------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1997.
All rights reserved.

Permission is granted to copy, use, modify, and merge this software into
your applications and to permit others to do any of the foregoing. You must
include this permission and copyright notice in all copies and modified
versions of this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS'
CONDITION. IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES
WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
--------------------------------------------------------------------------------
*/

#ifndef _2DDOCS_
#define _2DDOCS_

#define IC_ID_WND_MAIN                                                          0x1000
#define IC_ID_WND_DRAW                                                          0x8008

#define IC_ID_EXAMPLE_BOLT                                                      0x1201
#define IC_ID_EXAMPLE_STAR_ROTATE_CENTER                        0x1202
#define IC_ID_EXAMPLE_STAR_ROTATE_VIEWORIGIN            0x1203
#define IC_ID_EXAMPLE_STAR_ROTATE_ARBITRARYPOINT        0x1204
#define IC_ID_EXAMPLE_STAR_SCALE_CENTER                         0x1205
#define IC_ID_EXAMPLE_STAR_SCALE_VIEWORIGIN                     0x1206
#define IC_ID_EXAMPLE_STAR_SCALE_ARBITRARYPOINT         0x1207
#define IC_ID_EXAMPLE_STAR_MIRRORX                                      0x1208
#define IC_ID_EXAMPLE_STAR_MIRRORY                                      0x1209
#define IC_ID_EXAMPLE_STAR_MIRRORXY                                     0x120A
#define IC_ID_EXAMPLE_STAR_TRANSLATE                            0x120B
#define IC_ID_EXAMPLE_WAGON                                                     0x120C
#define IC_ID_EXAMPLE_CAG_ARBITRARY                                     0x120D
#define IC_ID_EXAMPLE_CAG_APPLE                                         0x120E
#define IC_ID_EXAMPLE_CAG_BANANA                                        0x120F
#define IC_ID_EXAMPLE_CAG_L                                                     0x1210
#define IC_ID_EXAMPLE_PIPELINE_SIMPLE_LINKED            0x1211
#define IC_ID_EXAMPLE_PIPELINE_SIMPLE_BUNDLE            0x1212
#define IC_ID_EXAMPLE_PIPELINE_COMPLEX_CLIP                     0x1213
#define IC_ID_EXAMPLE_PIPELINE_COMPLEX_CONCAT           0x1214
#define IC_ID_EXAMPLE_PIPELINE_COMPLEX_MULTILINKED      0x1215
#define IC_ID_EXAMPLE_PIPELINE_DIRECT                           0x1216
#define IC_ID_EXAMPLE_PIPELINE_DIRECT_CLIP                      0x1217

#define IC_ID_EXAMPLE__FIRST                                            IC_ID_EXAMPLE_BOLT
#define IC_ID_EXAMPLE__LAST                                                     IC_ID_EXAMPLE_PIPELINE_DIRECT_CLIP

#define IC_ID_ERROR_NO_EXAMPLE_SELECTED                         0x1300

#endif // _2DDOCS_
