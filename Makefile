OBJDIR		=	obj
SRCDIR		=	src
OBJ			=	$(addprefix $(OBJDIR)/, $(patsubst $(SRCDIR)/%.cpp, %.o, $(wildcard $(SRCDIR)/*.cpp)))
HDR			=	$(SRCDIR)/*.hpp
TARGET		=	best_tanks
GCC			=	g++
CPPFLAGS	=	-std=gnu++14 -Wall -Wextra -lncurses

.PHONY: all clean

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(GCC) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJ) $(HDR)
	$(GCC) $(CPPFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(wildcard *.o)
	rm -rf $(OBJDIR)

re: clean all