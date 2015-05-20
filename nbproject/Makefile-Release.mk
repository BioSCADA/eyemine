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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/Eyemine.o \
	${OBJECTDIR}/source/FaceDetect.o \
	${OBJECTDIR}/source/FaceHeuristics.o \
	${OBJECTDIR}/source/JavaStartInterface.o \
	${OBJECTDIR}/source/LeftContours.o \
	${OBJECTDIR}/source/LeftEyeDetect.o \
	${OBJECTDIR}/source/LeftEyeTrack.o \
	${OBJECTDIR}/source/MouthContours.o \
	${OBJECTDIR}/source/MouthDetect.o \
	${OBJECTDIR}/source/MouthTrack.o \
	${OBJECTDIR}/source/MultiCamera.o \
	${OBJECTDIR}/source/NoseDetect.o \
	${OBJECTDIR}/source/NoseTrack.o \
	${OBJECTDIR}/source/RightCamShift.o \
	${OBJECTDIR}/source/RightContours.o \
	${OBJECTDIR}/source/RightEyeDetect.o \
	${OBJECTDIR}/source/RightEyeTrack.o \
	${OBJECTDIR}/source/RightHough.o \
	${OBJECTDIR}/source/TrackerDetector.o


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
LDLIBSOPTIONS=-L/usr/lib -L/usr/local/lib `pkg-config --libs opencv`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libEyemine.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libEyemine.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libEyemine.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/source/Eyemine.o: source/Eyemine.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/Eyemine.o source/Eyemine.cpp

${OBJECTDIR}/source/FaceDetect.o: source/FaceDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/FaceDetect.o source/FaceDetect.cpp

${OBJECTDIR}/source/FaceHeuristics.o: source/FaceHeuristics.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/FaceHeuristics.o source/FaceHeuristics.cpp

${OBJECTDIR}/source/JavaStartInterface.o: source/JavaStartInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/JavaStartInterface.o source/JavaStartInterface.cpp

${OBJECTDIR}/source/LeftContours.o: source/LeftContours.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/LeftContours.o source/LeftContours.cpp

${OBJECTDIR}/source/LeftEyeDetect.o: source/LeftEyeDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/LeftEyeDetect.o source/LeftEyeDetect.cpp

${OBJECTDIR}/source/LeftEyeTrack.o: source/LeftEyeTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/LeftEyeTrack.o source/LeftEyeTrack.cpp

${OBJECTDIR}/source/MouthContours.o: source/MouthContours.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/MouthContours.o source/MouthContours.cpp

${OBJECTDIR}/source/MouthDetect.o: source/MouthDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/MouthDetect.o source/MouthDetect.cpp

${OBJECTDIR}/source/MouthTrack.o: source/MouthTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/MouthTrack.o source/MouthTrack.cpp

${OBJECTDIR}/source/MultiCamera.o: source/MultiCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/MultiCamera.o source/MultiCamera.cpp

${OBJECTDIR}/source/NoseDetect.o: source/NoseDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/NoseDetect.o source/NoseDetect.cpp

${OBJECTDIR}/source/NoseTrack.o: source/NoseTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/NoseTrack.o source/NoseTrack.cpp

${OBJECTDIR}/source/RightCamShift.o: source/RightCamShift.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/RightCamShift.o source/RightCamShift.cpp

${OBJECTDIR}/source/RightContours.o: source/RightContours.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/RightContours.o source/RightContours.cpp

${OBJECTDIR}/source/RightEyeDetect.o: source/RightEyeDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/RightEyeDetect.o source/RightEyeDetect.cpp

${OBJECTDIR}/source/RightEyeTrack.o: source/RightEyeTrack.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/RightEyeTrack.o source/RightEyeTrack.cpp

${OBJECTDIR}/source/RightHough.o: source/RightHough.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/RightHough.o source/RightHough.cpp

${OBJECTDIR}/source/TrackerDetector.o: source/TrackerDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/opencv -Iheader `pkg-config --cflags opencv`   -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/TrackerDetector.o source/TrackerDetector.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libEyemine.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
