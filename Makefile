SWOOLE_SRC = "/home/htf/workspace/swoole"
PHP_INCLUDE = `php-config --includes`
PHP_LIBS = `php-config --libs`
PHP_LDFLAGS = `php-config --ldflags`
PHP_EXTENSION_DIR = `php-config --extension-dir`

all: stdext.cpp
	c++ -DHAVE_CONFIG_H -g -o stdext.so -O2 -fPIC -shared stdext.cpp ${PHP_INCLUDE} -std=c++11 -I${SWOOLE_SRC}/include -I${SWOOLE_SRC}
clean: stdext.so
	rm stdext.so
install: stdext.so
	cp stdext.so ${PHP_EXTENSION_DIR}