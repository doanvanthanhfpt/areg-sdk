14_pubclient_PROJECT_NAME := 14_pubclient

14_pubclient_TARGET_BIN := $(14_pubclient_PROJECT_NAME)$(AREG_BIN_EXT)
14_pubclient_OUTPUT_OBJ := $(14_pubtraffic_OUTPUT_OBJ)/$(14_pubclient_PROJECT_NAME)

14_pubclient_SRC  :=
14_pubclient_OBJS :=

include $(14_pubtraffic_BASE)/pubclient/src/Makefile

# define one target for each source file
$(foreach cpp, $(14_pubclient_SRC), $(eval $(call obj, $(cpp), $(14_pubclient_OUTPUT_OBJ), 14_pubclient_OBJS, $(14_pubtraffic_CXXFLAGS))))

DEPS = $(14_pubclient_OBJS:%.o=%.d)
-include $(DEPS)

$(AREG_OUTPUT_BIN)/$(14_pubclient_TARGET_BIN): $(areg_TARGET_PATH) $(AREG_OUTPUT_LIB)/$(14_generated_TARGET_BIN) $(14_pubclient_OBJS)
	@echo "Linking $@ ..."
	@mkdir -p $(dir $@)
	$(AREG_TOOLCHAIN) $(CXXFLAGS) $(14_pubtraffic_CXXFLAGS) $(14_pubclient_OBJS) $(14_pubtraffic_LDFLAGS) -o $@
