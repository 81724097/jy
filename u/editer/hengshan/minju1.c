//  /d/hengshan/minju1.c
// written by Dewey

inherit ROOM;

void create()
{
        set("short", "���");
	set("long", @LONG
����һ���ƾɵķ��ݣ�����ֻ�м������ƵļҾ㡣����ս
�ҵ�Ӱ�죬�������ǵ�����Ƚ�ƶ�����ڿ��ſڵ�ǽ���м�
�����ڷ����еĿڴ����ƺ���������������ƿڴ�Ϊ���ġ�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"cyxijie",
           ]));
        
        set("no_clean_up", 0);
        
        set("objects", ([
                __DIR__"npc/oldwoman": 1 ]) );

        setup();
        replace_program(ROOM);
}
 
