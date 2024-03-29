//---------------------------------------------------------------------------

#ifndef OperationH
#define OperationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "trayicon.h"
#include <map>
#include <vector>
#include "LfcString.h"
//---------------------------------------------------------------------------
struct CIdNum{
        int id;
        int num;
        float unitprice;       //20120723
        AnsiString spname;      //只有out时才有spname概念,(in时 "")
        AnsiString unit;        //20120809 加入单位,不再与费用类别绑定
        bool operator == (const CIdNum &right) const{
                return num == right.num && unitprice == right.unitprice && spname == right.spname && unit == right.unit;
        }

};
typedef std::map<AnsiString, CIdNum>    money_t;
typedef std::map<AnsiString, int>       type_t;
typedef std::vector<CString>               sql_t;
//typedef std::map<AnsiString, money_t>   money_rec_t;    //<oid, money_detalis>      cache type
enum E_TYPE{
        E_TYPE_IN,
        E_TYPE_OUT,
};
//
enum E_WAY{
        E_WAY_EMPTY = 0,
        E_WAY_QICK = 1,
        E_WAY_AIR,
};
class TOperationForm : public TForm
{
__published:	// IDE-managed Components
        TButton *btnAdd;
        TButton *btnMod;
        TButton *btnDel;
        TButton *btnCancel;
        TPanel *Panel22;
        TListView *lvOpDetail;
        TPanel *plInput;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *edtInValue;
        TComboBox *cbbInType;
        TListView *lvInDetail;
        TListView *lvOutDetail;
        TComboBox *cbbOutType;
        TEdit *edtOutValue;
        TButton *btnInAdd;
        TButton *btnInMod;
        TButton *btnInDel;
        TButton *btnOutAdd;
        TButton *btnOutMod;
        TButton *btnOutDel;
        TEdit *edtDebug;
        TComboBox *cbbSpName;
        TComboBox *cbbInWayCalc;
        TComboBox *cbbOutWayCalc;
        TButton *Button1;
        TTrayIcon *TrayIcon1;
        TButton *btnQry;
        TDateTimePicker *dtpArrival;
        TComboBox *cbbGoodsSrc;
        TPanel *Panel7;
        TPanel *Panel1;
        TEdit *edtOId;
        TPanel *Panel8;
        TPanel *Panel2;
        TComboBox *cbbOpCodeSl;
        TComboBox *cbbGoodsDst;
        TPanel *Panel9;
        TPanel *Panel3;
        TComboBox *cbbClShortName;
        TEdit *edtNum;
        TPanel *Panel10;
        TPanel *Panel4;
        TComboBox *cbbGoodsName;
        TEdit *edtNetWeight;
        TPanel *Panel11;
        TPanel *Panel5;
        TEdit *edtLoadingId;
        TEdit *edtVolume;
        TPanel *Panel13;
        TComboBox *cbbWay0;
        TPanel *Panel6;
        TComboBox *cbbWay;
        TPanel *Panel21;
        TPanel *Panel17;
        TPanel *Panel19;
        TLabel *Label12;
        TLabel *lbGrossPect;
        TLabel *Label10;
        TLabel *lbGross;
        TEdit *edtInUnitPrice;
        TEdit *edtOutUnitPrice;
        TPanel *Panel30;
        TEdit *edtWayOther;
        TEdit *edtQryOId;
        TPanel *Panel14;
        TComboBox *cbbIsArrival;
        TPanel *Panel15;
        TLabel *Label11;
        TLabel *lbSumIn;
        TLabel *Label6;
        TLabel *lbSumOut;
        TButton *btnOK;
        TPanel *Panel12;
        TComboBox *cbbCondIn;
        TPanel *Panel16;
        TDateTimePicker *dtpCondIn;
        TPanel *Panel18;
        TComboBox *cbbInBank;
        TPanel *Panel20;
        TComboBox *cbbCondKB;
        TPanel *Panel23;
        TDateTimePicker *dtpCondKB;
        TPanel *Panel24;
        TComboBox *cbbKBBank;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall lvInDetailSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall lvOpDetailSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnInAddClick(TObject *Sender);
        void __fastcall btnInModClick(TObject *Sender);
        void __fastcall btnInDelClick(TObject *Sender);
        void __fastcall btnOutAddClick(TObject *Sender);
        void __fastcall btnOutModClick(TObject *Sender);
        void __fastcall btnOutDelClick(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall lvOutDetailSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall cbbOpCodeSlChange(TObject *Sender);
        void __fastcall cbbInTypeChange(TObject *Sender);
        void __fastcall cbbOutTypeChange(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall cbbGoodsDstChange(TObject *Sender);
        void __fastcall cbbGoodsDstSelect(TObject *Sender);
        void __fastcall cbbWay0Change(TObject *Sender);
private:	// User declarations
        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;
        type_t m_mInType;
        type_t m_mOutType;

        money_t m_mInDetailBefore;
        money_t m_mOutDetailBefore;

//        money_rec_t m_mCacheInDetail;
//        money_rec_t m_mCacheOutDetail;
//        std::vector<AnsiString> &m_v_cl_short_names;
public:		// User declarations
        __fastcall TOperationForm(TComponent* Owner);
        int m_nAuthor;        
        bool checkInput();
        void clearInput();
        void ResetCtrl();

        void Editor2RowAdd(TListItem *pItem);
        void Editor2RowUpdate(TListItem *pItem);
        void Row2Editor(TListItem *pItem);

        int getIdByType(E_TYPE et, AnsiString type);
        money_t loadDetail2map(E_TYPE et, TListView *v);//加载lv内容到map中，in、out通用
        void genDiffMaps(money_t &mbefore, money_t &mafter, \
                        money_t &beinsert, money_t &beupdate, money_t &bedelete);
        void loadBeforeMap();//加载beforemap
        void genMoneySql(sql_t &rt, AnsiString oid);//获取前后快照，压入sql列表，后main取出事务执行之
        void flushMoneyDetail(AnsiString OId);          //点击记录明细时，刷新费用明细

        int onAdd(TObject *Sender);
        void onMod(TObject *Sender);
        void flushCbbClShortName(const AnsiString &op_code_sl);//按销售刷新客户列表，经理以上不受限制
        void refresh_goods();
        bool addDicGoodsSrc(AnsiString src);//添加发货地-不存在则添加，true-已经存在或不存在时添加成功
        void refresh_dic_goods_src();
        bool checkValidGoodsSrc(AnsiString src);//由于目的地支持输入搜索，要开放edit，估要检查输入的合法性
        float genSumMomey(TListView *lv, int column);//对listview的column求和
        int get_way_type(TComboBox *cbb);
        void flush_lirun();  
};
//---------------------------------------------------------------------------
extern PACKAGE TOperationForm *OperationForm;
//---------------------------------------------------------------------------
#endif
