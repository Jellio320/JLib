PROJECT := JLib
SRCDIR = Src
OBJDIR = Int
OUTDIR = Bin
CC := gcc
CFLAGS := -std=c99 -g -Wall -Wextra -Wcast-align -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wundef -fmessage-length=0

OBJS := $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(wildcard $(SRCDIR)/*.c))

deps := $(patsubst, %.o, %.d, $(OBJS))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

.PHONY: dirs clean

all: dirs $(OUTDIR)/$(PROJECT).a

$(OUTDIR)/$(PROJECT).a: $(OBJS)
	gcc-ar rcs $(OUTDIR)/$(PROJECT).a $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@ $(DEPFLAGS)


MKDIR := mkdir -p

dirs: $(OBJDIR) $(OUTDIR)

$(OBJDIR):
	$(MKDIR) $@

$(OUTDIR):
	$(MKDIR) $@


clean: 
	rm -f $(OBJDIR)/*_e.c $(OBJDIR)/*.s $(OBJDIR)/*.o $(OUTDIR)/$(PROJECT).a