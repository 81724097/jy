//westroad1.c

inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long",
             "����һ��ֱͨ������ɽ·������Զ����ȺɽΡ�룬����Ʈ�죬\n"
         "����ǰ��Զ����Ҫ������ɽ֮���ˡ�������������֮���������䵱ɽ��\n"
	);
	set("exits",([
		      "west" : __DIR__"westroad2",
		      "east" : "/d/wudang/shanmen",
	   ]));
	setup();
	replace_program(ROOM);
}
        