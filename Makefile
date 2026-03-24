# Makefile for Anarch
#
# Usage:
#	To build:	make <platform> build
#	To clean:	make <platform> clean	
#	To rebuild:	make <platform> rebuild

PORTS = test mingw
PLATFORM_MAKE = ports/$(PLATFORM)/Makefile

.PHONY: $(PORTS) all build clean rebuild

help:
	@echo "To build anarch use 'make PLATFORM build'."
	@echo "To clean anarch use 'make PLATFORM clean'."
	@echo "To clean, then build anarch use 'make PLATFORM rebuild'."
	@echo "Valid platforms are: $(PORTS)"

$(PORTS):
	$(eval export PLATFORM=$@)
	@echo "Platform: $@ (type 'make help' for help)"

build:
	$(MAKE) -f $(PLATFORM_MAKE) all

clean:
	$(MAKE) -f $(PLATFORM_MAKE) clean

rebuild:
	$(MAKE) -f $(PLATFORM_MAKE) clean all
