1. Makefile:

  1) GNU/Make : addprefix

    $(addprefix <prefix>, <names…>)

    名称：加前缀函数 —— addprefix;

    功能：把前缀 <prefix> 加到 <names> 中的每个单词前面;

    返回：返回加过前缀的文件名序列;

    - 示例：$(addprefix src/,foo bar) 返回值是 “src/foo src/bar”;

  2) GNU/Make : addsuffix

    $(addsuffix <suffix>, <names…>)

    名称：加后缀函数 —— addsuffix;

    功能：把后缀 <suffix> 加到 <names> 中的每个单词后面;

    返回：返回加过后缀的文件名序列;

    - 示例：$(addsuffix .c,foo bar) 返回值是 “foo.c bar.c”

  3) wildcard

    在Makefile规则中，通配符会被自动展开。但在变量的定义和函数引用时，通配符将失效。这种情况下如果需要通配符有效，就需要使用函数“wildcard”;

    用法：$(wildcard PATTERN…) ;

      - 在Makefile中，它被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表。如果不存在任何符合此模式的文件，函数会忽略模式字符并返回空;

      - 例：$(wildcard ../Libraries/CMSIS/\*.c) ： 获取../Libraries/CMSIS/目录下的所有.c源文件;

  4) filter:

    $(filter <pattern…>, <text>)

    名称：过滤函数 —— filter。

    功能：以 <pattern> 模式过滤 <text> 字符串中的单词，保留符合模式 <pattern> 的单词。可以有多个模式。

    返回：返回符合模式 <pattern> 的字串。

    - 示例：

      sources := foo.c bar.c baz.s ugh.h

      foo: $(sources)

      cc \$(filter %.c %.s, $(sources)) -o foo

      \$(filter %.c %.s, $(sources)) 返回的值是 “foo.c bar.c baz.s”;
