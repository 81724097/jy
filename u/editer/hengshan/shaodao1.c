// Room: /u/dewey/shandao.c

inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
�����ڵ�ɽ��·���ϣ�·�������һ�����������������
���ɵ���Ԩ�����µ�·��խ�ֶ�������Ƕ��ʯ��֮�С�������
˷����ɽ��������ش������㲻��Ϊ���վ��ľ��󾪴��ˡ�            
LONG
        );

        set("no_clean_up", 0);

        set("exits", ([ /* sizeof() == 1 */
           "east" : "/u/editer/workroom",
           ]));

        setup();

        replace_program(ROOM);
}
