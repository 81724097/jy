// Room: /d/quanzhou/haigang.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǳ����ıؾ�֮�أ�����ʩ���С���������Գ������һ�����
LONG
	);

	set("exits", ([
                "west" : __DIR__"zhongxin",
	]));

	set("objects", ([
                __DIR__"npc/boy":2,
                __DIR__"npc/girl":1,
		"/d/taohua/npc/chuanfu" :1,
	]));

	set("outdoors", "quanzhou");
	setup();
	replace_program(ROOM);
}

