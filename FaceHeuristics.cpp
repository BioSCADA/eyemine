/* 
 * File:   FaceHeuristics.cpp
 * Author: diego
 * 
 * Created on June 4, 2010, 4:53 PM
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
//                  For Open Source Biosignal SCADA
//
// Copyright (C) 2010, Laboratorio de Educacao Cerebral, all rights reserved.
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
 
#include "IOGlobals.h"
#include "FaceHeuristics.h"
#include <math.h>


void FaceHeuristics::calcRefAngleEyes(){
    double deltaX = 0;
    double deltaY = 0;
    deltaX = GetRefPointRightEye().x - GetRefPointLeftEye().x;
    deltaY = GetRefPointRightEye().y - GetRefPointLeftEye().y;
    SetERefDistanceEye(sqrt(pow(deltaX,2)+pow(deltaY,2)));
    SetRefAngleEyes(atan2(deltaX,deltaY)*180/PI);
    SetEMaxDistanceEye(GetERefDistanceEye() + 1*EYE_TPL_WIDTH);
    SetEMinDistanceEye(GetERefDistanceEye() - 1*EYE_TPL_WIDTH);

}

void FaceHeuristics::calcTrackAngleEyes(){
    double deltaX = 0;
    double deltaY = 0;
    deltaX = GetTrackPointRightEye().x - GetTrackPointLeftEye().x;
    deltaY = GetTrackPointRightEye().y - GetTrackPointLeftEye().y;
    SetETrackDistanceEye(sqrt(pow(deltaX,2)+pow(deltaY,2)));
    SetTrackAngleEyes(atan2(deltaX,deltaY)*180/PI );
}

void FaceHeuristics::verifyDistances(){

    calcRefAngleEyes();
    calcTrackAngleEyes();

    int refNoseX = 0;
    int refNoseY = 0;
    refNoseX = GetTrackPointNose().x - GetRefPointNose().x;
    refNoseY = GetTrackPointNose().y - GetRefPointNose().y;

    int pointRightX = 0;
    int pointRightY = 0;
    pointRightX = GetTrackPointRightEye().x - GetRefPointRightEye().x;
    pointRightY = GetTrackPointRightEye().y - GetRefPointRightEye().y;



    FaceHeuristics::GazeRightX = pointRightX - refNoseX;
    FaceHeuristics::GazeRightY = -1*(pointRightY - refNoseY);

    SetERightGaze(sqrt(pow((double)FaceHeuristics::GazeRightX,2)+pow((double)FaceHeuristics::GazeRightY,2)));
    //heuristica para piscadas

    if(abs((int)GetEPrevRightGaze()-(int)GetERightGaze()) >= 5){        
        FaceHeuristics::GazeRightBlink += 1;
    }else{
         
    }

    SetEPrevRightGaze(sqrt(pow((double)FaceHeuristics::GazeRightX,2)+pow((double)FaceHeuristics::GazeRightY,2)));
    
    int pointLeftX = 0;
    int pointLeftY = 0;
    pointLeftX = GetTrackPointLeftEye().x - GetRefPointLeftEye().x;
    pointLeftY = GetTrackPointLeftEye().y - GetRefPointLeftEye().y;

    
    FaceHeuristics::GazeLeftX = pointLeftX - refNoseX;
    FaceHeuristics::GazeLeftY = -1*(pointLeftY - refNoseY);

    SetELeftGaze(sqrt((double)pow((double)FaceHeuristics::GazeLeftX,2)+pow((double)FaceHeuristics::GazeLeftY,2)));
    if(abs((int)GetEPrevLeftGaze()-(int)GetELeftGaze()) >= 5){
        FaceHeuristics::GazeLeftBlink += 1;
    }else{
        
    }
    SetEPrevLeftGaze(sqrt((double)pow((double)FaceHeuristics::GazeLeftX,2)+pow((double)FaceHeuristics::GazeLeftY,2)));

    
    if(GetTrackAngleEyes() > 60 && GetTrackAngleEyes() < 120 && GetETrackDistanceEye() > GetEMinDistanceEye() && GetETrackDistanceEye() < GetEMaxDistanceEye()){
        SetEyes(true);
    }else{
        SetEyes(false);
    }
    if(GetTrackPointNose().x < GetTrackPointRightEye().x && GetTrackPointNose().x > GetTrackPointLeftEye().x && GetTrackPointNose().y > GetTrackPointRightEye().y && GetTrackPointNose().y > GetTrackPointLeftEye().y){
        SetNose(true);
    }else{
        SetNose(false);
    }
    if(GetTrackPointMouth().x < GetTrackPointRightEye().x && GetTrackPointMouth().x > GetTrackPointLeftEye().x && GetTrackPointMouth().y > GetTrackPointRightEye().y && GetTrackPointMouth().y > GetTrackPointLeftEye().y){
        SetMouth(true);
    }else{
        SetMouth(false);
    }
   
   //get timestamp na marra
    time_t ltime;
    struct tm *Tm;
     
    ltime=time(NULL);
    Tm=localtime(&ltime);
 
    FaceHeuristics::GazeHH = Tm->tm_hour;
    FaceHeuristics::GazeMM = Tm->tm_min;
    FaceHeuristics::GazeSS = Tm->tm_sec;
}
 

FaceHeuristics::FaceHeuristics() {
    
}

FaceHeuristics::FaceHeuristics(const FaceHeuristics& orig) {

}

FaceHeuristics::~FaceHeuristics() {
     
}
 
 
void FaceHeuristics::SetTrackPointMouth(CvPoint trackPointMouth) {
    this->trackPointMouth = trackPointMouth;
}
CvPoint FaceHeuristics::GetTrackPointMouth() const {
    return trackPointMouth;
}
void FaceHeuristics::SetTrackPointNose(CvPoint trackPointNose) {
    this->trackPointNose = trackPointNose;
}
CvPoint FaceHeuristics::GetTrackPointNose() const {
    return trackPointNose;
}
void FaceHeuristics::SetTrackPointRightEye(CvPoint trackPointRightEye) {
    this->trackPointRightEye = trackPointRightEye;
}
CvPoint FaceHeuristics::GetTrackPointRightEye() const {
    return trackPointRightEye;
}
void FaceHeuristics::SetTrackPointLeftEye(CvPoint trackPointLeftEye) {
    this->trackPointLeftEye = trackPointLeftEye;
}
CvPoint FaceHeuristics::GetTrackPointLeftEye() const {
    return trackPointLeftEye;
}
void FaceHeuristics::SetRefPointMouth(CvPoint refPointMouth) {
    this->refPointMouth = refPointMouth;
}
CvPoint FaceHeuristics::GetRefPointMouth() const {
    return refPointMouth;
}
void FaceHeuristics::SetRefPointNose(CvPoint refPointNose) {
    this->refPointNose = refPointNose;
}
CvPoint FaceHeuristics::GetRefPointNose() const {
    return refPointNose;
}
void FaceHeuristics::SetRefPointRightEye(CvPoint refPointRightEye) {
    this->refPointRightEye = refPointRightEye;
}
CvPoint FaceHeuristics::GetRefPointRightEye() const {
    return refPointRightEye;
}
void FaceHeuristics::SetRefPointLeftEye(CvPoint refPointLeftEye) {
    this->refPointLeftEye = refPointLeftEye;
}
CvPoint FaceHeuristics::GetRefPointLeftEye() const {
    return refPointLeftEye;
}
void FaceHeuristics::SetNose(bool nose) {
    this->nose = nose;
}
bool FaceHeuristics::IsNose() const {
    return nose;
}
void FaceHeuristics::SetEyes(bool eyes) {
    this->eyes = eyes;
}
bool FaceHeuristics::IsEyes() const {
    return eyes;
}
void FaceHeuristics::SetRefAngleEyes(double refAngleEyes) {
    this->refAngleEyes = refAngleEyes;
}
double FaceHeuristics::GetRefAngleEyes() const {
    return refAngleEyes;
}
void FaceHeuristics::SetTrackAngleEyes(double trackAngleEyes) {
    this->trackAngleEyes = trackAngleEyes;
}
double FaceHeuristics::GetTrackAngleEyes() const {
    return trackAngleEyes;
}
void FaceHeuristics::SetETrackDistanceMouth(double eTrackDistanceMouth) {
    this->eTrackDistanceMouth = eTrackDistanceMouth;
}
double FaceHeuristics::GetETrackDistanceMouth() const {
    return eTrackDistanceMouth;
}
void FaceHeuristics::SetETrackDistanceNose(double eTrackDistanceNose) {
    this->eTrackDistanceNose = eTrackDistanceNose;
}
double FaceHeuristics::GetETrackDistanceNose() const {
    return eTrackDistanceNose;
}
void FaceHeuristics::SetETrackDistanceEye(double eTrackDistanceEye) {
    this->eTrackDistanceEye = eTrackDistanceEye;
}
double FaceHeuristics::GetETrackDistanceEye() const {
    return eTrackDistanceEye;
}
void FaceHeuristics::SetERefDistanceMouth(double eRefDistanceMouth) {
    this->eRefDistanceMouth = eRefDistanceMouth;
}
double FaceHeuristics::GetERefDistanceMouth() const {
    return eRefDistanceMouth;
}
void FaceHeuristics::SetERefDistanceNose(double eRefDistanceNose) {
    this->eRefDistanceNose = eRefDistanceNose;
}
double FaceHeuristics::GetERefDistanceNose() const {
    return eRefDistanceNose;
}
void FaceHeuristics::SetERefDistanceEye(double eRefDistanceEye) {
    this->eRefDistanceEye = eRefDistanceEye;
}
double FaceHeuristics::GetERefDistanceEye() const {
    return eRefDistanceEye;
}
void FaceHeuristics::SetEMaxDistanceEye(double eMaxDistanceEye) {
    this->eMaxDistanceEye = eMaxDistanceEye;
}
double FaceHeuristics::GetEMaxDistanceEye() const {
    return eMaxDistanceEye;
}
void FaceHeuristics::SetEMinDistanceEye(double eMinDistanceEye) {
    this->eMinDistanceEye = eMinDistanceEye;
}
double FaceHeuristics::GetEMinDistanceEye() const {
    return eMinDistanceEye;
}
void FaceHeuristics::SetMouth(bool mouth) {
    this->mouth = mouth;
}
bool FaceHeuristics::IsMouth() const {
    return mouth;
}
void FaceHeuristics::SetEPrevRightGaze(double ePrevRightGaze) {
    this->ePrevRightGaze = ePrevRightGaze;
}
double FaceHeuristics::GetEPrevRightGaze() const {
    return ePrevRightGaze;
}
void FaceHeuristics::SetEPrevLeftGaze(double ePrevLeftGaze) {
    this->ePrevLeftGaze = ePrevLeftGaze;
}
double FaceHeuristics::GetEPrevLeftGaze() const {
    return ePrevLeftGaze;
}
void FaceHeuristics::SetERightGaze(double eRightGaze) {
    this->eRightGaze = eRightGaze;
}
double FaceHeuristics::GetERightGaze() const {
    return eRightGaze;
}
void FaceHeuristics::SetELeftGaze(double eLeftGaze) {
    this->eLeftGaze = eLeftGaze;
}
double FaceHeuristics::GetELeftGaze() const {
    return eLeftGaze;
}
 
int FaceHeuristics::GazeLeftX = 0;
int FaceHeuristics::GazeLeftY = 0;
int FaceHeuristics::GazeLeftBlink = 0;
int FaceHeuristics::GazeRightX = 0;
int FaceHeuristics::GazeRightY = 0;
int FaceHeuristics::GazeRightBlink = 0;
int FaceHeuristics::GazeHH = 0;
int FaceHeuristics::GazeMM = 0;
int FaceHeuristics::GazeSS = 0;
