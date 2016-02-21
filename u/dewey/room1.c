// Room: /d/snow/school.c                                                       
                                                                                
#include "/include/ansi.h";                                                     
inherit ROOM;                                                                   
inherit F_SAVE;                                                                 
int zhenfa;                                                                     
//int do_change();                                                              
void create()                                                                   
{                                                                               
                                                                                
string longtxt,randtxt;                                                         
mapping *notes;                                                                 
        int num;                                                                
        restore_object("/data/board/info_b");                                   
        notes = query("notes");                                                 
        zhenfa=random(4);                                                       
        set("short","��Ժ");                                                    
        if( !arrayp(notes) || num < 1 || num > sizeof(notes) )                  
        {                                                                       
                                                                                
        switch( zhenfa ) {                                                      
        case 0:                                                                 
                randtxt="Զ�������ö��ķ�����������Ƭɽ�ִ����˲���������";     
                break;                                                          
        case 1:                                                                 
                randtxt="Զ����������ľ����������Ƭɽ�ִ����˲���������";     
                break;                                                          
        case 2:                                                                 
                randtxt="Զ��Ʈ���ŵ�һ�ƴ��̣�����Ƭɽ�ִ����˲���������";     
                break;                                                          
        case 3:                                                                 
                randtxt="Զ��������������ˮ��������Ƭɽ�ִ����˲���������";     
                break;                                                          
        }                                                                       
        longtxt =                                                               
        "������һ�������Ժ����Ȼ���ӿ��������Ͼ��ˣ����Ǵ�ɨ�ú�             
���࣬ǽ���Ϲ���һ��ɽˮ�����⾳��Ϊ���ף���Ժ�Ĵ��ſ��ڱ��ߡ�                  
"+randtxt+"\n";                                                                 
        set("long", longtxt                                                     
        );                                                                      
        set("exits", ([ /* sizeof() == 1 */                                     
        "south" : __DIR__"entry2",                                              
        "north" : __DIR__"entry",                                               
        "east":__DIR__"workroom",                                                  
        "down":__FILE__,                                                        
        ]));                                                                    
        }                                                                       
        else{ num=sizeof(notes)-1;                                              
        if (notes[num]["status"]) {set("short","����");                         
        set("long","������һƬ���棬ֻ��һ��������ʯ�������������ʮ�ֹ���");
}                                                                               
        delete("exits/down");}                                                  
                                                                                
        setup();                                                                
	 "/clone/board/wiz_b"->foo();
}                                                                               
void init()                                                                     
{       remove_call_out("help_signal");                                         
        call_out("help_signal",20);                                             
        this_player()->set("marks/zhen",zhenfa);                                
        add_action("do_change","destroy");                                      
        add_action("do_rebuild","rebuild");                                     
}                                                                               
int help_signal()                                                               
{                                                                               
        string signal;                                                          
        switch( zhenfa ) {                                                      
        case 0:                                                                 
                signal=CYN "һ�����ҡҷ֮������������ö������㲻���������еķ���" NOR;                                                                        
                break;                                                          
        case 1:                                                                 
                signal=HBYEL "һ������ľ����������������ľ���ʱƽ��������" NOR;
;                                                                               
                break;                                                          
        case 2:                                                                 
                signal=HIW "Զ������������ʹ���潭�����㲻��������е����ˡ�" NOR;
;                                                                               
                break;                                                          
        case 3:                                                                 
                signal=BLU "Զ����ˮ����������������ɽ�����Եø����������" NOR;
                break;                                                          
        }                                                                       
        write(signal+"\n");                                                     
        return 1;}                                                              
        int do_change(string arg)                                               
        {if (!arg) return notify_fail("������\n");                              
        set("short","����");                                                    
        set("long","������һƬ���棬ֻ��һ��������ʯ�������������ʮ�ֹ���");
                                                                                
        delete("exits/down");                                                   
        call_other("/clone/board/try_b","do_destroy",this_player(),arg);        
        return 1;}                                                              
int do_rebuild(string arg)                                                      
        {                                                                       
        if (!arg) return notify_fail("������\n");                               
        set("short","��Ժ");                                                    
                                                                                
        set("long", "������һ�������Ժ����Ȼ���ӿ��������Ͼ��ˣ����Ǵ�ɨ�ú� 
        ���࣬ǽ���Ϲ���һ��ɽˮ�����⾳��Ϊ���ף���Ժ�Ĵ��ſ��ڱ��ߡ�          
        \n" );                                                                  
        set("exits/down",__FILE__);                                             
        call_other("/clone/board/try_b","do_rebuild",this_player(),arg);        
        return 1;}      //����Ϊ����ԭ��                                        
