/*$Id: iceb_l_smenabaz_p.c,v 1.5 2011-02-21 07:36:07 sasa Exp $*/
/*17.04.2010	17.04.2010	Белых А.И.	iceb_l_smenabaz_p.c
Меню для ввода реквизитов поиска 
*/
#include <stdlib.h>
#include "iceb_libbuh.h"

enum
 {
  E_IMABAZ,
  E_IMAKONTR,
  KOLENTER  
 };

enum
 {
  FK2,
  FK4,
  FK10,
  KOL_FK
 };

class iceb_l_smenabaz_p_data
 {
  public:
    
  GtkWidget *entry[KOLENTER];
  GtkWidget *knopka[KOL_FK];
  GtkWidget *window;
  short kl_shift;
  short voz;      //0-ввели 1 нет

  class iceb_u_str imabaz;
  class iceb_u_str imakontr;  
  
  iceb_l_smenabaz_p_data() //Конструктор
   {
    kl_shift=0;
    voz=1;
   }

  void read_rek()
   {
    imabaz.new_plus(iceb_u_fromutf((char*)gtk_entry_get_text(GTK_ENTRY(entry[E_IMABAZ]))));
    imakontr.new_plus(iceb_u_fromutf((char*)gtk_entry_get_text(GTK_ENTRY(entry[E_IMAKONTR]))));
   }

  void clear_data()
   {
    clear_rek();
    for(int i=0; i< KOLENTER; i++)
     gtk_entry_set_text(GTK_ENTRY(entry[i]),"");

    gtk_widget_grab_focus(entry[0]);
   }

  void clear_rek()
   {
    imabaz.new_plus("");
    imakontr.new_plus("");
   }
 };

void iceb_l_smenabaz_p_clear(class iceb_l_smenabaz_p_data *data);
void    iceb_l_smenabaz_p_vvod(GtkWidget *widget,class iceb_l_smenabaz_p_data *data);
void  iceb_l_smenabaz_p_knopka(GtkWidget *widget,class iceb_l_smenabaz_p_data *data);
gboolean   iceb_l_smenabaz_p_key_press(GtkWidget *widget,GdkEventKey *event,class iceb_l_smenabaz_p_data *data);

extern char      *name_system;

int iceb_l_smenabaz_p(class iceb_u_str *imabaz,class iceb_u_str *imakontr,GtkWidget *wpredok)
{
class iceb_l_smenabaz_p_data data;
char strsql[312];
data.imabaz.new_plus(imabaz->ravno());
data.imakontr.new_plus(imakontr->ravno());

data.window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position( GTK_WINDOW(data.window),ICEB_POS_CENTER);
gtk_window_set_modal(GTK_WINDOW(data.window),TRUE);
sprintf(strsql,"%s %s",name_system,gettext("Поиск"));

gtk_window_set_title(GTK_WINDOW(data.window),strsql);

gtk_signal_connect(GTK_OBJECT(data.window),"delete_event",GTK_SIGNAL_FUNC(gtk_widget_destroy),NULL);
gtk_signal_connect(GTK_OBJECT(data.window),"destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
gtk_signal_connect_after(GTK_OBJECT(data.window),"key_press_event",GTK_SIGNAL_FUNC(iceb_l_smenabaz_p_key_press),&data);

if(wpredok != NULL)
 {
  gdk_window_set_cursor(wpredok->window,gdk_cursor_new(ICEB_CURSOR_GDITE));
  //Удерживать окно над породившем его окном всегда
  gtk_window_set_transient_for(GTK_WINDOW(data.window),GTK_WINDOW(wpredok));
  //Закрыть окно если окно предок удалено
  gtk_window_set_destroy_with_parent(GTK_WINDOW(data.window),TRUE);
 }



GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
GtkWidget *hbox[KOLENTER];
for(int i=0; i < KOLENTER; i++)
 hbox[i] = gtk_hbox_new (FALSE, 0);
GtkWidget *hboxknop = gtk_hbox_new (FALSE, 0);

gtk_container_add (GTK_CONTAINER (data.window), vbox);
for(int i=0; i < KOLENTER; i++)
  gtk_box_pack_start (GTK_BOX (vbox),hbox[i], TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hboxknop, TRUE, TRUE, 0);


GtkWidget *label=gtk_label_new(gettext("База"));
gtk_box_pack_start (GTK_BOX (hbox[E_IMABAZ]), label, FALSE, FALSE, 0);

data.entry[E_IMABAZ] = gtk_entry_new_with_max_length (20);
gtk_box_pack_start (GTK_BOX (hbox[E_IMABAZ]), data.entry[E_IMABAZ], TRUE, TRUE, 0);
gtk_signal_connect(GTK_OBJECT (data.entry[E_IMABAZ]), "activate",GTK_SIGNAL_FUNC(iceb_l_smenabaz_p_vvod),&data);
gtk_entry_set_text(GTK_ENTRY(data.entry[E_IMABAZ]),data.imabaz.ravno_toutf());
gtk_object_set_user_data(GTK_OBJECT(data.entry[E_IMABAZ]),(gpointer)E_IMABAZ);

label=gtk_label_new(gettext("Наименование контрагента"));
gtk_box_pack_start (GTK_BOX (hbox[E_IMAKONTR]), label, FALSE, FALSE, 0);

data.entry[E_IMAKONTR] = gtk_entry_new_with_max_length (80);
gtk_box_pack_start (GTK_BOX (hbox[E_IMAKONTR]), data.entry[E_IMAKONTR], TRUE, TRUE, 0);
gtk_signal_connect(GTK_OBJECT (data.entry[E_IMAKONTR]), "activate",GTK_SIGNAL_FUNC(iceb_l_smenabaz_p_vvod),&data);
gtk_entry_set_text(GTK_ENTRY(data.entry[E_IMAKONTR]),data.imakontr.ravno_toutf());
gtk_object_set_user_data(GTK_OBJECT(data.entry[E_IMAKONTR]),(gpointer)E_IMAKONTR);


GtkTooltips *tooltips[KOL_FK];

sprintf(strsql,"F2 %s",gettext("Поиск"));
data.knopka[FK2]=gtk_button_new_with_label(strsql);
tooltips[FK2]=gtk_tooltips_new();
gtk_tooltips_set_tip(tooltips[FK2],data.knopka[FK2],gettext("Начать поиск нужных записей"),NULL);
gtk_signal_connect(GTK_OBJECT(data.knopka[FK2]),"clicked",GTK_SIGNAL_FUNC(iceb_l_smenabaz_p_knopka),&data);
gtk_object_set_user_data(GTK_OBJECT(data.knopka[FK2]),(gpointer)FK2);
gtk_box_pack_start(GTK_BOX(hboxknop), data.knopka[FK2], TRUE, TRUE, 0);

sprintf(strsql,"F4 %s",gettext("Очистить"));
data.knopka[FK4]=gtk_button_new_with_label(strsql);
tooltips[FK4]=gtk_tooltips_new();
gtk_tooltips_set_tip(tooltips[FK4],data.knopka[FK4],gettext("Очистить меню от введеноой информации"),NULL);
gtk_signal_connect(GTK_OBJECT(data.knopka[FK4]),"clicked",GTK_SIGNAL_FUNC(iceb_l_smenabaz_p_knopka),&data);
gtk_object_set_user_data(GTK_OBJECT(data.knopka[FK4]),(gpointer)FK4);
gtk_box_pack_start(GTK_BOX(hboxknop), data.knopka[FK4], TRUE, TRUE, 0);


sprintf(strsql,"F10 %s",gettext("Выход"));
data.knopka[FK10]=gtk_button_new_with_label(strsql);
tooltips[FK10]=gtk_tooltips_new();
gtk_tooltips_set_tip(tooltips[FK10],data.knopka[FK10],gettext("Поиск не выполнять"),NULL);
gtk_signal_connect(GTK_OBJECT(data.knopka[FK10]),"clicked",GTK_SIGNAL_FUNC(iceb_l_smenabaz_p_knopka),&data);
gtk_object_set_user_data(GTK_OBJECT(data.knopka[FK10]),(gpointer)FK10);
gtk_box_pack_start(GTK_BOX(hboxknop), data.knopka[FK10], TRUE, TRUE, 0);

gtk_widget_grab_focus(data.entry[0]);

gtk_widget_show_all (data.window);

gtk_main();

if(wpredok != NULL)
  gdk_window_set_cursor(wpredok->window,gdk_cursor_new(ICEB_CURSOR));
if(data.voz == 0)
 {
  imabaz->new_plus(data.imabaz.ravno());
  imakontr->new_plus(data.imakontr.ravno());
 }
return(data.voz);

}
/*********************************/
/*Обработка нажатия клавиш       */
/*********************************/

gboolean   iceb_l_smenabaz_p_key_press(GtkWidget *widget,GdkEventKey *event,class iceb_l_smenabaz_p_data *data)
{
//char  bros[512];

//printf("vl_zarkateg_key_press\n");
switch(event->keyval)
 {

  case GDK_F2:
    gtk_signal_emit_by_name(GTK_OBJECT(data->knopka[FK2]),"clicked");
    return(FALSE);

  case GDK_F4:
    gtk_signal_emit_by_name(GTK_OBJECT(data->knopka[FK4]),"clicked");
    return(TRUE);

    
  case GDK_Escape:
  case GDK_F10:
    gtk_signal_emit_by_name(GTK_OBJECT(data->knopka[FK10]),"clicked");
    return(FALSE);

  case ICEB_REG_L:
  case ICEB_REG_R:
//    printf("Нажата клавиша Shift\n");

    data->kl_shift=1;

    return(TRUE);
 }

return(TRUE);
}
/*****************************/
/*Обработчик нажатия кнопок  */
/*****************************/
void  iceb_l_smenabaz_p_knopka(GtkWidget *widget,class iceb_l_smenabaz_p_data *data)
{
//char bros[512];

int knop=GPOINTER_TO_INT(gtk_object_get_user_data(GTK_OBJECT(widget)));
//g_print("iceb_l_smenabaz_p_knopka knop=%d\n",knop);

switch (knop)
 {
  case FK2:
    data->read_rek();
    data->voz=0;
    gtk_widget_destroy(data->window);
    return;  

  case FK4:
    data->clear_data();
    return;  


  case FK10:
    data->voz=1;
    gtk_widget_destroy(data->window);

    return;
 }
}
/********************************/
/*чтение текста и перевод фокуса на следующюю строку ввода*/
/******************************************/

void    iceb_l_smenabaz_p_vvod(GtkWidget *widget,class iceb_l_smenabaz_p_data *data)
{
int enter=GPOINTER_TO_INT(gtk_object_get_user_data(GTK_OBJECT(widget)));

switch (enter)
 {
  case E_IMABAZ:
    data->imabaz.new_plus(iceb_u_fromutf((char*)gtk_entry_get_text(GTK_ENTRY(data->entry[E_IMABAZ]))));
    break;
  case E_IMAKONTR:
    data->imakontr.new_plus(iceb_u_fromutf((char*)gtk_entry_get_text(GTK_ENTRY(data->entry[E_IMAKONTR]))));
    break;
 }

enter+=1;
if(enter >= KOLENTER)
 enter=0;
gtk_widget_grab_focus(data->entry[enter]);
 
}
