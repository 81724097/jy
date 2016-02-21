// zhaixing.c ժ����

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
       set_name("ժ����", ({ "zhaixing zi", "zhaixing" }));
       set("nickname", "�����ɴ�ʦ��");
       set("long", 
               "�����Ƕ�����Ĵ���ӡ������ɴ�ʦ��ժ���ӡ�\n"
               "����ʮ���꣬�����������۹���͸��һ˿����֮����\n");
       set("gender", "����");
       set("age", 35);
       set("attitude", "peaceful");
       set("shen_type", -1);
       set("str", 26);
       set("int", 28);
       set("con", 26);
       set("dex", 26);
       
       set("max_qi", 1000);
       set("max_jing", 800);
       set("neili", 1800);
       set("max_neili", 1800);
       set("jiali", 60);
       set("combat_exp", 350000);
       set("score", 50000);

       set_skill("force", 80);
       set_skill("huagong-dafa", 80);
       set_skill("dodge", 100);
       set_skill("zhaixinggong", 85);
       set_skill("unarmed", 105);
       set_skill("xingxiu-duzhang", 100);
       set_skill("parry", 70);
       set_skill("staff", 70);
       set_skill("tianshan-zhang", 60);
       set_skill("literate", 70);

       map_skill("force", "huagong-dafa");
       map_skill("dodge", "zhaixinggong");
       map_skill("unarmed", "xingxiu-duzhang");
       map_skill("parry", "tianshan-zhang");
       map_skill("staff", "tianshan-zhang");

       create_family("������", 2, "����");

       setup();
//     carry_object("/clone/weapon/gangzhang")->wield();
       carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
       command("say �ðɣ��Ҿ��������ˡ�");
       command("recruit " + ob->query("id"));
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                if ((ob->query("shen")>10000) &&
                        (!wizardp(ob))) {
        command("say ���޺����Ƕ����й�֮�أ�\n");
                        remove_call_out("do_killing");
                        call_out("do_killing",4,ob);
                }
        }
}

void do_killing(object ob)
{
       if (!ob || environment(ob) != environment())
                return;
        this_object()->kill_ob(ob);
}

