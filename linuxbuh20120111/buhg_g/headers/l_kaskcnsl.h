/*$Id: l_kaskcnsl.h,v 1.4 2011-01-13 13:49:50 sasa Exp $*/
/*29.09.2006	29.09.2006	Белых А.И.	l_kaskcnsl.h
Реквизиты для поиска записей
*/
class l_kaskcnsl_rek
 {
  public:
   class iceb_u_str god;
   class iceb_u_str kod;
   class iceb_u_str kas;
   short metka_poi;
      
   l_kaskcnsl_rek()
    {
     clear_data();
    }
  void clear_data()
   {
    kod.new_plus("");
    god.new_plus("");
    kas.new_plus("");
    metka_poi=0;
   }
 
 };
