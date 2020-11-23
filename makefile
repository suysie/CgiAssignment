src = $(wildcard Source/*.c)
obj = $(src:.c=.o)
build/main: $(obj)
	$(CC) -o $@ $^
.PHONY: clean
clean:
	@echo "Lets clean it..."
	rm -f $(obj) build/main