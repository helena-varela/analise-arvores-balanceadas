CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

TARGET   := amazon_challenge

SRCS     := main.cpp avl.cpp rubro_negra.cpp
OBJS     := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "\n[SUCESSO] Projeto compilado com sucesso! Execute com: ./$(TARGET)\n"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) resultados_testes.csv
	@echo "\n[LIMPEZA] Arquivos compilados e relatórios temporários removidos.\n"

run: all
	./$(TARGET)

.PHONY: all clean run