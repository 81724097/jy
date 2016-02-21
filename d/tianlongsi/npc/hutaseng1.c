inherit NPC;

void create()
{
	set_name("����ɮ", ({ "huta seng","seng"}) );
	set("gender", "����" );
	set("class", "bonze");
	set("age", 30);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 1000);
	set("max_qi", 1000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 20);
	set("combat_exp", 80000);
	set("score", 10000);

	set_skill("force", 100);
	set_skill("hunyuan-yiqi", 100);
	set_skill("dodge", 100);
	set_skill("shaolin-shenfa", 100);
	set_skill("parry", 100);
	set_skill("finger", 100);
	set_skill("staff", 100);
	set_skill("liumai-shenjian", 100);
	set_skill("weituo-gun", 100);
	set_skill("buddhism", 120);
	set_skill("literate", 120);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "liumai-shenjian");
	map_skill("finger", "liumai-shenjian");
	map_skill("staff", "weituo-gun");

	prepare_skill("staff","weituo-gun");	
	set("inquiry" ,([
	"������" : "����������֮����ԭ��������������ʩ������ȥ�����𣿡�\n",
	"����" : "��ʩ��Ҳ��֪�����ǵ�������������ѵ�����˼��˼һ�£���\n",
	]));

	setup();
	carry_object("/clone/weapon/gangzhang")->wield();
}

int accept_object(object who, object ob)
{
	if (ob->query("money_id") )
	{
	if( ob->value() >= 100000) 
		{
		message_vision("����ɮ���ĵذ�$N������������\n", who);
		who->move("/d/tianlongsi/tading");
		return 1;
		}
	else
		{
		message_vision("����ɮ˫�ֺ�ʮ�����������������ӷ𣡡�\n");
		return 1;
		}
	}
	return 0;
}