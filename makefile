CXX      = g++
MAIN     = main

DLL_NAME   = JDMC
DLL_SPRITE = JDMCSprite
DLL_CONS   = JDMCApplication
ALL_DLL    = -l$(DLL_NAME) -l$(DLL_CONS) -l$(DLL_SPRITE)

DLL_DIR = Build
BIN_DIR = Build

I1 = -IJDMC
I2 = -IJDMC/Headers
INCLUDE = $(I1) $(I2)

SRC_DIR  = JDMC/Source
OBJ_DIR  = JDMC/Object

SRC_DIRS = $(SRC_DIR) 
SOURCES  = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS  = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

SPRITE_SRC      = $(SRC_DIR)/Sprites
SPRITE_SOURCES  = $(foreach dir, $(SPRITE_SRC), $(wildcard $(dir)/*.cpp))
SPRITE_OBJECTS  = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SPRITE_SOURCES))

CONSOLE_DIR  = ConsoleApplication
CONSOLE_DIR  = ConsoleApplication

CONSOLE    = $(CONSOLE_DIR) 
C_SOURCES  = $(foreach dir, $(CONSOLE), $(wildcard $(dir)/*.cpp))
C_OBJECTS  = $(patsubst $(CONSOLE_DIR)/%.cpp, $(CONSOLE_DIR)/%.o, $(C_SOURCES))

JDMC_DLL        = $(DLL_DIR)/$(DLL_NAME).dll
JDMC_SPRITE_DLL = $(DLL_DIR)/$(DLL_SPRITE).dll
CONSOLE_DLL     = $(DLL_DIR)/$(DLL_CONS).dll
EXECUTABLE      = $(BIN_DIR)/$(MAIN).exe

all: clean $(EXECUTABLE) exec

$(EXECUTABLE): $(JDMC_DLL) $(JDMC_SPRITE_DLL) $(CONSOLE_DLL)
	@echo ===================================================
	@echo - Compiling the Main executable...
	@if not exist $(BIN_DIR)\$(MAIN).exe $(CXX) main.cpp -o $(EXECUTABLE) -L$(DLL_DIR) $(ALL_DLL) $(INCLUDE)
	@echo - [SUCCESS] Main executable compiled: $(EXECUTABLE)

$(JDMC_DLL): $(OBJECTS)
	@echo ===================================================
	@echo - Creating JDMC DLL...
	@$(CXX) -shared -o $(JDMC_DLL) $(OBJECTS) $(INCLUDE)
	@echo - [SUCCESS] JDMC DLL created: $(JDMC_DLL)

$(JDMC_SPRITE_DLL): $(SPRITE_OBJECTS)
	@echo ===================================================
	@echo - Creating JDMCSprite DLL...
	@$(CXX) -shared -o $(JDMC_SPRITE_DLL) $(SPRITE_OBJECTS) $(INCLUDE) -L$(DLL_DIR) -l$(DLL_NAME)
	@echo - [SUCCESS] JDMCSprite DLL created: $(JDMC_SPRITE_DLL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo ---------------------------------------------------
	@echo - Compiling source file: $< ...
	@$(CXX) -c $< -o $@ $(INCLUDE)
	@echo - [SUCCESS] Compiled: $@



$(CONSOLE_DLL): $(C_OBJECTS)
	@echo ===================================================
	@echo - Creating CONSOLE DLL...
	@$(CXX) -shared -o $(CONSOLE_DLL) $(C_OBJECTS) $(INCLUDE) -L$(DLL_DIR) -l$(DLL_NAME) -l$(DLL_SPRITE)
	@echo - [SUCCESS] CONSOLE DLL created: $(CONSOLE_DLL)

$(CONSOLE_DIR)/%.o: $(CONSOLE_DIR)/%.cpp | $(CONSOLE_DIR)
	@echo ---------------------------------------------------
	@echo - Compiling console source file: $< ...
	@$(CXX) -c $< -o $@ $(INCLUDE)
	@echo - [SUCCESS] Compiled: $@

$(OBJ_DIR):
	@echo ---------------------------------------------------
	@echo - Creating Object Directories...
	@echo ---------------------------------------------------
	@echo - [INFO] Making Necessary Directories
	@mkdir JDMC\Object\Sprites
	@echo - [SUCCESS] Object directories created

clean:
	@cls
	@echo ---------------------------------------------------
	@echo - Cleaning the Directory...
# 	@if exist $(BIN_DIR)\$(MAIN).exe del $(BIN_DIR)\$(MAIN).exe
	@echo - [SUCCESS] Cleaning completed

exec:
	@echo ===================================================
	@echo - Running the executable...
	@echo ===================================================
	@$(BIN_DIR)/$(MAIN).exe
