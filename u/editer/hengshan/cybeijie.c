inherit ROOM;

void create()
{
	set("short", "��Ҥ�ڱ���");
	set("long", @LONG
����һ����ʯ��ֵ������ϱ���ͷ���졣���Ͼ����ĵغ�
�����壬ֻ�м����������ǳ����ĵĹ㳡���ϱ���һ��С�������Ǽ���
�ƾɵ��񷿡�
LONG
	);
        set("outdoors", "city");

	set("exits", ([
		"east" : __DIR__"cygc",
		"south" : __DIR__"cyxiaomiao",
		"west" : __DIR__"cyximen",
		"north" : __DIR__"minju1",
	]));

	setup();
	replace_program(ROOM);
}

