# Variables

PROGRAM := fractals
ifeq ($(OS), Windows_NT)
	PROGRAM := $(PROGRAM).exe
endif

SHADER_COMPILER := glslc

COMPILER := clang++

SOURCE_TYPE := .cpp
HEADER_TYPE := .hpp
OBJECT_TYPE := .o

SHADER_FLAGS := -O

STANDARD := -std=c++26
OPTIMIZE := -O1

IGNORED := -Wno-c23-extensions -Wno-cast-function-type-strict -Wno-covered-switch-default -Wno-disabled-macro-expansion -Wno-padded -Wno-reserved-identifier -Wno-switch-default -Wno-unsafe-buffer-usage
IGNORED_C := -Wno-declaration-after-statement
IGNORED_CPP := -Wno-c++98-compat-pedantic -Wno-old-style-cast

ifeq ($(COMPILER), clang)
	WARNINGS := -Weverything $(IGNORED) $(IGNORED_C)
else ifeq ($(COMPILER), clang++)
	WARNINGS := -Weverything $(IGNORED) $(IGNORED_CPP)
else ifeq ($(COMPILER), gcc)
	WARNINGS := -Wall $(IGNORED) $(IGNORED_C)
else ifeq ($(COMPILER), g++)
	WARNINGS := -Wall $(IGNORED) $(IGNORED_CPP)
endif

COMPILE_FLAGS := $(STANDARD) $(OPTIMIZE) $(WARNINGS) -isystem include

ifeq ($(OS), Windows_NT)
	NO_CONSOLE := -Wl,/subsystem:windows,/entry:mainCRTStartup
	LINK_FLAGS := -lgdi32 -lglu32 -lopengl32 -luser32 -fuse-ld=lld -Wl,/manifest:embed -Wl,/manifestinput:res/windows.xml
else
# 	LINK_FLAGS := -Wl,-s -lX11 -lxcb -lXau -lXdmcp -static
	LINK_FLAGS := -Wl,-s -lX11 -lGL
endif

DEBUG_SYMBOLS := 0
ifeq ($(DEBUG_SYMBOLS), 1)
	LINK_FLAGS := $(LINK_FLAGS) -g
endif

SHADER_SOURCE_FOLDER := src/shaders

SOURCE_FOLDER := src
OUTPUT_FOLDER := out

ifeq ($(OS), Windows_NT)
	SHADER_OUTPUT_FOLDER_MKDIR := $(OUTPUT_FOLDER)\shaders
	SHADER_OUTPUT_FOLDER := $(OUTPUT_FOLDER)/shaders
	OUTPUT_FOLDER_MKDIR := $(OUTPUT_FOLDER)\win
	OUTPUT_FOLDER := $(OUTPUT_FOLDER)/win
else
	SHADER_OUTPUT_FOLDER_MKDIR := $(OUTPUT_FOLDER)/shaders
	SHADER_OUTPUT_FOLDER := $(OUTPUT_FOLDER)/shaders
	OUTPUT_FOLDER_MKDIR := $(OUTPUT_FOLDER)/lin
	OUTPUT_FOLDER := $(OUTPUT_FOLDER)/lin
endif

CLEAN_FOLDERS := $(OUTPUT_FOLDER)

ECHO_NEW_LINE := echo
CLEAN_COMMAND := rm -rf $(CLEAN_FOLDERS)
MKDIR_COMMAND := mkdir -p

ifeq ($(OS), Windows_NT)
	ECHO_NEW_LINE := set _= && echo.
	CLEAN_COMMAND := rmdir /S /Q $(CLEAN_FOLDERS) 1>NUL 2>NUL || set _=
	MKDIR_COMMAND := mkdir
endif

SHADER_SOURCES := $(wildcard $(SHADER_SOURCE_FOLDER)/*.vert $(SHADER_SOURCE_FOLDER)/*.tesc $(SHADER_SOURCE_FOLDER)/*.tese $(SHADER_SOURCE_FOLDER)/*.geom $(SHADER_SOURCE_FOLDER)/*.frag $(SHADER_SOURCE_FOLDER)/*.comp)
SHADER_OBJECTS := $(patsubst $(SHADER_SOURCE_FOLDER)/%,$(SHADER_OUTPUT_FOLDER)/%.spv,$(SHADER_SOURCES))

ifeq ($(OS), Windows_NT)
	SOURCE_FILTER := _lin$(SOURCE_TYPE)
else
	SOURCE_FILTER := _win$(SOURCE_TYPE)
endif

SOURCES := $(filter-out %$(SOURCE_FILTER),$(wildcard $(SOURCE_FOLDER)/*$(SOURCE_TYPE)))
HEADERS := $(wildcard $(SOURCE_FOLDER)/*$(HEADER_TYPE))
OBJECTS := $(patsubst $(SOURCE_FOLDER)/%$(SOURCE_TYPE),$(OUTPUT_FOLDER)/%$(OBJECT_TYPE),$(SOURCES))
PROGRAM := $(OUTPUT_FOLDER)/$(PROGRAM)


# Targets


$(PROGRAM): $(OBJECTS) | $(OUTPUT_FOLDER)
	$(COMPILER) -o $(PROGRAM) $(OBJECTS) $(LINK_FLAGS)

$(SHADER_OUTPUT_FOLDER)/%.spv: $(SHADER_SOURCE_FOLDER)/% | $(SHADER_OUTPUT_FOLDER)
	$(SHADER_COMPILER) -o $@ -c $< $(SHADER_FLAGS)

$(OUTPUT_FOLDER)/%$(OBJECT_TYPE): $(SOURCE_FOLDER)/%$(SOURCE_TYPE) $(HEADERS) $(SHADER_OBJECTS) | $(OUTPUT_FOLDER)
	$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS)

$(SHADER_OUTPUT_FOLDER):
	$(MKDIR_COMMAND) $(SHADER_OUTPUT_FOLDER_MKDIR)

$(OUTPUT_FOLDER):
	$(MKDIR_COMMAND) $(OUTPUT_FOLDER_MKDIR)


# Commands


clean:
	$(CLEAN_COMMAND)

help:
	@$(ECHO_NEW_LINE)
	@echo make
	@echo     Compile the program
	@$(ECHO_NEW_LINE)
	@echo make clean
	@echo     Remove the obj and bin folders
	@$(ECHO_NEW_LINE)
	@echo make help
	@echo     Get help with the Makefile
	@$(ECHO_NEW_LINE)
	@echo make run
	@echo     Compile the program and run it
	@$(ECHO_NEW_LINE)

run: $(PROGRAM)
	@$(ECHO_NEW_LINE)
	@echo $(PROGRAM)
	@$(ECHO_NEW_LINE)
	@$(PROGRAM)
