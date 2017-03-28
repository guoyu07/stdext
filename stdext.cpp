/*
  +----------------------------------------------------------------------+
  | Swoole                                                               |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Tianfeng Han  <mikan.tenny@gmail.com>                        |
  +----------------------------------------------------------------------+
*/

#include <string>
#include <iostream>

#include "PHP_API.hpp"
#include "swoole.h"
#include "module.h"

using namespace std;
using namespace PHP;

extern "C"
{
    int swModule_init(swModule *);
    void swModule_destroy(swModule *);
}

static defineMethod(String, construct)
{
    if (!args[0].isString())
    {
        throwException("\\Exception", "parameter 1 is not string.");
        return;
    }
    _this.set("string", args[0].toString());
}

static defineMethod(String, split)
{
    auto delim = args[0];
    auto str = _this.get("string");
    Variant ret;
    if (args.count() == 2)
    {
        ret = PHP::exec("explode", delim, str, args[1]);
    }
    else
    {
        ret = PHP::exec("explode", delim, str);
    }
    Object o = PHP::newObject("ArrayType", ret);
    retval.copy(o);
}

static defineMethod(String, substr)
{
    auto str = _this.get("string");
    Variant ret;
    if (args.count() == 2)
    {
        ret = PHP::exec("substr", str, args[0], args[1]);
    }
    else
    {
        ret = PHP::exec("substr", str, args[0]);
    }
    Object o = PHP::newObject("StringType", ret);
    retval.copy(o);
}

static defineMethod(String, test)
{
    auto a = PHP::newResource("StringResource", new String("hello world"));
    _this.set("resource", a);
}

static defineMethod(Array, toArray)
{
    auto arr = _this.get("array");
    retval.copy(arr);
}

void Array_construct(Object &_this, Args &args, Variant &retval)
{
    auto _array = args[0];
    if (!_array.isArray())
    {
        throwException("\\Exception", "parameter 1 is not array.");
        return;
    }
    Array array(_array);
    _this.set("array", array);
}

void Array_contains(Object &_this, Args &args, Variant &retval)
{
    auto val = args[0];
    auto arr = _this.get("array");
    auto ret = PHP::exec("in_array", val, arr);
    retval = ret.toBool();
}

void Array_join(Object &_this, Args &args, Variant &retval)
{
    auto val = args[0];
    auto arr = _this.get("array");
    auto ret = PHP::exec("implode", val, arr);
    Array _args;
    _args.append(ret);
    Object o = PHP::create("StringType", _args);
    retval.copy(o);
}

static void StringResource_destory(zend_resource *res)
{
    String *str = static_cast<String *>(res->ptr);
    delete str;
}

int swModule_init(swModule *module)
{
    module->name = (char *) "stdext";

    Class *class_string = new Class("StringType");
    class_string->addMethod("__construct", String_construct, CONSTRUCT);
    class_string->addMethod("split", String_split);
    class_string->addMethod("substr", String_substr);
    class_string->addMethod("test", String_test);
    //static property
    class_string->addProperty("version", "1.0.5", STATIC);
    PHP::registerClass(class_string);

    Class *class_array = new Class("ArrayType");
    class_array->addMethod("__construct", Array_construct, CONSTRUCT);
    class_array->addMethod("contains", Array_contains);
    class_array->addMethod("join", Array_join);
    class_array->addMethod("toArray", Array_toArray);
    PHP::registerClass(class_array);

    PHP::registerResource("StringResource", StringResource_destory);

    return SW_OK;
}

void swModule_destroy(swModule *module)
{
    PHP::destroy();
}
