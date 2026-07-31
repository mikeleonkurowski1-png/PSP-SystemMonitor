TARGET = PSP-SystemMonitor

PSPSDK := $(shell psp-config --pspsdk-path)

OBJS = src/main.o

CFLAGS = -O2 -G0 -Wall

BUILD_PRX = 1

LIBS = -lpspdebug -lpspdisplay -lpsppower -lpspctrl -lpspwlan -lpspaudio -lpspaudiocodec -lpspaudiolib -lpspnet -lpspnet_inet -lpspnet_apctl	

EXTRA_TARGETS = EBOOT.PBP

PSP_EBOOT_TITLE = PSP-SystemMonitor

include $(PSPSDK)/lib/build.mak