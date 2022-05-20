CFLAGS=-O3 -std=c11 -Wall -Wextra

SRCS=main.c

a.out: $(SRCS)
	@echo "$(CC) $@"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(SRCS)
