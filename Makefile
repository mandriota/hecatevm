build:
	cc -std=c17 -o bin/hcvm main.c util.c mac.c

run: build
ifdef ef
	bin/hcvm $(ef)
else
	@echo "no executable defined: pass a executable name to a 'ef' varaible."
	@echo "example: make run ef=path/to/my/executable.bin"
endif
