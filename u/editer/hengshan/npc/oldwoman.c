// oldwoman.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("�ϴ���", ({ "old woman", "woman" }) );
        set("gender", "Ů��" );
        set("age", 63);
        set("long", "һ��������˪֮ɫ��������,���ڱ������ӡ�\n");
        set("shen", 1000);
	set("shen_type", 1);
	set("combat_exp", 150);
        set("env/wimpy", 60);
        set("chat_chance_combat", 50 );
        set("vendor_goods", ({
		"/u/editer/hengshan/obj/koudai"
	}));;
        set("str", 13);
        set("dex", 12);
        set("con", 14);
        set("int", 13);
        set("attitude", "friendly");
        set("inquiry", ([
                "�ڴ�" : WHT "��λ�͹٣����ǲ�������ڴ�����ʮ��Ǯһ��" NOR,
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
		"�ϴ������ĵ�˵������Ϊ̫ƽȮ����Ϊ������ѽ��\n",
		"�ϴ���̾�˿�����˵����������̣����Ǹ�ʲ����������\n",
        }) );
	carry_object("/u/editer/hengshan/obj/cloth")->wear();
	add_money("coin", 100);
}

void init()
{	
	add_action("do_buy", "buy");
}

