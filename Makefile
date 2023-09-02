build:
	cc -std=c17 -o bin/hcvm main.c mac.c asm.c util.c

run: build
ifdef f
	bin/hcvm run $(f)
else
	@echo "no executable defined: pass a executable name to a 'ef' varaible."
	@echo "example: make run f=path/to/my/executable.hcvm"
endif

asm: build
ifdef f
ifdef d
	bin/hcvm asm -o $(d) $(f)
else
	bin/hcvm asm $(f)
endif
else
	@echo "no assembler file provided: pass a assembler file to a 'af' varaible."
	@echo "example: make asm f=path/to/my/file.asm"
endif
