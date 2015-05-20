/* 
 * File:   MultiCamera.cpp
 * Author: diego
 * 
 * Created on June 10, 2010, 1:08 AM
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
#include "stdafx.h"
#include "MultiCamera.h"
#include "cv.h"
#include "highgui.h"
#include "Demand.h"

void MultiCamera::setup(int index){
   // capture = cvCaptureFromCAM(index);
    const char *filename="G:\\17214119.wmv";
	if( true )
        capture = cvCaptureFromCAM( index );
    else if( false )
        capture = cvCaptureFromAVI( filename);

      
	//cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,0);
   
	if( capture ){
        SetReady(true);
    }else{
        SetReady(false);
		fprintf(stderr,"Could not initialize capturing...\n"); 
    } 
}

int MultiCamera::queryFrame(){
    frame = cvQueryFrame(capture);
    if( !frame )
      return 0;
    cvFlip(frame, frame, 1);
    frame->origin = 0;
    SetFrame(frame);
    
    return (capture) ? 1 : 0;
}

MultiCamera::MultiCamera() {
}

MultiCamera::MultiCamera(const MultiCamera& orig) {
}

MultiCamera::~MultiCamera() {

    if(CV_IS_IMAGE(frame)){
        cvReleaseImage(&frame);
    }
     
    cvReleaseCapture( &capture );
}
void MultiCamera::SetReady(bool ready) {
    this->ready = ready;
}
bool MultiCamera::IsReady() const {
    return ready;
}

void MultiCamera::SetFrameHeight(double frameHeight) {
    this->frameHeight = frameHeight;
}
double MultiCamera::GetFrameHeight() const {
    return cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
}
void MultiCamera::SetFrameWidth(double frameWidth) {
    this->frameWidth = frameWidth;
}
double MultiCamera::GetFrameWidth() const {
    return cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
}
double MultiCamera::GetFPS() const {
    return cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
}
void MultiCamera::SetFrame(IplImage* frame) {
    this->frame = frame;
}
IplImage* MultiCamera::GetFrame() const {
    return frame;
}

