// go.c

inherit F_CLEAN_UP;

mapping default_dirs = ([
	"north":		"��",
	"south":		"��",
	"east":			"��",
	"west":			"��",
	"northup":		"����",
	"southup":		"�ϱ�",
	"eastup":		"����",
	"westup":		"����",
	"northdown":	"����",
	"southdown":	"�ϱ�",
	"eastdown":		"����",
	"westdown":		"����",
	"northeast":	"����",
	"northwest":	"����",
	"southeast":	"����",
	"southwest":	"����",
	"up":			"��",
	"down":			"��",
	"enter":		"��",
	"out":			"��",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string dest, mout, min, dir;
	object env, obj;
	mapping exit;
	object *f_obs, *ob;
	int count = 0, my_dex, i;

	if( !arg ) return notify_fail("��Ҫ���ĸ������ߣ�\n");

	if( me->over_encumbranced() )
		return notify_fail("��ĸ��ɹ��أ��������á�\n");

	if( me->is_busy() )
		return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
	if (me->is_fighting()) {
		f_obs = me->query_enemy();
		if (objectp(f_obs[0]))
		if (5 + random((int)me->query("dex")) <= 
			random((int)f_obs[0]->query("dex"))) {
			me->start_busy(1);
//added by King
			message_vision("$N���Ʋ��ã�ת��Ҫ�ߣ���$nһ��������ǰ�����ߣ�û��ô���ף�\n", me, f_obs[0]);
//end of appendence

			return notify_fail("������ʧ�ܡ�\n");
		}
	}

	env = environment(me);
	if(!env) return notify_fail("������Ҳȥ���ˡ�\n");

	if( !mapp(exit = env->query("exits")) || undefinedp(exit[arg]) ) {
		if( query_verb()=="go")
			return notify_fail("�������û�г�·��\n");
		else
			return 0;
	}

	dest = exit[arg];

	if( !(obj = find_object(dest)) )
		call_other(dest, "???");
	if( !(obj = find_object(dest)) )
		return notify_fail("�޷��ƶ���\n");

// Added by Hop
	ob = all_inventory(obj);
	for(i=0; i<sizeof(ob); i++)
		if( living(ob[i]) && ob[i] != me )
			count++;
	my_dex = (int)me->query_dex();
	if(!objectp(present("zhu xi", environment(me)))
        &&!objectp(present("wind", environment(me)))
        &&!objectp(present("peter", environment(me)))) 
//��ʱ���ж��Ƿ����⼸��npc��ȷ���Ƿ�����������
	if(((my_dex < 15) && (count > 6))
	|| ((my_dex < 20) && (count > 8))
	|| ((my_dex < 30) && (count > 10))
	|| ((my_dex < 40) && (count > 12)))
		return notify_fail("ǰ����̫���ˣ�����ô��Ҳ������ȥ��\n");
// End of appendence	
 
	if( !env->valid_leave(me, arg) ) return 0;

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;

	if( me->is_fighting() ) {
		mout = me->name() + "��" + dir + "��Ķ����ˡ�\n";
		min = me->name() + "����ײײ�����˹�����ģ����Щ�Ǳ���\n";
	}
	else {
		if(me->query("gender") == "Ů��"){
			mout = "һ��ٻӰ��" + dir + "�뿪��\n";
			min = "һ��ٻӰ���˹�����\n";
		}
		else{
			mout = "һ����Ӱ��" + dir + "�뿪��\n";
			min = "һ����Ӱ���˹�����\n";
		}
	}

	message( "vision", mout, environment(me), ({me}) );
	if( me->move(obj) ) {
		me->remove_all_enemy();
		message( "vision", min, environment(me), ({me}) );
		me->set_temp("pending", 0);
		all_inventory(env)->follow_me(me, arg);
		return 1;
	}

	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;

	if( !environment(me) || !living(me) ) return;
	exits = environment(me)->query("exits");
	if( !mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	tell_object(me, "�������һ���������...\n");
	main(me, directions[random(sizeof(directions))]);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : go <����>
 
������ָ���ķ����ƶ���
 
HELP
    );
    return 1;
}
