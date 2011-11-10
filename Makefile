

all:
	make -C ./test_dev
	make -C ./test_fb

.PHONY: clean

clean:
	rm -rf *~
	make -C ./test_dev clean
	make -C ./test_fb clean
