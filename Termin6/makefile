# Vorschlag eines Makefile zu Termin5 SS2011
# Quelldatei
FILE = Termin6Aufgabe1
# Toolchain
TOOLCHAIN = arm-elf
# Compiler
COMPILER = gcc
# Linker/Binder
LINKER = ld
# Pfad zur libgcc.a
# fuer Virtuell_RA_MPS_WS2020
LIBGCC = /opt/mpstools/lib/gcc/arm-v4t-eabi/4.4.5/libgcc.a
# Debugger
DEBUGGER = insight
# Optimierungsstufe
OPTI = 0

# Bauen
all:
# uebersetzen der Quelldatei
	$(TOOLCHAIN)-$(COMPILER) -c -g -O$(OPTI) $(FILE).c -I ../h

# Erzeugen der Assemblerdateien aus den Quelldateien	
	$(TOOLCHAIN)-$(COMPILER) -S -O$(OPTI) $(FILE).c -I ../h

# Erzeugen der benoetitgen Objektdateien
# eigener SoftWareInterrupt-Handler
	$(TOOLCHAIN)-$(COMPILER) -c -g -O$(OPTI) ../boot/swi.S -o swi.o -I ../h
	$(TOOLCHAIN)-$(COMPILER) -c -g -O$(OPTI) ../boot/boot_ice.S -o boot_ice.o -I ../h
	
# Binden fuer die RAM-Version 
	$(TOOLCHAIN)-$(LINKER) -Ttext 0x02000000 -O$(OPTI) boot_ice.o swi.o $(FILE).o -o $(FILE).elf $(LIBGCC)

# Debugger starten
debug:
	$(TOOLCHAIN)-$(DEBUGGER) $(FILE).elf

# Aufraeumen
clean:
	rm -f *.o
	rm -f *.s
	rm -f *.elf
	rm -f *.rom

# BDI2000 zuruecksetzen
bdireset:
	bash bdi_reset


