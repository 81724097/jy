//wuqiku.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long",
             "�����ǡ�����ɽ�����ӵ������⣬������ɽ�����ӿ��Ե���\n"
         "��ȡ�����õĸ����������������ɵ����ǲ���������ġ�\n"
        );
        set("exits", ([
                "east" : __DIR__"yuanzi",
        ]));
	set("objects",([
		"/clone/weapon/gangzhang":2,
	]));
        setup();
        replace_program(ROOM);
}






