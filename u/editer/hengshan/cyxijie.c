// Room: /city/xidajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "��Ҥ������");
	set("long", @LONG
����һ����ʯ��ֵ���������ͷ���졣���Ͼ����ĵغ�
�����塣�����ǳ����ĵĹ㳡���ϱ���һ��С�������Ǽ���
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

