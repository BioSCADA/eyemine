#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Eyemine.o \
	${OBJECTDIR}/FaceDetect.o \
	${OBJECTDIR}/FaceHeuristics.o \
	${OBJECTDIR}/JavaStartInterface.o \
	${OBJECTDIR}/LeftContours.o \
	${OBJECTDIR}/LeftEyeDetect.o \
	${OBJECTDIR}/LeftEyeTrack.o \
	${OBJECTDIR}/MouthContours.o \
	${OBJECTDIR}/MouthDetect.o \
	${OBJECTDIR}/MouthTrack.o \
	${OBJECTDIR}/MultiCamera.o \
	${OBJECTDIR}/NoseDetect.o \
	${OBJECTDIR}/NoseTrack.o \
	${OBJECTDIR}/RightCamShift.o \
	${OBJECTDIR}/RightContours.o \
	${OBJECTDIR}/RightEyeDetect.o \
	${OBJECTDIR}/RightEyeTrack.o \
	${OBJECTDIR}/RightHough.o \
	${OBJECTDIR}/TrackerDetector.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib -L/usr/local/lib -lopencv_core -lopencv_ml -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_adas -lopencv_face -lopencv_bgsegm -lopencv_face -lopencv_datasets -lopencv_ccalib -lopencv_latentsvm -lopencv_optflow -lopencv_flann -lopencv_features2d -lopencv_objdetect -lopencv_photo -lopencv_text -lopencv_rgbd -lopencv_shape -lopencv_videostab

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eyemine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eyemine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eyemine ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Eyemine.o: Eyemine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Eyemine.o Eyemine.cpp

${OBJECTDIR}/FaceDetect.o: FaceDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FaceDetect.o FaceDetect.cpp

${OBJECTDIR}/FaceHeuristics.o: FaceHeuristics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FaceHeuristics.o FaceHeuristics.cpp

${OBJECTDIR}/JavaStartInterface.o: JavaStartInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/JavaStartInterface.o JavaStartInterface.cpp

${OBJECTDIR}/LeftContours.o: LeftContours.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LeftContours.o LeftContours.cpp

${OBJECTDIR}/LeftEyeDetect.o: LeftEyeDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LeftEyeDetect.o LeftEyeDetect.cpp

${OBJECTDIR}/LeftEyeTrack.o: LeftEyeTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LeftEyeTrack.o LeftEyeTrack.cpp

${OBJECTDIR}/MouthContours.o: MouthContours.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MouthContours.o MouthContours.cpp

${OBJECTDIR}/MouthDetect.o: MouthDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MouthDetect.o MouthDetect.cpp

${OBJECTDIR}/MouthTrack.o: MouthTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MouthTrack.o MouthTrack.cpp

${OBJECTDIR}/MultiCamera.o: MultiCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MultiCamera.o MultiCamera.cpp

${OBJECTDIR}/NoseDetect.o: NoseDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NoseDetect.o NoseDetect.cpp

${OBJECTDIR}/NoseTrack.o: NoseTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NoseTrack.o NoseTrack.cpp

${OBJECTDIR}/RightCamShift.o: RightCamShift.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RightCamShift.o RightCamShift.cpp

${OBJECTDIR}/RightContours.o: RightContours.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RightContours.o RightContours.cpp

${OBJECTDIR}/RightEyeDetect.o: RightEyeDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RightEyeDetect.o RightEyeDetect.cpp

${OBJECTDIR}/RightEyeTrack.o: RightEyeTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RightEyeTrack.o RightEyeTrack.cpp

${OBJECTDIR}/RightHough.o: RightHough.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RightHough.o RightHough.cpp

${OBJECTDIR}/TrackerDetector.o: TrackerDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/opencv -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TrackerDetector.o TrackerDetector.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eyemine

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
