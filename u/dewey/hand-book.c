inherit ITEM;

void create()
{
	set_name( "�ַ�ͼ��", ({ "hand book", "book","shu" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�����ַ�ͼ�ᣬ����д��һЩ�����ַ�����ʽ���������š�\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"hand",	
			"exp_required":	100,	// minimum combat experience required
			"jing_cost": 20, 	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	150,	// the maximum level you can learn
		]) );
	}
}
