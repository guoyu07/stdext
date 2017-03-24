<?php
swoole_load_module(__DIR__.'/stdext.so');

$s = new StringType("a,b,c");
$a = $s->split(',');
var_dump($a->contains('e'));
var_dump($a->join('-'));
