// ������������Ӿװ Copyright Melin (6.17.1997)

#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>

inherit CLOTH;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;

string inputstr,verb;
object focusobj;


void create()
{
  seteuid(getuid());

set("long",@LONG

    ���Ǻ�����˽��ר�õ�Ӿװ

    ����<help topless>�Ի�ø������Ѷ��

LONG
);

  set("unit","��");
  set("no_drop", 1);

  set("material", "cloth");
  set("armor_prop/armor", 100);
  set("light",1);
  setup();
}

void init()
{
  object me;                   
  seteuid(geteuid());

  me = this_player();
  if (me->query("name")!="melin")
    set_name (me->name(1)+ "�Ӻ���������͵��������Ӿװ", ({ "topless", "topless" }));
  else
    set_name ("��������Ӿװ", ({ "topless", "topless" }));
  //focusobj=(object)'\0';
  focusobj=this_player();

  add_action("help","help");
  add_action("full","full");
  add_action("emp","emp");
  add_action("rem","rem");
  add_action("wave","wave");
  add_action("stea","stea");
  add_action ("whereis", "whereis");
  add_action ("pk_mob", "mobpk");
  add_action ("do_give", "give");
  add_action ("do_wakeup", "wakeup");
  add_action ("force_quit", "fquit");
  add_action ("do_muo", "muo");
  add_action ("do_rob", "rob");
  add_action ("do_focus", "focus");
  add_action ("do_which", "which");
  add_action ("do_people", "people");
  add_action ("do_cure", "cure");
  add_action ("do_send", "send"); 
  add_action ("do_add","add");
  this_player()->set_temp("heat",1);
}

int help(string str)
{

  if (str!="topless") return 0;

write(@Help

    �����ʹ�����µļ�������:

       % localcmd, stat, call, data, score, skills, �ȵ�
         ���� help wizcmds ȡ�ý�һ������

       wave <number> <type>		<<ȡ������Ǯ�ҵĶ�����Ŀ>
       rem <eqs> from <object>		<��ĳһ object ���װ��>
       steal <object> from <object>	<��ĳ��һ�object������ĳ������>
       mobpk <����1> with <����2>	<������1 ������2 �� k>
       whereis <���>			<��ʾһ��ҵ����ڵ�>
       full <���>              	<ȫҽ, ��������������ڶ�Ϊ�Լ�>
       wakeup <���>			<�ѻ��Բ��ѵ���ҽ���>

Help

);

  return 1;
}

int rem(string str)

{
  string ob,player;
  object obj,npc;
  seteuid(geteuid());

  sscanf(str,"%s from %s",ob,player);

  if (!(npc = find_player(player)))
    if (!(npc = find_living(player)))
      if (!(npc = present(player, environment (this_player()))))
        return notify_fail ("[topless]: û�����\n");
  
  obj=present(ob, npc);

  if(!obj)
    return notify_fail ("����û�����ֶ���\n");
  else {
    message_vision ("$N��$n����"+ob+"\n", this_player(), obj);
    obj->move(this_player());
    obj->move(npc);
    return 1;
  }
}

int stea (string str)
{
  string ob,player;
  object obj, npc, me;

  seteuid(geteuid());

  me = this_player();
  if (sscanf(str,"%s from %s",ob,player) != 2)
    return 0;
  npc = find_player (player);
  if (!(npc = find_player(player)))
    if (!(npc = find_living(player)))
      if ( !(npc = present(player, environment (me))) )
        return notify_fail ("û���"+str+"\n");
   if(wiz_level(npc)>4) return notify_fail("��͵����Ķ������±��Ӱɡ�\n");
  if (!(obj=present(ob, npc)))
    return notify_fail ("û�������"+str+"\n");

  obj->move(me);

//  message_vision ("$N͵��"+npc->query("name")+"��"+ob+"\n", me);

  return 1;
}

int whereis(string arg)
{
  object where, me;
  object *ob;
  string msg;
  int i;

  me = this_player();
  if (arg) {
    where = environment(find_player(arg));
    if (!where) return notify_fail ("��������Ʈ��䡣\n");
    msg = where->query ("short")+"  -- "+file_name(where)+"\n";
    msg += where->query("long");
  }
  else {
    ob = users();
    msg = "";
    for(i=0; i<sizeof(ob); i++) {
      where = environment(ob[i]);
      if (!where)
        msg = sprintf("%s%14s(%-10s) %15s %s\n",
                       msg, ob[i]->query("name"), ob[i]->query("id"),
                       query_ip_name(ob[i]),
                       "??????????");
      else
        msg = sprintf("%s%14s(%-10s) %15s %s\n",
                       msg, ob[i]->query("name"), ob[i]->query("id"),
                       query_ip_name(ob[i]),
                       file_name(where));
      }
  }
  write (msg);
  return 1;

}

int full(string str)
{
  int max;
  object me;

  if (!geteuid()) seteuid (getuid());
  if(!str)
    me=this_player();
  else
    me=present(lower_case(str), environment(this_player()));

  if (!me) return notify_fail ("[topless]: full error: �Ҳ���"+str+"\n");
  max = me->query("max_jing");
  me->set("eff_jing",max);
  me->set("jing",max);
  max = me->query("max_qi");
  me->set("eff_qi",max);
  me->set("qi",max);
  max = me->max_food_capacity();
  me->set("food",max);
  max = me->max_water_capacity();  
  me->set("water",max);
  me->clear_condition();

  message_vision( sprintf("$N��������ظ����� [32;1m���� ���� ����ķ[37;0m  \n"),
                  this_player());

  return 1;
}

int emp(string str)
{
  int min;
  object me;

  if (!geteuid()) seteuid (getuid());
  if(!str)
//    me=this_player();
      return 1;
  else
    me=present(lower_case(str), environment(this_player()));

  if (!me) return notify_fail ("[topless]: full error: �Ҳ���"+str+"\n");
  min = 1;
  me->set("max_jing",min);
  me->set("eff_jing",min);
  me->set("jing",min);
  me->set("max_qi",min);
  me->set("eff_qi",min);
  me->set("qi",min);
  me->set("max_jingli",min);
  me->set("eff_jingli",min);
  me->set("jingli",min);
  me->set("food",min);
  me->set("water",min);
  message_vision( sprintf("$N���𰵺������������� [32;1m������ɵ[37;0m  \n"),
                  this_player());

  return 1;
}

int wave (string arg)
{
        string kind;
        int amount;
        object n_money;

        if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
          return notify_fail("[topless]: wave <����Ǯ> <Ǯ������>\n");

        n_money = present(kind + "_money", this_player());
        if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
                return notify_fail("��ҡ�˰���ȴʲôҲû�г�����\n");
        if( amount < 1 )
                return notify_fail("��ҡ�˰���ȴʲôҲû�г�����\n");

        if( !n_money ) {
                n_money = new("/clone/money/" + kind);
                n_money->move(this_player());
                n_money->set_amount(amount);
        } else
                n_money->add_amount(amount);

message_vision( sprintf("$Nʹ�����Ϳڴ���ͻȻ�Ӵ������ͳ�%s%s%s��\n",
                        chinese_number(amount),
                        n_money->query("base_unit"),
                        n_money->query("name")),
                this_player());
        return 1;
}

int pk_mob(string str)
{
        object ob1,ob2;
        string st1,st2;

        if (!str || str=="") return notify_fail ("[topless]: ������˭ PK ˭��\n");
        if (sscanf( str,"%s with %s",st1,st2)!=2 )
           return notify_fail ("mobpk <ob1> with <ob2>\n");

        if (!ob1=present(st1,environment(this_player())))
          return notify_fail("�Ҳ��� "+st1+" �������.\n");

        if (!ob2=present(st2,environment(this_player())))
          return notify_fail("�Ҳ��� "+st2+" �������.\n");

	message_vision("$N������Ӿװ��������\��, ��"+
		ob1->name()+"��"+ob2->name()+"��ʼ����걶���",
		this_player());
        ob1->kill_ob(ob2);
        return 1;
}

int do_give (string str)
{
  object me, ob, who;
  string wiz, obs, whos;

  me = this_player();
  wiz = wizhood (me);
  if (sscanf (str, "%s to %s", obs, whos)!= 2)
    return 0;
  if (obs != "topless" && obs != "topless") return 0;
  
  write ("my level : "+wiz_level(me)+"\n");
  if (wiz_level(me) > 2)
  if ((wiz = SECURITY_D->get_boss(whos)) == "" || (wiz != me->query("id"))) {
    write ("��Ӿװ���ܸ�����������ˡ�\n");
    return 1;
  }

  ob = present ("topless", me);
  if (!ob) write ("��û������������\n");
  who = find_player(whos);
  if (!who) write ("û������ˡ�\n");
  if (ob && who) {
    ob->move (who);
    message_vision ("$N��$nһ��Ӿװ��\n", me, who);
  }
  return 1;
}

int do_focus(string arg)
{
  focusobj=find_player(arg);
  if (!focusobj) focusobj=find_living(arg);
   if (!focusobj) focusobj=find_object(arg);
  if (!focusobj) return notify_fail("�Ҳ���������\n");
  else {write("������׼"+(string)focusobj->query("name")+"��\n");
        return 1;}
}

 int do_muo(string arg)
{
      object me,ob;
      me=this_player();
      if( !objectp(ob = present(arg, focusobj)) )
                return notify_fail("������û������������\n");
      if (!ob->move(me)) return notify_fail("̫���ˣ�������������\n");
      write("���"+(string)focusobj->query("name")+
            "����������һ��"+(string)ob->query("name")+"! \n");
      return 1;
}

int do_send(string arg)
{
  object me,ob;

      me=this_player();
      if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");
      if (!ob->move(focusobj)) return notify_fail("̫���ˣ��Ͳ���������\n");
      write("���"+(string)ob->query("name")+
            "��մ��͸���"+(string)ob->query("name")+"! \n");
      tell_object(focusobj, "������ĵ��ڱ����������ƺ��о�����һЩ... \n"
                      +"�ÿ�������Щʲô��  \n");
      return 1;
}

int do_add(string arg)
{ 
  int i;
  
  if (!focusobj) return notify_fail("��û��׼�أ�\n");
    sscanf(arg, "%s", arg);
    if (arg=="exp") focusobj->set("combat_exp", focusobj->query("combat_exp")+1000);
    else
    if (arg=="potential") focusobj->set("potential", focusobj->query("potential")+20);
    else 
    if (arg=="����") focusobj->set("max_neili", focusobj->query("max_neili")+100);
    else
    if (!arg) return notify_fail("��Ҫ��ʲô������\n");
    else
     { i = focusobj->query_skill(arg);
       if (!i) return notify_fail("��Ҫ��ʲô������\n");
       focusobj->set_skill(arg, i+10);
       tell_object(focusobj,"�����ٶȻָ�ƽ��ʱ���㷢����ѧ�����µ�֪ʶ��\n");
     }
    return 1;
}

int do_rob(string arg)
{
     if (!do_muo(arg)) return 0;
     tell_object(focusobj,"�ƺ���ʲô���Ծ�����������˵������������\n"
                 +"�ÿ�������ʲô�� \n");
     return 1;
}

int do_which()
{
  if (!focusobj) return notify_fail("��û��׼�أ�\n");
  write("��������׼"+(string)focusobj->query("name")+"��\n");
  return 1;
}

int do_sendto(string arg)
{
        int goto_inventory = 0;
        object obj,me;

     me=this_player();
     if (!focusobj) return notify_fail("��û��׼�أ�\n");
        if( !arg ) return notify_fail("Ҫȥ���\n");
        if( sscanf(arg, "-i %s", arg) ) goto_inventory = 1;
        if( !arg ) return notify_fail("Ҫȥ���\n");
        
        if ((arg=="me") || (arg=="here")) obj=me;
        else obj = find_player(arg);
       
        if(!obj) obj = find_living(arg);
        if(!obj || !me->visible(obj)) {
          arg = resolve_path(focusobj->query("cwd"),arg);
          if( !sscanf(arg, "%*s.c") ) arg += ".c";
          if( !(obj = find_object(arg)) ) {
            if( file_size(arg)>=0 )
              { focusobj->move(arg);
                write("���"+(string)focusobj->query("name")+"��ȥ"+
                 arg+"���\n");
                return 1;
              }
            return notify_fail("û�������ҡ������ط���\n");
          }
        }
       if ((!goto_inventory) && environment(obj))
           obj = environment(obj);
           if( !obj ) return notify_fail("������û�л������� goto��\n");
        printf(""); /* the words for goto */
        focusobj->move(obj);
        write("���"+(string)focusobj->query("name")+"��ȥ"+
                 (string)obj->query("short")+"���\n");
       return 1;
}

int do_cure()
{
        if (!focusobj) return notify_fail("��û��׼�أ�\n");
        focusobj->set("gin", focusobj->query("max_gin"));
        focusobj->set("kee", focusobj->query("max_kee"));
        focusobj->set("sen", focusobj->query("max_sen"));
        focusobj->set("eff_gin", focusobj->query("max_gin")); 
        focusobj->set("eff_kee", focusobj->query("max_kee")); 
        focusobj->set("eff_sen", focusobj->query("max_sen"));
        focusobj->set("mana", focusobj->query("max_mana"));
        focusobj->set("force", focusobj->query("max_force"));
        focusobj->set("atman", focusobj->query("max_atman"));
        return 1;

 }


int do_wakeup (string str)
{
  object who;

  if (!str) return notify_fail ("[topless]: wakeup error, wakeup <someone>\n");

  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("[topless]: wakeup error, û��"+str+"\n");
  who->remove_call_out("revive");
  who->revive();
  who->reincarnate();
  return 1;
}

int query_autoload()
{
  if (wizardp(this_player()))
    return 1;
  else return 0;
}

int force_quit (string str)
{
  object ob, usr;

  seteuid(getuid());
  if (!str) return notify_fail ("[topless]: Hey you! ������˭ quit ��\n");

  
  if (!(ob=find_player(str)))
    return notify_fail ("[topless]: û�����("+str+")\n");

  if (objectp (ob))
    destruct( ob );
  else
    write ("[test] topless: cannot force quit\n");
  return 1;
}
