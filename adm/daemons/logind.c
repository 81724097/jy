// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
int mad_lock = 0;
string *banned_name = ({
	"��", "��", "��", "��", "��",
	"ʱ��",
});

void get_id(string arg, object ob);
void confirm_id(string yn, object ob);
object make_body(object ob);
void init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);

void random_gift(mapping my)
{
	int i;
	int tmpstr, tmpint, tmpcon, tmpdex;
	tmpstr = tmpint = tmpcon = tmpdex = 10;

	for (i = 0; i < 40; i++) {
		switch (random(4)) {
//		case 0: if (tmpstr <= 25) tmpstr++; else i--; break;
//		case 1: if (tmpint <= 25) tmpint++; else i--; break;
//		case 2: if (tmpcon <= 25) tmpcon++; else i--; break;
//		case 3: if (tmpdex <= 25) tmpdex++; else i--; break;
		case 0: tmpstr++; break;
		case 1: tmpint++; break;
		case 2: tmpcon++; break;
		case 3: tmpdex++; break;
		}
	}
	if (tmpstr <= 30) my["str"] = tmpstr; else my["str"] = 30;
	if (tmpint <= 30) my["int"] = tmpint; else my["int"] = 30;
	if (tmpcon <= 30) my["con"] = tmpcon; else my["con"] = 30;
	if (tmpdex <= 30) my["dex"] = tmpdex; else my["dex"] = 30;
	// next 2 are randomly selected
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);
}

void create() 
{
	seteuid(getuid());
	set("channel_id", "���߾���");
}

void logon(object ob)
{
	object *usr;
	int i, wiz_cnt, ppl_cnt, login_cnt;

	if( mad_lock == 1 ) {
		write("����ʱ���Ѿ�����ˣ����ܽ��룡�� \n");
                destruct(ob);
                return;
        }

	if (BAN_D->is_banned(query_ip_name(ob)) == 1) {
		write("��ĵ�ַ�ڱ� MUD ���ܻ�ӭ��\n");
		destruct(ob);
		return;
	}
	cat(WELCOME);
	UPTIME_CMD->main();

	usr = users();
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) ) login_cnt++;
		else if( wizardp(usr[i]) ) wiz_cnt++;
		else ppl_cnt++;
	}
	printf("Ŀǰ���� %d λ��ʦ��%d λ��������ϣ��Լ� %d λʹ���߳��������С�\n\n",
		wiz_cnt, ppl_cnt, login_cnt );

	write("����Ӣ�����֣�");
	input_to( (: get_id :), ob );
}

void get_id(string arg, object ob)
{
	object ppl;
	object *usr;
	int i, wiz_cnt;

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
		write("����Ӣ�����֣�");
		input_to("get_id", ob);
		return;
	}

//#ifdef MAX_USERS
	usr = users();
	wiz_cnt = 0;
	for(i=0; i<sizeof(usr); i++) {
		if( wizardp(usr[i]) ) wiz_cnt++;
	}
	if( (string)SECURITY_D->get_status(arg)=="(player)"
         && (sizeof(users()) - wiz_cnt) >= 60) {
		ppl = find_body(arg);
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		if( !ppl || !interactive(ppl) ) {
//			write("�Բ���" + MUD_NAME + "��ʹ�����Ѿ�̫���ˣ������������\n");
			write("�Բ��𣬽�ӹȺ������ʹ�����Ѿ�̫���ˣ������������\n");
			destruct(ob);
			return;
		}
	}
//#endif

	if( wiz_level(arg) < wiz_lock_level ) {
//		write("�Բ���" + MUD_NAME + "Ŀǰ������ʦ�ȼ� " + WIZ_LOCK_LEVEL
		write("�Բ��𣬽�ӹȺ����Ŀǰ������ʦ�ȼ� " + WIZ_LOCK_LEVEL
			+ " ���ϵ��˲������ߡ�\n");
		destruct(ob);
		return;
	}
	
	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	if( arg=="guest" ) {
		// If guest, let them create the character.
		confirm_id("Yes", ob);
		return;
	} else if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) {
		if( ob->restore() ) {
			write("���������룺");
			input_to("get_passwd", 1, ob);
			return;
		}
		write("�������ﴢ�浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
		destruct(ob);
		return;
	}

	write("ʹ�� " + (string)ob->query("id") + " ������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");
	input_to("confirm_id", ob);
}

void get_passwd(string pass, object ob)
{
	string my_pass;
	object user;

	write("\n");
	my_pass = ob->query("password");
	if( crypt(pass, my_pass) != my_pass ) {
		write("�������\n");
		destruct(ob);
		return;
	}

	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
		if( user->query_temp("netdead") ) {
			reconnect(ob, user);
			return;
		}
		write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
			log_file( "USAGE", sprintf("%s loggined from %s (%s)\n", user->query("name"),
				query_ip_name(ob), ctime(time()) ) );
			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}
	write("�������´���������\n");
	confirm_id("y", ob);
}

void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}	

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("�ðɣ���ӭ�´�������\n");
		destruct(ob);
		return;
	} else {
		tell_object(user, "���˴ӱ�( " + query_ip_number(ob)
			+ " )����ȡ���������Ƶ����\n");
		log_file( "USAGE", sprintf("%s replaced by %s (%s)\n", user->query("name"),
			query_ip_name(ob), ctime(time()) ) );
	}

	// Kick out tho old player.
	old_link = user->query_temp("link_ob");
	if( old_link ) {
		exec(old_link, user);
		destruct(old_link);
	}

	reconnect(ob, user);	
}

void confirm_id(string yn, object ob)
{
	if( yn=="" ) {
		write("ʹ��������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");
		input_to("confirm_id", ob);
		return;
	}	

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("�ðɣ���ô��������������Ӣ�����֣�");
		input_to("get_id", ob);
		return;
	}
	write( @TEXT

���������ĸ��մ���������������ִ��������������Ժ��ܸ��ģ�
����������������Ź۵���������ɾ���������벻Ҫѡ���ӹС˵��
��������������

(��������֮�⣬�� mud �����ȡ�ºš���Ƶ���ƣ�����֣�ؽ�����
 ȡһ���Ƚ������ֵ��������֡�)

TEXT
	);
	write("�����������֣�");
	input_to("get_name", ob);
}

void get_name(string arg, object ob)
{
	if( !check_legal_name(arg) ) {
		write("�����������֣�");
		input_to("get_name", ob);
		return;
	}
	printf("%O\n", ob);
	ob->set("name", arg);
	write("���趨�������룺");
	input_to("new_password", 1, ob);
}

void new_password(string pass, object ob)
{
	write("\n");
	if( strlen(pass)<5 ) {
		write("����ĳ�������Ҫ����ַ����������������룺");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
	write("��������һ���������룬��ȷ����û�Ǵ�");
	input_to("confirm_password", 1, ob);
}

void confirm_password(string pass, object ob)
{
	mapping my;
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("��������������벢��һ�����������趨һ�����룺");
		input_to("new_password", 1, ob);
		return;
	}

	write(@TEXT

һ��������츳��������������ϰ������ϢϢ��ء��������е����������
���������츳��

	������Ӱ�칥���������������Ĵ�С��
	���ԣ�Ӱ��ѧϰ�书�ؼ����ٶȼ����ʦ����������
	���ǣ�Ӱ�������ָ����ٶȼ������������ӵ�������
	����Ӱ���������ܵ�������

TEXT);
	my = ([]);
	random_gift(my);
	printf("\n����[%d]�� ����[%d]�� ����[%d]�� ��[%d]\n",
                my["str"], my["int"], my["con"], my["dex"]);
        write("��������һ���츳��");
        input_to("get_gift", ob, my);
}

void get_gift(string yn, object ob, mapping my)
{
	if (yn[0] != 'y' && yn[0] != 'Y') {
		random_gift(my);
		printf("\n����[%d]�� ����[%d]�� ����[%d]�� ��[%d]\n",
                      my["str"], my["int"], my["con"], my["dex"]);
                write("��ͬ����һ���츳��");
		input_to("get_gift", ob, my);
	}
	if (yn[0] == 'y' || yn[0] == 'Y') {
          	write("\n���ĵ����ʼ���ַ��");
        	input_to("get_email", ob, my);
	}
}

void get_email(string email, object ob, mapping my)
{
	object user;

	write("\n");
	if (email == "" || strsrch(email, "@") == -1) {
		write("�����ʼ���ַ��Ҫ�� id@address �ĸ�ʽ��\n");
		write("���ĵ����ʼ���ַ��");
		input_to("get_email", ob, my);
		return;
	}
	ob->set("email", email);
	ob->set("registered", 1);

	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) )
		return;
	user->set("str", my["str"]);
	user->set("dex", my["dex"]);
	user->set("con", my["con"]);
	user->set("int", my["int"]);
	ob->set("registered", 1);
	user->set("registered", 1);

	write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��");
	input_to("get_gender", ob, user);
}

void get_gender(string gender, object ob, object user)
{
	write("\n");
	if( gender=="" ) {
		write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "����");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "Ů��" );
	else {
		write("�Բ�����ֻ��ѡ������(m)��Ů��(f)�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}

	log_file( "USAGE", sprintf("%s was created from %s (%s)\n", user->query("id"),
		query_ip_name(ob), ctime(time()) ) );
	init_new_player(user);
	enter_world(ob, user);
	write("\n");
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	user = new(ob->query("body"));
	if(!user) {
		write("���ڿ������������޸�ʹ��������ĳ�ʽ���޷����и��ơ�\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

void init_new_player(object user)
{
	user->set("title", "��ͨ����");
	user->set("birthday", time() );
	user->set("potential", 99);

	user->set("channels", ({ "chat", "rumor", "music" }) );
//	user->set("balance", 1000);
}

		
varargs void enter_world(object ob, object user, int silent)
{
	object cloth, room, mailbox;
	string startroom;
        object login_ob;

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set("registered", ob->query("registered"));
	exec(user, ob);

	write("\nĿǰȨ�ޣ�" + wizhood(user) + "\n");

	user->setup();
	if (!user->query("food") && !user->query("water") && ob->query("age") == 14) {
	        user->set("food", user->max_food_capacity());
        	user->set("water", user->max_water_capacity());
	}

	// In case of new player, we save them here right aftre setup 
	// compeleted.
	user->save();
	ob->save();
	
	if (wizhood(user) == "(player)") {
		cloth = new("/clone/misc/cloth");
		cloth->move(user);
		cloth->wear();
	}
	else {
		cloth = new("/d/city2/obj/jinduan");
		cloth->move(user);
		cloth->wear();
	}
// Give user a mailbox.
// Modified by Hop at 1997.04.10
	mailbox = new("clone/misc/mailbox");
	mailbox->move(user);
// End of modification

	if( !silent ) {
		cat(MOTD);
//		if (ob->query("registered") == 0) 
//			cat(UNREG_MOTD);
//		else 
//			cat(MOTD);
		if( ob->query("new_mail") ) {
			write( GRN + "\n�������ţ��쿴�������ɣ�\n\n" + NOR);
			ob->set("new_mail", 0);
		}
		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else if( !stringp(startroom = user->query("startroom")) )
			startroom = START_ROOM;

		if( !catch(load_object(startroom)) )
			user->move(startroom);
		else {
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		tell_room(startroom, user->query("name") + "���߽���������硣\n",
			({user}));
	}
        login_ob=new(LOGIN_OB);
        login_ob->set("id",user->query("id"));
        login_ob->restore();
        write("���ϴ������Ǵ�" + HIR +login_ob->query("last_from") + NOR + " on " + HIR +ctime(login_ob->query("last_on"))+ NOR + "\n");
        destruct(login_ob);

	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s��%s���߽��롣", user->name(), query_ip_name(user)) );
	UPDATE_D->check_user(user);
}

varargs void reconnect(object ob, object user, int silent)
{
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	exec(user, ob);

	user->reconnect();
	if( !silent ) {
		tell_room(environment(user), user->query("name") + "�������߻ص�������硣\n",
		({user}));
	}
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s��%s�������߽��롣", user->query("name"), query_ip_name(user)) );
	UPDATE_D->check_user(user);
}

int check_legal_id(string id)
{
	int i;

	i = strlen(id);
	
	if( (strlen(id) < 3) || (strlen(id) > 12 ) ) {
		write("�Բ������Ӣ�����ֱ����� 3 �� 12 ��Ӣ����ĸ��\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) {
			write("�Բ������Ӣ������ֻ����Ӣ����ĸ��\n");
			return 0;
		}

	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);
	
	if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
		write("�Բ�������������ֱ����� 1 �� 6 �������֡�\n");
		return 0;
	}
	while(i--) {
		if( name[i]<=' ' ) {
			write("�Բ�������������ֲ����ÿ�����Ԫ��\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("�Բ��������á����ġ�ȡ���֡�\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) {
		write("�Բ����������ֻ���������˵����š�\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++)
		if( clonep(body[i])
		&&	getuid(body[i]) == name ) return body[i];

	return 0;
}

int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}

int set_madlock(int setmark)
{
	if( wiz_level(this_player(1)) < wiz_level("(arch)") )
		return 0;
	if( setmark == 1 ) mad_lock = 1;
	else mad_lock = 0;
	return 1;
}

int get_madlock()
{
	return mad_lock;
}
