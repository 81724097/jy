// zhang.c ������

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_me();

void create()
{
	set_name("������", ({ "zhang sanfeng", "zhang" }));
	set("nickname", HIG "��������" NOR);
	set("long", 
		"�������䵱�ɿ�ɽ���桢�������ֵ�̩ɽ�������������ˡ�\n"
		"��һ���ۻ�Ļ�ɫ���ۣ����ޱ߷���\n"
		"��ĸߴ��������꣬������⣬��ü�԰ס�\n");
	set("gender", "����");
	set("age", 100);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 5000);
	set("max_jing", 3000);
	set("neili", 10000);
	set("max_neili", 10000);
	set("jiali", 100);
	set("combat_exp", 2000000);
	set("score", 500000);

	set_skill("force", 200);
	set_skill("taiji-shengong", 200);
	set_skill("dodge", 150);
	set_skill("tiyunzong", 150);
	set_skill("unarmed", 200);
	set_skill("taiji-quan", 200);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("taiji-jian", 200);
	set_skill("blade", 200);
	set_skill("taiji-dao", 200);
	set_skill("taoism", 150);
	set_skill("literate", 100);

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	map_skill("blade", "taiji-dao");

	create_family("�䵱��", 1, "��ɽ��ʦ");
	set("class", "taoist");

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.lian" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.sui" :),
		(: exert_function, "recover" :),
	}) );

	//modified by jackyboy [98.9.9]
	set("inquiry", ([
		"����"       : (: ask_me :)
	]));


	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();
}

//This function is added by jackyboy.[98.9.9]
int ask_me()
{
       mapping my_fam;
 
       object  me;
	int my_age, already_age, i;

	me = this_player();
       my_fam = (mapping)me->query("family");
	my_age = me->query("age");
	already_age = (int)me->query("already_age");

	if(random(5) >= 1)
	{
		me->add("con", 1);
		me->add("str", 1);
		me->add("int", 1);
		me->add("con_improve_time", 1);
		me->add("max_neili", 50);
 		me->add("neili", 50);
		me->add("dex", 1);
		me->add("max_jing", 1);
		me->add("max_qi", 1);
		me->add("jiali", 1);
		me->add("max_jingli", 1);
		me->add("score", 1);
		me->add("shen", 50);
		me->add("combat_exp", 100);
		me->add("potential", 10);
		me->set("already_age", my_age);
		tell_object(me,HIY"������һ�ƻ������ͷ������е�����ůů�ģ�\n"NOR);
	}
	else
	{
		me->add("potential",-10);	
		tell_object(me,HIY"��������һ������ʲô�������ף�ȥ���ɣ���\nһ����������е���������ϵ����˵���\n"NOR);
	}
	return 1;
	
}

void attempt_apprentice(object ob)
{
	if(wizardp(ob))
	{
		command("chat ����������������");
		command("chat �벻���ϵ��ڴ���֮�꣬���ٵ�һ������֮�ţ� ���ǿ�ϲ�ɺء�");
		command("recruit " + ob->query("id"));
		return;
	}
	if ((int)ob->query_skill("taiji-shengong", 1) < 50) {
		command("say ���䵱�����ڼ��书���������ڹ��ķ���"); 
		command("say " + RANK_D->query_respect(ob) + 
			"�Ƿ�Ӧ����̫�����϶��µ㹦��");
		return;
	}
	if ((int)ob->query("shen") < 2000) {
		command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}
	if (ob->query_int() < 30) {
		command("say ���䵱���书ȫ�ӵ��������");
		command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
		command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	command("chat ����������������");
	command("chat �벻���ϵ��ڴ���֮�꣬���ٵ�һ������֮�ţ����ǿ�ϲ�ɺء�");
	command("recruit " + ob->query("id"));
}
