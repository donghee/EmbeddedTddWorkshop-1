#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = SandBox_Unity

#--- Inputs ----#
PROJECT_HOME_DIR = ..
UNITY_HOME = ../../unity/harness
CPP_PLATFORM = Gcc

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/LedDriver \

TEST_SRC_DIRS = \
	.\
	LedDriver\
	$(UNITY_HOME)/src\
	$(UNITY_HOME)/tests\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/include\
  $(PROJECT_HOME_DIR)/include/LedDriver\

include $(UNITY_HOME)/build/MakefileWorker.mk
