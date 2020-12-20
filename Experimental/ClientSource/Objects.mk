ifndef SourceRoot

CURRENT :=
CURRENT += Libraries/CRC32.cpp
CURRENT += Libraries/Logging.cpp
CURRENT += Libraries/MessageConverter.cpp
CURRENT += Libraries/PushButtons.cpp
CURRENT += Libraries/PokemonRoutines.cpp
CURRENT += Connection/Unicode.cpp
CURRENT += Connection/PABotBaseConnection.cpp
CURRENT += Connection/PABotBase.cpp
CURRENT += Programs.cpp

SOURCES := $(SOURCES) $(addprefix $(CURRENT_DIR)/, $(CURRENT))
endif
