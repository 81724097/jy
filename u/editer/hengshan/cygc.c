// /u/editer/hengshan/cygc.c
// 

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��Ҥ�ڹ㳡");
	set("long", @LONG
�����Ǵ�Ҥ�ڵ������ģ������ǻ������ɵģ���Ȼ�ǳ���
�����ģ���Ҳ���������û��ʲô�ˣ�ż������·����Ҳ�Ǽ�
�Ҵҵ��߹�ȥ�ˡ��㳡�ı����и��Ʒ���pai fang���������
����һ����΢����һ��Ľֵ���������ͨ����ԭ�Ĵ�·������
��һ����ģ���Ĺ��á�
LONG
	);
        set("no_sleep_room",1);
        set("outdoors", "city");

	set("item_desc", ([
		"pai fang" : "����д�ţ�"+HIR"��������"NOR+"�ĸ����֡�\n",
	]));

	set("exits", ([
		"east" : __DIR__"cydongjie",
		"south" : __DIR__"cynanjie",
		"west" : __DIR__"cyxijie",
		"north" : __DIR__"cybeijie",
	]));

	set("objects", ([
		
	]));

	setup();
}

