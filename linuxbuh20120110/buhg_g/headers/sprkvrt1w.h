/*$Id: sprkvrt1w.h,v 1.1 2011-08-29 07:13:44 sasa Exp $*/
/*04.03.2009	31.04.2005	����� �.�.	sprkvrt1w.h
��������� ��� ���ޣ�� ����� 1��
*/

class sprkvrt1_nast
 {
  public:
  class iceb_u_spisok sheta;               //��������� ��� ������ ��� ������ ������ ��������
  class iceb_u_int kodi_pd; //���� ��������� �������
  class iceb_u_spisok kodi_nah;       // ���� ���������� � ��������� �������
  char gosstrah[512]; //���� ������ �� 27 �������
  short		TYP; /*����� 0-����������� ����� 1-���������� �����*/
  short    *kodnvf8dr;  /*���� �� �������� � ����� 8��*/
  short    *kodud;  /*���� ��������� �� �������� � ����� 8��*/
  
  class iceb_u_int kodi_pd_prov; //���� ��������� ������� ��� ������� ������ ��ң� �� ������� �����
  
  sprkvrt1_nast() //�����������
   {
    memset(gosstrah,'\0',sizeof(gosstrah));
    TYP=0;    
    kodnvf8dr=NULL;
    kodud=NULL;
   }

  ~sprkvrt1_nast() //����������
   {
    if(kodnvf8dr != NULL)
      delete(kodnvf8dr);
    if(kodud != NULL)
      delete(kodud);
   }

 };

