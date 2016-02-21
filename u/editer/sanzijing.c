// blade_book.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(WHT "���־�" NOR, ({"sanzi jing","jing","shu", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			"����һ�����־�����С���Ӷ���ʶ�ֵĿα�\n");
		set("value", 260);
		set("material", "paper");
		set("skill", ([
			"name":         "literate",	// name of the skill
			"exp_required":	10,		// minimum combat experience required
							// to learn this skill.
			"sen_cost":	10,		// gin cost every time study this
			"difficulty":	20,		// the base int to learn this skill
							// modify is gin_cost's (difficulty - int)*5%
			"max_skill":	50		// the maximum level you can learn
							// from this object.
		]) );
	}
}
