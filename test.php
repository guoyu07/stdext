<?php
swoole_load_module(__DIR__.'/stdext.so');

$s = new StringType("a,b,c");
$a = $s->split(',');
var_dump($a->contains('e'));
var_dump($a->toArray());

$s2 = $a->join('-');
var_dump($s2);
var_dump($s2->substr(2));
