TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord

# Install xxxSupport.dbd into <top>/dbd
DBD += xxxSupport.dbd

# Build an IOC support library
LIBRARY_IOC += rcsRfCalcSupport

# Compile and add the code to the support library
rcsRfCalcSupport_SRCS += xxxRecord.c
rcsRfCalcSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
# This is required for Windows DLL builds.
rcsRfCalcSupport_SRCS += dbSubExample.c
rcsRfCalcSupport_SRCS += rcsRfCalcHello.c
rcsRfCalcSupport_SRCS += initTrace.c

rcsRfCalcSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

# Build the IOC application
PROD_IOC = rcsRfCalc

# rcsRfCalc.dbd will be created and installed
DBD += rcsRfCalc.dbd

# rcsRfCalc.dbd will include these files:
rcsRfCalc_DBD += base.dbd
rcsRfCalc_DBD += xxxSupport.dbd
rcsRfCalc_DBD += dbSubExample.dbd
rcsRfCalc_DBD += rcsRfCalcHello.dbd
rcsRfCalc_DBD += initTrace.dbd

# rcsRfCalc_registerRecordDeviceDriver.cpp derives from rcsRfCalc.dbd
rcsRfCalc_SRCS += rcsRfCalc_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
rcsRfCalc_SRCS_DEFAULT += rcsRfCalcMain.cpp
rcsRfCalc_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#rcsRfCalc_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Link in the code from our support library
rcsRfCalc_LIBS += rcsRfCalcSupport

# To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file
ifneq ($(SNCSEQ),)
    # Build sncExample into rcsRfCalcSupport
    sncExample_SNCFLAGS += +r
    rcsRfCalc_DBD += sncExample.dbd
    rcsRfCalcSupport_SRCS += sncExample.stt
    rcsRfCalcSupport_LIBS += seq pv
    rcsRfCalc_LIBS += seq pv

    # Build sncProgram as a standalone program
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

# Finally link IOC to the EPICS Base libraries
rcsRfCalc_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE

