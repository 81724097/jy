// /hengshan/cyximen.c
// written by Dewey 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "��Ҥ������");
	set("long", @LONG
���Ǳ��������Ҥ�ڵ������ţ���ͨ��������Į��ͨ��֮
һ��Ҳ�Ǳ����������³�ѡ����ڡ�����������ս���Ѿ��Ե�
��Щ�ưܡ��������Ϸ�����ǿǿ�����ϳ������š��������֣�
��ǽ�����ż���ͨ����ʾ(gaoshi)���ٱ��ǽ䱸ɭ�ϣ�������
�ͽ�ס�������ʡ�һ����ֱ����ʯ���������������졣��
�����У��������Ź��ˡ������ѽӽ��߹أ����˺��١�������
���
LONG
	);
        set("outdoors", "hengshan");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"east" : __DIR__"cyxijie",
  		"west" : "/d/xingxiu/xxroad1",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 3,
        ]));
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n��������ʹ\n";
}

