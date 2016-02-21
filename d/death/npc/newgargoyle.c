// gargoyle.c

#include <ansi.h>
#include <login.h>

inherit NPC;

string *death_msg = ({
	HIW "ʵϰ�޳�˵����ι�������ģ����ʲ�����֣�\n\n" NOR,
	HIW "ʵϰ�޳���������۹ⶢ���㣬����Ҫ�������һ���Ƶġ�\n\n" NOR,
	HIW "ʵϰ�޳����ߡ���һ�����������ͳ�һ�����ʲ�Ķ�����������\n\n" NOR,
	HIW "ʵϰ�޳����ϲ��ӣ�˵�����ף�����δ����������ܣ�\n\n" NOR,
	HIW "ʵϰ�޳�ɦ��ɦͷ��̾�������˰��ˣ����߰ɡ�\n\n"
		"һ�������Ũ��ͻȻ���֣��ܿ�ذ�Χ���㡣\n\n" NOR,
});

void create()
{
	set_name("ʵϰ�޳�", ({ "new gargoyle", "gargoyle" }) );
	set("long",
		"ʵϰ�޳�������������ͷ�����㣬���׵����Ͽ������κ�ϲŭ���֡�\n");
	set("attitude", "peaceful");
	set("chat_chance", 15);
	set("chat_msg", ({
		(: this_object(), "random_move" :),
		"ʵϰ�޳�����һ����������������������������ע��������ʱ�򣬵�����һ�ۡ�\n",
		"ʵϰ�޳��ѳ�������ͷ��������������������Լ��ְ��ֳ�����ָ��\n"
	}) );
	set("age", 217);
	set("combat_exp", 20000);
	set("max_gin", 900);
	set("max_kee", 900);
	set("max_sen", 200);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	setup();
}

void init()
{
	::init();
	if( !previous_object()
	||	!userp(previous_object())
	||	wizardp(previous_object()) ) return;
	call_out( "death_stage", 5, previous_object(), 0 );
}

void death_stage(object ob, int stage)
{
	if( !ob || !present(ob) ) return;

	tell_object(ob, death_msg[stage]);
	if( ++stage < sizeof(death_msg) ) {
		call_out( "death_stage", 5, ob, stage );
		return;
	} else
		ob->reincarnate();

	ob->move(REVIVE_ROOM);
	message("vision",
		"���Ȼ����ǰ�����һ����Ӱ����������Ӱ�ֺ����Ѿ�������\n"
		"�ܾ��ˣ�ֻ����һֱû������\n", environment(ob), ob);
}


