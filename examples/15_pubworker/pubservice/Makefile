15_pubservice_PROJECT_NAME := 15_pubservice

15_pubservice_TARGET_BIN := $(15_pubservice_PROJECT_NAME)$(AREG_BIN_EXT)
15_pubservice_OUTPUT_OBJ := $(15_pubworker_OUTPUT_OBJ)/$(15_pubservice_PROJECT_NAME)

15_pubservice_SRC  :=
15_pubservice_OBJS :=

include $(15_pubworker_BASE)/pubservice/src/Makefile

# define one target for each source file
$(foreach cpp, $(15_pubservice_SRC), $(eval $(call obj, $(cpp), $(15_pubservice_OUTPUT_OBJ), 15_pubservice_OBJS, $(15_pubworker_CXXFLAGS))))

DEPS = $(15_pubservice_OBJS:%.o=%.d)
-include $(DEPS)

$(AREG_OUTPUT_BIN)/$(15_pubservice_TARGET_BIN): $(areg_TARGET_PATH) $(AREG_OUTPUT_LIB)/$(15_generated_TARGET_BIN) $(15_pubservice_OBJS)
	@echo "Linking $@ ..."
	@mkdir -p $(dir $@)
	$(AREG_TOOLCHAIN) $(CXXFLAGS) $(15_pubworker_CXXFLAGS) $(15_pubservice_OBJS) $(15_pubworker_LDFLAGS) -o $@
