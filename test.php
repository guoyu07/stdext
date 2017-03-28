<?php
$module = swoole_load_module(__DIR__.'/stdext.so');

class Test
{
	static $name = "test";
}

function test()
{
	$s = new StringType("a,b,c");
	$s->test();
	// var_dump($s, StringType::$version);

	$a = $s->split(',');
	var_dump($a->contains('a'));
	var_dump($a->contains('e'));
	var_dump($a->toArray());

	$s2 = $a->join('-');
	var_dump($s2);
	var_dump($s2->substr(2));
}


test();
$module->destroy();
exit(1);
