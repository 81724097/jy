//
//  ��Ƥ��

inherit ITEM;

void create()
{
        set_name( "��Ƥ��", ({ "skin" , "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ����Ƥ,���滭���轣��С�ˡ�\n");
		set("value", 0);
		set("material", "paper");
		set("skill", ([
                        "name": "sword",        // name of the skill
                        "exp_required": 10000,      // minimum combat experience required
                        "jing_cost":  60,// jing cost every time study this
                        "difficulty":   42,     // the base int to learn this skill
                        "max_skill":    150,     // the maximum level you can learn
		]) );
	}
}
