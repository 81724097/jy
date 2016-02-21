// miaozhu.c

#include <ansi.h>

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("��ף", ({ "miao zhu","zhu" }) );
        set("gender", "����" );
        set("age", 74);
        set("long",
        "������˿�������ʮ�����ˣ����������͵���Ӱ�����Ȼ��������������������\n");
        set("combat_exp", 1);
        set("str", 13);
        set("dex", 12);
        set("con", 14);
        set("int", 13);
        set("attitude", "friendly");
        setup();
        carry_object("/u/editer/hengshan/obj/cloth")->wear();
	add_money("coin", 200);
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || !present(ob, environment(this_object())) ) return;
        say( WHT "��ף˵������λ" + RANK_D->query_respect(ob)
                + "��������Ǯ�������°ɡ�\n"NOR);
}
int accept_object(object who, object ob)
{
        int val;

        val = ob->value();
        if( !val )
                return notify_fail("��ף������Ʒ�ľ��ס�\n");
        else if( val > 100 ) {
                if( (who->query("bellicosity") > 0)
                &&      (random(val/10) > (int)who->query("con")) )
                        who->add("bellicosity", - 
(random((int)who->query("con")) + val/1000) );
        }
        say( "��ף˵������л��λ" + RANK_D->query_respect(who)
                + "������һ���ᱣ����ġ�\n");

        return 1;
}