inherit ITEM;

void create()
{
	set_name( "�Ʒ�ͼ��", ({ "strike book", "book","shu" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�����Ʒ�ͼ�ᣬ����д��һЩ�����Ʒ�����ʽ���������š�\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"strike",	
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 20, 	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100,	// the maximum level you can learn
		]) );
	}
}
