/* 
 * File:   IOGlobals.h
 * Author: diego schmaedech
 * 
 *
 * Created on May 24, 2010, 4:09 PM
 */
/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library  
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
//
							For Open Source Biosignal SCADA
//
// Copyright (C) 2010, Laboratório de Educação Cerebral, all rights reserved.
//
// Third party copyrights are property of their respective owners.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/
#ifndef _IOGLOBALS_H
#define	_IOGLOBALS_H

static const double PI = 3.14159265358979323846;

//#define DEVICE CV_CAP_ANY
#define DEVICE 0
#define NTRACK 10
#define SCALE  2

#define  EYE_TPL_WIDTH       40
#define  EYE_TPL_HEIGHT      25
#define  EYE_BOX_WIDTH    50
#define  EYE_BOX_HEIGHT   30

#define  NOSE_TPL_WIDTH       60
#define  NOSE_TPL_HEIGHT      40
#define  NOSE_BOX_WIDTH    70
#define  NOSE_BOX_HEIGHT   50

#define  MOUTH_TPL_WIDTH       80
#define  MOUTH_TPL_HEIGHT      40
#define  MOUTH_BOX_WIDTH    90
#define  MOUTH_BOX_HEIGHT   50

 
#endif	/* _IOGLOBALS_H */

