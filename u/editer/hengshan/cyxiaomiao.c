inherit ROOM;

void create()
{
	set("short", "С��");
	set("long", @LONG
����һ��ʮ���Ͼɵĳ��������ú�С��������ǰ��
�����Ϲ�����һ������ĳ��������Ͼɣ�����������
�ѱ����޹���ںڵ���ɫ����������ľ��񳣵���������
��ƽ����
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"cyxijie",
		"east" : __DIR__"cynanjie",
	]));
	set("no_fight", "1");

	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/keeper" : 1,
	]));

	setup();
	replace_program(ROOM);
}
