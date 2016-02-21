#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void consider();

void create()
{
    set_name("��ҩʦ", ({"huang yaoshi", "huang", "yaoshi"}));
    set("nickname", HIY "��а" NOR );
    set("gender", "����");
    set("age", 42);
    set("long", 
        "�������һ����������ºö�ȫ�ɼ��ģ���˱��˳�������а����\n");
    set("attitude", "peaceful");
	
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("chat_chance", 1);
    set("chat_msg", ({
        "��ҩʦ̾�˿����������� ���� �ض�������ĺ��ӣ���С��û���� ������\n",
        "��ҩʦ��ͷ��˼����Ȼ���\n",
    }));
    set("inquiry", ([
        "����"     : "���ֱ����Ů���Ĺ����� \n",
        "�����澭" : "������ܰ���ȡ���澭�ϲᣬ��һ������л�㡣\n",
    ]));

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 3000);
    set("max_jing", 3000);
    set("neili", 3500);
    set("max_neili", 3500);
    set("jiali", 100);
	
    set("combat_exp", 1500000);
    set("score", 0);
	 
    set_skill("force", 150);             // �����ڹ�
    set_skill("bibo-shengong", 150);     // �̲���
	set_skill("claw", 150);
    set_skill("finger", 170);            // ����ָ��
    set_skill("tanzhi-shentong", 170);   // ��ָ��ͨ
    set_skill("unarmed", 120);           // ����ȭ��
    set_skill("luoying-zhang", 120);     // ��Ӣ����
    set_skill("dodge", 150);             // ��������
    set_skill("anying-fuxiang", 120);    // ��Ӱ����
    set_skill("parry", 150);             // �����м�
    set_skill("sword", 200);             // ��������
    set_skill("luoying-shenjian", 200);  // ��Ӣ��
    set_skill("qimen-wuxing",150);       // ��������
    set_skill("literate",150);           // ����ʶ��
	
    map_skill("force"  , "bibo-shengong");
    map_skill("finger" , "tanzhi-shentong");
    map_skill("unarmed", "luoying-zhang");
    map_skill("dodge"  , "anying-fuxiang");
    map_skill("parry"  , "luoying-shenjian");
    map_skill("sword"  , "luoying-shenjian");
	
    create_family("�һ���", 1, "����");
    setup();
	
    carry_object(__DIR__"obj/yuxiao")->wield();
    carry_object(__DIR__"obj/bupao")->wear();
    carry_object(__DIR__"obj/jiuyin2");
    
}

void attempt_apprentice(object ob)
{
    if (ob->query_int() < 30) {
        command("say �Ҳ������ʲ�ĵ��ӣ�����ذɣ�");
		return;
    }
    if ((int)ob->query_skill("bibo-shengong",1) < 50 ) {
        command("say ��ı����ڹ��ķ�̫����,����ŬŬ�������һ�°�!");
		return;
    }
    if ((int)ob->query("shen") >100000 || (int)ob->query ("shen") < -100000 ) {
        command("say ���һ��������������������������ֳ�������򽻵�������ذɣ�");
		return;
	}
    command("say �ܺã��ܺá�");
    command("recruit " + ob->query("id"));
}

int recognize_apprentice(object ob)
{
	mapping myfam;
       	myfam = (mapping)ob->query("family");
        if ( myfam["family_name"] == "�һ���") return 1 ;
	if ((int)ob->query_temp("tmark/��") == 1 )
        message_vision("��ҩʦ���˿�$N��˵��������������˭Ҳ��Ƿ˭,\n"
                          "�㲻Ҫ������ѧϰ�����ˡ�\n", ob);
	if (!(int)ob->query_temp("tmark/��"))
		return 0; 
	ob->add_temp("tmark/��", -1);
	return 1;
}

int accept_object(object who, object ob)
{
	
	if ( (string) ob->query("id") =="jiuyin zhenjing1" ) {
 		if (!(int)who->query_temp("tmark/��")) who->set_temp("tmark/��", 0);
		message_vision("��ҩʦ���˿�$N�������ؼ������˵�ͷ��˵����\n"
                               "�ѵ��㽫�澭�ͻء������ҵĶ����Ҿ������ˡ�\n"
                               "��Ϊ����,����Դ�������ѧ�㹦��\n", who);
		who->add_temp("tmark/��", 120);
		return 1;
	}
	return 0;
}