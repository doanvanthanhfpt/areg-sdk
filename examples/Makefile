ifeq ($(AREG_BINARY), shared)
	examples_CXXFLAGS += -DIMP_AREG_DLL
	examples_LDFLAGS  += -Wl,-rpath=$(AREG_OUTPUT_BIN) -L $(AREG_OUTPUT_BIN) -lareg $(LDFLAGS)
else
	examples_CXXFLAGS += -DIMP_AREG_LIB
	examples_LDFLAGS  += -L $(AREG_OUTPUT_LIB) -Wl,-Bstatic -lareg -Wl,-Bdynamic $(LDFLAGS)
endif

include $(AREG_EXAMPLES)/00_helloservice/Makefile
include $(AREG_EXAMPLES)/01_hello/Makefile
include $(AREG_EXAMPLES)/02_buffer/Makefile
include $(AREG_EXAMPLES)/03_file/Makefile
include $(AREG_EXAMPLES)/04_trace/Makefile
include $(AREG_EXAMPLES)/05_timer/Makefile
include $(AREG_EXAMPLES)/06_threads/Makefile
include $(AREG_EXAMPLES)/07_synch/Makefile
include $(AREG_EXAMPLES)/08_service/Makefile
include $(AREG_EXAMPLES)/09_svcmulti/Makefile
include $(AREG_EXAMPLES)/10_locsvc/Makefile
include $(AREG_EXAMPLES)/11_locmesh/Makefile
include $(AREG_EXAMPLES)/12_pubsvc/Makefile
include $(AREG_EXAMPLES)/13_pubmesh/Makefile
include $(AREG_EXAMPLES)/14_pubtraffic/Makefile
include $(AREG_EXAMPLES)/15_pubworker/Makefile
include $(AREG_EXAMPLES)/16_pubfsm/Makefile

examples: 00_helloservice 01_hello 02_buffer 03_file 04_trace \
    05_timer 06_threads 07_synch 08_service 09_svcmulti \
    10_locsvc 11_locmesh 12_pubsvc 13_pubmesh \
    14_pubtraffic 15_pubworker 16_pubfsm

.PHONY: examples
