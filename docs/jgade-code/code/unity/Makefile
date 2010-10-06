#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = BookCode_Unity

#--- Inputs ----#
UNITY_HOME = harness
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = ..
PROJECT_TEST_DIR = .
CPP_PLATFORM = Gcc

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/LedDriver \

TEST_SRC_DIRS = \
	.\
	$(PROJECT_TEST_DIR)/LedDriver\
	$(PROJECT_TEST_DIR)/stdio\
	$(UNITY_HOME)/src\
	$(UNITY_HOME)/tests\

MOCKS_SRC_DIRS = \
	$(PROJECT_TEST_DIR)/mocks\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/include\
  $(PROJECT_HOME_DIR)/include/LedDriver\
  $(PROJECT_HOME_DIR)/include/util\
  
include $(UNITY_HOME)/build/MakefileWorker.mk

