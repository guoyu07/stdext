PHP_INCLUDE = `php-config --includes`
PHP_LIBS = `php-config --libs`
PHP_LDFLAGS = `php-config --ldflags`
PHP_INCLUDE_DIR = `php-config --include-dir`
PHP_EXTENSION_DIR = `php-config --extension-dir`

all: stdext.cpp
	c++ -DHAVE_CONFIG_H -g -o stdext.so -O2 -fPIC -shared stdext.cpp -std=c++11 ${PHP_INCLUDE} -I${PHP_INCLUDE_DIR}/ext/swoole -I${PHP_INCLUDE_DIR}/ext/swoole/include
clean: stdext.so
	rm stdext.so
install: stdext.so
	cp stdext.so ${PHP_EXTENSION_DIR}
