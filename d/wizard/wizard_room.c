// Room: /d/wizard/wizard_room.c

inherit ROOM;

void create()
{
	set("short", "��ʦ��Ϣ��");
	set("long", @LONG
������ǡ���ӹȺ��������ʦ����Ϣ���ڣ��շ�ˢ��������ǽ����
��ͺͺ��ʲô��û�У����ӵ����������һ���ľ�����������һ
����ʦ���Բ�(board)��
LONG );

	set("exits", ([ /* sizeof() == 1 */
  	"down" : __DIR__"guest_room" ]));

	set("valid_startroom", 1);
	set("no_fight", "1");
	set("no_clean_up", 0);
	setup();

	call_other("/clone/board/wiz_b", "???");
	replace_program(ROOM);
}
