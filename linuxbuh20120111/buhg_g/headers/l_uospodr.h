/*$Id: l_uospodr.h,v 1.4 2011-01-13 13:49:51 sasa Exp $*/
/*29.11.2008	18.10.2007	Белых А.И.	l_uospodr.h
Реквизиты для работы со списком подразделений в подсистеме "Учёт основных средств"
*/
class l_uospodr_rek
 {
  public:
   class iceb_u_str kod;
   class iceb_u_str naim;
   int metka_sost;   
   l_uospodr_rek()
    {
     clear_data();
    }
   void clear_data()
    {
     metka_sost=0;
     kod.new_plus("");
     naim.new_plus("");
    }
 }; 
