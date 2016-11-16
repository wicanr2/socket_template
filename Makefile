ECHO ?= @echo -e
MAKE = @make
CP ?= @cp
MKDIR ?= @mkdir
RM = @rm
MV ?= @mv
TAR ?= @tar
CAT ?= @cat
SED ?= @sed
DATE ?= @date
CHMOD ?= @chmod
TABS ?= @tabs
CD ?= @cd

#Color
BLACK=\033[0;30m     
DARK_GRAY=\033[1;30m
RED=\033[0;31m     
LIGHT_RED=\033[1;31m
GREEN=\033[0;32m     
LIGHT_GREEN=\033[1;32m
ORANGE=\033[0;33m     
YELLOW=\033[1;33m
BLUE=\033[0;34m
LIGHT_BLUE=\033[1;34m
PURPLE=\033[0;35m     
LIGHT_PURPLE=\033[1;35m
CYAN=\033[0;36m     
LIGHT_CYAN=\033[1;36m
LIGHT_GRAY=\033[0;37m    
WHITE=\033[1;37m
NC=\033[0m

all:
	$(ECHO) "$(WHITE)==== Start Building ====$(NC)"
	$(ECHO) "$(GREEN)\tBuild ipv6 sample$(NC)\n"
	$(MAKE) -C ipv6 > /dev/null
	$(ECHO) "$(GREEN)\tBuild ipv4 sample$(NC)\n"
	$(MAKE) -C ipv4 > /dev/null
	$(ECHO) "$(GREEN)\tBuild udp_multicast$(NC)\n"
	$(MAKE) -C udp_multicast > /dev/null
	$(ECHO) "$(GREEN)\tBuild utee$(NC)\n"
	$(MAKE) -C utee > /dev/null
	$(ECHO) "$(WHITE)==== Build Successful ====$(NC)\n"

clean:
	$(ECHO) "$(WHITE)==== Start Clean ====$(NC)"
	$(MAKE) clean -C ipv6 > /dev/null
	$(MAKE) clean -C ipv4 > /dev/null
	$(MAKE) clean -C udp_multicast > /dev/null
	$(MAKE) clean -C utee > /dev/null
	$(ECHO) "$(WHITE)==== Finish Clean ====$(NC)\n"
