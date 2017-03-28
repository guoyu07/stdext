# stdext
Swoole的C++模块，支持了面向对象的string和array接口。

## 准备
安装swoole-1.9.9或更高版本

```shell
git clone https://github.com/swoole/swoole-src
cd swoole-src
phpize
./configure
make && make -j4 install
```
## 编译
```shell
cd stdext
make && make install
```

## 加载
修改php.ini，增加
```shell
swoole.modules="stdext.so"
```

## 运行

```php
swoole_load_module(__DIR__.'/stdext.so');
$s = new StringType("a,b,c");
$a = $s->split(',');
var_dump($a->contains('e'));
var_dump($a->toArray());

$s2 = $a->join('-');
var_dump($s2);
var_dump($s2->substr(2));
```
