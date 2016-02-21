// abandon.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !arg || arg=="" ) 
		return notify_fail("��Ҫ������һ��ܣ�\n");

	if( !me->delete_skill(arg) )
		return notify_fail("�㲢û��ѧ������ܡ�\n");

	write("�������������ѧϰ" + to_chinese(arg) + "��\n");
	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��abandon|fangqi <��������>

����һ������ѧ���ļ��ܣ�ע��������˵�ġ���������ָ������ܴ�������
��������ɾ����������Ժ�Ҫ��������ӣ���ʼ����������ؿ��������

���ָ��ʹ�õĳ���ͨ��������ɾ��һЩ����С�ġ��������ļ��ܣ�����ÿ��
�����Ų�ͬ���츳������ϰ���书Ҳ������ͬ�����������ѧ����ͷ��ֻ����
��������
TEXT
	);
	return 1;
}
