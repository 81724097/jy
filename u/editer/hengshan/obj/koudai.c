// item: /d/hengshan/obj/koudai.c
// written by Dewey

inherit ITEM;

void create()
{
        set_name("�ڴ�", ({"kou dai", "dai"}));
        set_weight(1000);
        set_max_encumbrance(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ���ֹ����ƵĿڴ������԰Ѷ���װ�����档\n");
                set("value", 50);
        }
}

